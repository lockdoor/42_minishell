/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_here.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:10:26 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/29 08:32:22 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
				if (*parse)
					write (fd, parse, sizeof (parse));
				free (parse);
			}
		}
		else
			write (fd, s++, 1);
	}
}

int	parse_heredoc(char *limiter, t_shell *sh)
{
	int		p[2];
	char	*line;

	if (pipe(p))
	{
		perror("fd_heredoc");
		return (-1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strncmp(line, limiter, ft_strlen(line)))
			break ;
		write_heredoc(line, sh, p[1]);
		ft_putchar_fd('\n', p[1]);
		free (line);
	}
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
