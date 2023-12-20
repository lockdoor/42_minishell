/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 10:08:51 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/20 06:17:45 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_qoute(char **str, t_shell *sh)
{
	char	*t;
	char	*s;

	(void) sh;
	s = *str;
	s++ ;
	while (*s && *s != '\'')
		s++ ;
	t = ft_substr(*str, 1, s - *str - 1);
	*str = ++s;
	return (t);
}

char	*parse_var(char **str, t_shell *sh)
{
	char	*s;
	char	*var;

	s = *str;
	s++ ;
	while (*s != '\0' && *s != '$' && *s != ' '
		&& *s != '\'' && *s != '"' && *s != '?')
		s++ ;
	if (*s == '?')
	{
		*str = ++s;
		return (ft_itoa(sh->exit_code));
	}
	var = ft_substr(*str, 1, s - *str - 1);
	*str = s;
	if (!var)
		return (NULL);
	return (get_env(var, sh));
}

char	*parse_db_qoute(char **str, t_shell *sh)
{
	char	*result;
	char	*s;
	char	*t;

	s = *str;
	result = ft_strdup("");
	*str = ++s;
	while (*s && *s != '"' && result)
	{
		if (*s == '$')
		{
			t = ft_substr(*str, 0, s - *str);
			if (!t)
			{
				free (result);
				return (NULL);
			}
			result = join_free (result, t);
			t = parse_var(&s, sh);
			if (!t)
			{
				free (result);
				return (NULL);
			}
			result = join_free (result, t);
			*str = ++s;
		}
		s++ ;
	}
	t = ft_substr(*str, 0, s - *str);
	if (!t)
	{
		free (result);
		return (NULL);
	}
	result = join_free(result, t);
	*str = ++s;
	return (result);
}
