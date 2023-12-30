/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 07:11:17 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/30 10:57:11 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute_try(char *cmd, char **env)
{
	char	*argv[3];

	argv[0] = "/bin/bash";
	argv[1] = cmd;
	argv[2] = NULL;
	execve ("/bin/bash", argv, env);
}

void	execute_source(char *cmd, char **argv, t_shell *sh)
{
	if (!argv[1])
	{
		free_split(argv);
		free_shell(sh);
		free(cmd);
		ft_putendl_fd (".: usage: . filename [arguments]", 2);
		exit(2);
	}
	ft_execute_try (argv[1], sh->char_env);
}

void	execute_error(char *parse_cmd, char **argv, t_shell *sh)
{
	perror (parse_cmd);
	free (parse_cmd);
	free_split(argv);
	free_shell (sh);
	if (errno == EACCES)
		exit (126);
	else
		exit (127);
}

void	ft_execute(char **argv, t_shell *sh)
{
	char	*parse_cmd;

	if (!argv || !argv[0])
		exit (0);
	parse_cmd = ft_parse_cmd(*argv, sh->env);
	if (!parse_cmd)
	{
		free_split(argv);
		free_shell(sh);
		exit (127);
	}
	if (!ft_strncmp(parse_cmd, ".", -1))
		execute_source(parse_cmd, argv, sh);
	if (execve(parse_cmd, argv, sh->char_env))
	{
		if (errno == ENOEXEC)
			ft_execute_try(parse_cmd, sh->char_env);
		execute_error(parse_cmd, argv, sh);
	}
}
