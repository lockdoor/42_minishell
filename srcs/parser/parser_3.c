/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:57:06 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/26 15:21:43 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* use this parser in child process only */
int	fd_heredoc(char **q)
{
	char	*limiter;
	int		p[2];
	char	*line;

	if (pipe(p))
	{
		perror("fd_heredoc");
		return (-1);
	}
	limiter = ft_substr(q[0], 0, q[1] - q[0]);
	if (!limiter)
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
		ft_putstr_fd(line, p[1]);
		free (line);
	}
	ft_putstr_fd("\n", p[1]);
	free (line);
	free (limiter);
	close (p[1]);
	return (p[0]);
}

t_cmd	*token_error(t_cmd *cmd, char *s)
{
	if (s)
		ft_putendl_fd (s, 2);
	free_cmd (cmd);
	return (NULL);
}
