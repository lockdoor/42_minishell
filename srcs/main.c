/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:26:15 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/27 10:13:14 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* global variable for get signal status */
int	g_signal;

int	exec_command(t_cmd *cmd, t_shell *sh)
{
	int	id;
	int	status;

	id = fork_1("exec_command", sh);
	if (id == 0)
	{
		--g_signal ;
		runcmd(cmd, sh);
	}
	wait(&status);
	return (WEXITSTATUS(status));
}

void	sigint_handler(int signum)
{
	if (!g_signal)
	{
		if (signum == SIGINT)
			ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (g_signal == -1)
	{
		if (signum == SIGINT)
			ft_putendl_fd("^C", STDOUT_FILENO);
		if (signum == SIGQUIT)
			ft_putendl_fd("^\\Quit: 3", STDOUT_FILENO);
		g_signal = signum;
	}
}

void	main_execute(t_shell *sh)
{
	parse_here(sh->cmd, sh);
	if (is_build_in_non_fork(sh->cmd, sh))
		sh->exit_code = runcmd_non_fork(sh->cmd, sh);
	else
		sh->exit_code = exec_command(sh->cmd, sh);
	if (g_signal == SIGINT)
		sh->exit_code = 130;
	if (g_signal == SIGQUIT)
		sh->exit_code = 131;
	set_last_cmd(sh->cmd, sh);
	free_cmd (sh->cmd);
}

int	main(void)
{
	char	*line;
	t_shell	*sh;
	int		status;

	sh = init_shell();
	while (!sh->exit)
	{
		g_signal = 0;
		line = readline("$ ");
		if (!line)
			break ;
		add_history(line);
		sh->cmd = parser(line);
		--g_signal ;
		if (sh->cmd)
			main_execute(sh);
		free (line);
	}
	ft_lstclear(&sh->env, &free_env);
	status = sh->exit_code;
	free (sh);
	return (status);
}
