/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:26:15 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/15 07:07:41 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char	*line;
	t_cmd	*cmd;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break;
		// showtoken (line);
		// parsecmd (line);
		cmd = parser (line);
		if (cmd)
		{
			debug_parser (cmd);
			free_cmd (cmd);
		}
		free (line);
	}
	free (line);
	return (0);
}
