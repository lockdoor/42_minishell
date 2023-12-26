/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_here.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:10:26 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/26 16:40:01 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*white_space(char **str, t_shell *sh)
{
	char	*s;
	char	*space;

	(void)	sh;
	s = *str;
	while (*s && ft_strchr(WHITESPACE, *s))
		s++ ;
	space = ft_substr(*str, 0, s - *str);
	*str = s;
	if (!space)
		return (NULL);
	return (space);
}

char	*parse_heredoc_2(char *s, t_shell *sh)
{
	char	*result;
	char	*t;
	char	*(*func)(char **, t_shell *);

	result = ft_strdup("");
	while (*s && result)
	{
		if (ft_strchr(WHITESPACE, *s))
			func = &white_space;
		else if (*s == '$')
			func = &parse_var;
		else if (*s == '\'')
			func = &parse_qoute;
		else if (*s == '"')
			func = &parse_db_qoute;
		else
			func = &get_word;
		t = func(&s, sh);
		if (!t)
		{
			free (result);
			return (NULL);
		}
		result = join_free(result, t);
		
		// debug
		// printf ("parse_token: %s\n", result);
	}
	return (result);
}

int	parse_heredoc(char *limiter, t_shell *sh)
{
	int		p[2];
	char	*line;
	char	*parse;

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
		/* should parse before write */
		parse = parse_heredoc_2(line, sh);
		ft_putendl_fd(parse, p[1]);
		free (line);
		free (parse);
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
		return;
	if (cmd->type == EXEC)
		return;
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
