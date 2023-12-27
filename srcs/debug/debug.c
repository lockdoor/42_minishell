/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:24:22 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/27 06:51:40 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* use this for check line */
int	showtoken(char	*line)
{
	char	*ps;
	char	*es;
	char	*q;
	char	*eq;
	int		type;

	ps = line;
	es = ft_strchr(ps, 0);
	type = 1;
	while (type)
	{
		type = gettoken(&ps, es, &q, &eq);
		if (type == -1)
			return (-1);
		write (1, "type: ", 7);
		write (1, &type, 1);
		write (1, ", ", 2);
		write (1, "char: ", 7);
		write (1, q, eq - q);
		write (1, "\n", 1);
	}
	return (0);
}
