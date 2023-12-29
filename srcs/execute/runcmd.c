/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 10:09:49 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/29 08:11:12 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_build_in(char *str)
{
	if (!str)
		return (0);
	return (!ft_strncmp(str, "echo", -1)
		|| !ft_strncmp(str, "cd", -1)
		|| !ft_strncmp(str, "pwd", -1)
		|| !ft_strncmp(str, "export", -1)
		|| !ft_strncmp(str, "unset", -1)
		|| !ft_strncmp(str, "env", -1)
		|| !ft_strncmp(str, "exit", -1));
}

int	run_build_in(char **argv, t_shell *sh)
{
	if (!ft_strncmp(argv[0], "echo", -1))
		return (echo(argv));
	else if (!ft_strncmp(argv[0], "exit", -1))
		return (ft_exit(argv, sh));
	else if (!ft_strncmp(argv[0], "env", -1))
		return (ft_env(argv, sh));
	else if (!ft_strncmp(argv[0], "unset", -1))
		return (ft_unset(argv, sh));
	else if (!ft_strncmp(argv[0], "pwd", -1))
		return (ft_pwd());
	else if (!ft_strncmp(argv[0], "export", -1))
		return (ft_export(argv, sh));
	else if (!ft_strncmp(argv[0], "cd", -1))
		return (ft_cd(argv, sh));
	return (0);
}

// debug
// void	print_split(char **str)
// {
// 	int i;

// 	i = -1;
// 	while (str[++i])
// 		printf ("%s\n", str[i]);
// }

void	run_exec(t_cmd *cmd, t_shell *sh)
{
	t_exec	*exec;
	char	**argv;
	int		exit_code;

	exec = (t_exec *)cmd;
	argv = ft_parser(exec->argv, sh);
	if (argv == NULL)
	{
		free_shell (sh);
		exit (EXIT_FAILURE);
	}
	if (is_build_in(argv[0]))
	{
		exit_code = run_build_in(argv, sh);
		free_split (argv);
		free_shell (sh);
		exit (exit_code);
	}
	else
		ft_execute (argv, sh);
	exit (0);
}

void	runcmd(t_cmd *cmd, t_shell *sh)
{
	if (!cmd)
		exit (0);
	else if (cmd->type == EXEC)
		run_exec(cmd, sh);
	else if (cmd->type == REDIR)
		run_redir(cmd, sh);
	else if (cmd->type == PIPE)
		run_pipe(cmd, sh);
}
