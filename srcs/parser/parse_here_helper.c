/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_here_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 12:57:22 by pnamnil           #+#    #+#             */
/*   Updated: 2024/01/01 13:07:39 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

char	*parse_limiter(char *s, int *should_parse);

int	init_pipe_limiter(int *p, char **lim, char *limiter, int *should_parse)
{
	*lim = parse_limiter(limiter, should_parse);
	if (pipe(p))
	{
		perror("fd_heredoc");
		return (-1);
	}
	if (!*lim)
		return (-1);
	return (0);
}
