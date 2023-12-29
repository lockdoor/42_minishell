/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 11:32:05 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/29 12:43:34 by pnamnil          ###   ########.fr       */
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

static char	*ft_atoi_2_h(const char *str, int *sign)
{
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++ ;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			*sign *= -1;
		str++ ;
	}
	return ((char *) str);
}

static int	ft_atoi_2(const char *str, int *dst)
{
	u_int64_t	n;
	int			sign;

	n = 0;
	sign = 1;
	str = ft_atoi_2_h (str, &sign);
	if (!ft_isdigit(*str))
		return (FALSE);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (FALSE);
		n = (n * 10) + (*str - '0');
		if ((sign == -1 && n - 1 > LONG_MAX) || (sign == 1 && n > LONG_MAX))
			return (FALSE);
		str++ ;
	}
	*dst = n * sign;
	return (TRUE);
}

int	ft_exit(char **argv, t_shell *sh)
{
	int	len;
	int	status;

	len = argv_len(argv);
	ft_putendl_fd("exit", 2);
	sh->exit = TRUE;
	if (len == 1)
		return (0);
	if (len == 2)
	{
		if (!ft_atoi_2(argv[1], &status))
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(argv[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (255);
		}
		return (status);
	}
	sh->exit = FALSE;
	ft_putendl_fd("exit: too many arguments", 2);
	return (EXIT_FAILURE);
}
