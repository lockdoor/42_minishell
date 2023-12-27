/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:57:06 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/27 09:58:51 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_no_cmd(t_cmd *cmd, char	*s)
{
	t_exec	*exec;

	if (!cmd)
		return (1);
	if (cmd->type == EXEC)
	{
		exec = (t_exec *)cmd;
		if (exec->argv[0] == NULL)
		{
			free_cmd(cmd);
			if (s)
				ft_putendl_fd(s, 2);
			return (1);
		}
	}
	return (0);
}

t_cmd	*token_error(t_cmd *cmd, char *s)
{
	if (s)
		ft_putendl_fd (s, 2);
	free_cmd (cmd);
	return (NULL);
}
