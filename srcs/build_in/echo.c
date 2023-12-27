/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 06:42:42 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/27 06:39:58 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char **argv)
{
	int		i;
	int		newline;

	i = 1;
	newline = 1;
	if (!argv[i])
	{
		printf ("\n");
		return (0);
	}
	if (!ft_strncmp(argv[i], "-n", -1))
	{
		i++;
		newline = 0;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1] != NULL)
			printf(" ");
		i++ ;
	}
	if (newline)
		printf ("\n");
	return (0);
}
