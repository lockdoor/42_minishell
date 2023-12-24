/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 11:32:05 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/24 16:45:06 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* 
	- when exit call it print exit to stderr
	- exit get 1 argv only 
		if more then it print exit: too many arguments
		to stderr and not exit then return status 1
	- if argv is non digit such as string 
		it print exit: [argv]: numeric argument required
		to stderr and not exit then 255
	- if success it print exit to stderr
		- if user init status it return WEXITSTATUS(status)
		- return 0;
*/
static int	is_nondigit(char *s)
{
	if (!s)
		return (0);
	while (*s && ft_isdigit(*s))
		s++ ;
	return (*s);
}

int	ft_exit(char **argv, t_shell *sh)
{
	int status;

	status = 0;
	ft_putendl_fd("exit", 2);
	if (argv_len(argv) > 2)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return (EXIT_FAILURE);
	}
	if (is_nondigit(argv[1]))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (255);
	}
	sh->exit = 1;
	if (argv[1])
		status = ft_atoi(argv[1]);
	return (status);
}
