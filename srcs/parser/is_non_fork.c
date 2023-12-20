/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_non_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:22:02 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/20 15:29:33 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*is_non_fork(char *line)
{
	char	*es;
	t_cmd	*cmd;

	es = ft_strchr(line, 0);
	cmd = pre_parse_pipe(&line, es);
}

t_cmd	*pre_parse_pipe(char **ps, char *es)
{
	t_cmd	*cmd;
	t_pipe	*pipe;

	cmd = parse_exec(ps, es);
	if (cmd == NULL)
		return (NULL);
	if (peek(ps, es, "|"))
	{
		free_cmd(cmd);
		return (NULL);
	}
	// debug
	// printf ("parse_pipe: %d, %c\n", **ps, **ps);
	return (cmd);
}