/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gettoken.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:25:48 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/27 11:24:56 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	token_symbols(char **ps)
{
	char	*s;
	int		ret;

	s = *ps;
	ret = *s;
	s++ ;
	if (ret == '<' && *s == '<')
	{
		s++ ;
		ret = 'h';
	}
	else if (ret == '>' && *s == '>')
	{
		s++ ;
		ret = '+';
	}
	*ps = s;
	return (ret);
}

static int	qoute(char **ps, int q)
{
	char	*s;

	s = *ps;
	s++ ;
	while (*s && *s != q)
		s++ ;
	if (*s != q)
		return (1);
	*ps = s;
	return (0);
}

static int	token_string(char **ps)
{
	char	*s;

	s = *ps;
	while (*s && !ft_strchr(WHITESPACE, *s) && !ft_strchr(SYMBOLS, *s))
	{
		if (*s == '\'' || *s == '"')
		{
			if (qoute(&s, *s))
			{
				ft_putendl_fd ("not found end qoute", 2);
				return (-1);
			}
		}
		s++ ;
	}
	*ps = s;
	return ('a');
}

int	peek(char **ps, char *es, char *tok)
{
	char	*s;

	s = *ps;
	while (s < es && ft_strchr(WHITESPACE, *s))
		s++ ;
	*ps = s;
	return (*s && ft_strchr(tok, *s));
}

int	gettoken(char **ps, char *es, char **q, char **eq)
{
	char	*s;
	int		ret;

	s = *ps;
	while (s < es && ft_strchr(WHITESPACE, *s))
		s++;
	if (q)
		*q = s;
	ret = *s;
	if (ft_strchr(SYMBOLS, *s))
		ret = token_symbols(&s);
	else if (ret)
		ret = token_string(&s);
	if (eq)
		*eq = s;
	*ps = s;
	return (ret);
}
