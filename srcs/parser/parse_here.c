/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_here.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:10:26 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/01 14:45:33 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_pipe_limiter(int *p, char **lim, char *limiter, int *should_parse);

static void	write_heredoc(char *s, t_shell *sh, int fd)
{
	char	*parse;

	while (*s)
	{
		if (*s == '$')
		{
			parse = parse_var(&s, sh);
			if (parse)
			{
				write (fd, parse, ft_strlen(parse));
				free (parse);
			}
			continue ;
		}
		write (fd, s++, 1);
	}
	ft_putchar_fd('\n', fd);
}

char	*parse_limiter(char *s, int *should_parse)
{
	char	*lim;
	int		q;
	int		i;

	lim = ft_calloc(1, ft_strlen(s) + 1);
	if (!lim)
		return (NULL);
	*should_parse = 1;
	i = 0;
	while (*s)
	{
		if (*s == '\'' || *s == '"')
		{
			q = *s;
			s++ ;
			*should_parse = 0;
			while (*s && *s != q)
				lim[i++] = *s++;
			if (*s == q)
				s++ ;
			continue ;
		}
		lim[i++] = *s++;
	}
	return (lim);
}

int	parse_heredoc(char *limiter, t_shell *sh)
{
	int		p[2];
	char	*line;
	char	*lim;
	int		should_parse;

	if (init_pipe_limiter(p, &lim, limiter, &should_parse))
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strncmp(line, lim, -1))
			break ;
		if (should_parse)
			write_heredoc(line, sh, p[1]);
		else
			ft_putendl_fd(line, p[1]);
		free (line);
	}
	free (lim);
	free (line);
	close (p[1]);
	return (p[0]);
}

void	parse_here(t_cmd *cmd, t_shell *sh)
{
	t_pipe	*p;
	t_redir	*r;

	if (!cmd)
		return ;
	if (cmd->type == EXEC)
		return ;
	if (cmd->type == PIPE)
	{
		p = (t_pipe *)cmd;
		parse_here(p->left, sh);
		parse_here(p->right, sh);
	}
	else if (cmd->type == REDIR)
	{
		r = (t_redir *)cmd;
		if (r->mode == 'h')
		{
			r->fd = parse_heredoc(r->file, sh);
		}
		parse_here(r->cmd, sh);
	}
}
