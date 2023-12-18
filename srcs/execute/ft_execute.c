/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 07:11:17 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/18 16:56:48 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute(char **argvs, t_shell *sh)
{
	// t_exec	*exec;
	char	*parse_cmd;
	char	*argv[3];

	if (!argvs)
		exit (0);
	// exec = (t_exec *)cmd;
	parse_cmd = ft_parse_cmd(*argvs, sh->env);
	if (!parse_cmd)
	{
		free_split(argvs);
		free_shell(sh);
		exit (1);
	}
	if (execve(parse_cmd, argvs, NULL))
	{
		if (errno == ENOEXEC)
		{
			argv[0] = "/bin/bash";
			argv[1] = *argv;
			argv[2] = NULL;
			execve ("/bin/bash", argv, NULL);
		}
		perror (parse_cmd);
		free_split(argvs);
		free (parse_cmd);
		free_shell (sh);
		if (errno == EACCES)
			exit (126);
		else
			exit (127);
	}
}
