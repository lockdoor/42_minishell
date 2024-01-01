/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 14:43:03 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/01 13:31:24 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_sig(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = sigint_handler;
	sa_quit.sa_handler = sigint_handler;
	sigemptyset (&sa_int.sa_mask);
	sigemptyset (&sa_quit.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sa_quit.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
	{
		perror ("sigaction");
		exit (EXIT_FAILURE);
	}
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
	{
		perror ("sigaction");
		exit (EXIT_FAILURE);
	}
}

static int	minishell_terminal(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
	return (0);
}

static void	set_shell_level(t_shell *sh)
{
	t_env	*env;
	int		level;
	char	*s;

	env = find_env(sh->env, "SHLVL");
	if (!env)
		return ;
	if (!env->value)
		return ;
	level = ft_atoi(env->value);
	level += 1;
	s = ft_itoa(level);
	if (!s)
		return ;
	free (env->value);
	env->value = s;
}

t_shell	*init_shell(char **env, t_shell *sh)
{
	minishell_terminal();
	init_sig();
	ft_memset(sh, 0, sizeof(t_shell));
	sh->env = ft_get_env(env);
	sh->char_env = make_char_env(sh->env);
	set_shell_level(sh);
	if (!sh->env)
	{
		perror ("init_shell cannot get env");
		exit (EXIT_FAILURE);
	}
	return (sh);
}
