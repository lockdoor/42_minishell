/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 10:09:49 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/19 07:43:38 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_build_in(char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = ft_strlen(str);
	return (!ft_strncmp(str, "echo", len)
		|| !ft_strncmp(str, "cd", len)
		|| !ft_strncmp(str, "pwd", len)
		|| !ft_strncmp(str, "export", len)
		|| !ft_strncmp(str, "unset", len)
		|| !ft_strncmp(str, "env", len)
		|| !ft_strncmp(str, "exit", len));
}

int	run_build_in(char **argv)
{
	size_t	len;

	len = ft_strlen(argv[0]);
	if (!ft_strncmp(argv[0], "echo", len))
		return (echo(argv));
	else
		printf("%s: Build_in is inconstruction\n", argv[0]);
	return (0);
}

void	run_exec(t_cmd *cmd, t_shell *sh)
{
	t_exec	*exec;
	char	**argv;
	int		exit_code;

	exec = (t_exec *)cmd;
	if (exec->argv[0] == NULL)
	{
		free_shell (sh);
		exit (0);		
	}
	/* parse variable before use argv */
	argv = ft_parser(exec->argv, sh);
	if (argv == NULL)
	{
		free_shell (sh);
		exit (0);
	}
	if (is_build_in(argv[0]))
	{
		exit_code = run_build_in(argv);
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
