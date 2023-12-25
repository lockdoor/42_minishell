/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 10:03:27 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/25 10:15:47 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	buf[100];

	if (!getcwd(buf, 100))
	{
		perror ("pwd");
		return (EXIT_FAILURE);
	}
	printf("%s\n", buf);
	return (0);
}
