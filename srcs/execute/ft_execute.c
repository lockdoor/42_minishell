/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 07:11:17 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/17 10:41:24 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	ft_execute(t_cmd *cmd, t_shell *sh)
{
	t_exec	*exec;
	char	*parse_cmd;
	char	*argv[3];

	if (!cmd)
		exit (0);
	exec = (t_exec *)cmd;
	parse_cmd = ft_parse_cmd(*exec->argv, sh->env);
	if (!parse_cmd)
	{
		free_shell(sh);
		exit (1);
	}
	if (execve(parse_cmd, exec->argv, NULL))
	{
		if (errno == ENOEXEC)
		{
			argv[0] = "/bin/bash";
			argv[1] = *argv;
			argv[2] = NULL;
			execve ("/bin/bash", argv, NULL);
		}
		perror (*exec->argv);
		free (parse_cmd);
		free_shell (sh);
		// px_free_pipex (pipex);
		if (errno == EACCES)
			exit (126);
		else
			exit (127);
	}
	// exit (1);
}
