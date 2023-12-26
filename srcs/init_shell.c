/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 14:43:03 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/24 14:45:00 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_sig(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	/* set handler funtion */
	sa_int.sa_handler = sigint_handler;
	sa_quit.sa_handler = sigint_handler;

	/* init struct empty */
	sigemptyset (&sa_int.sa_mask);
	sigemptyset (&sa_quit.sa_mask);

	sa_int.sa_flags = SA_RESTART;
	sa_quit.sa_flags = SA_RESTART;

	/* register hangler */
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

t_shell	*init_shell(void)
{
	t_shell	*sh;

	minishell_terminal();
	init_sig();
	
	sh = (t_shell *) malloc (sizeof(t_shell));
	if (!sh)
	{
		perror ("init_shell");
		exit (EXIT_FAILURE);
	}
	ft_memset(sh, 0, sizeof(t_shell));
	sh->env = ft_get_env();
	if (!sh->env)
	{
		free (sh);
		perror ("init_shell cannot get env");
		exit (EXIT_FAILURE);
	}
	return (sh);
}