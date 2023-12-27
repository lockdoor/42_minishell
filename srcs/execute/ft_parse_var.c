/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 10:08:51 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/27 09:19:14 by pnamnil          ###   ########.fr       */
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

static char	*parse_var_in_db_qoute(char *result, \
	t_shell *sh, char *start, char **str)
{
	char	*t;
	char	*s;

	s = *str;
	t = ft_substr(start, 0, s - start);
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
	*str = s;
	return (result);
}

char	*parse_db_qoute(char **start, t_shell *sh)
{
	char	*result;
	char	*s;
	char	*t;

	s = *start;
	result = ft_strdup("");
	*start = ++s;
	while (*s && *s != '"' && result)
	{
		if (*s == '$')
		{
			result = parse_var_in_db_qoute(result, sh, *start, &s);
			*start = s;
		}
		s++ ;
	}
	t = ft_substr(*start, 0, s - *start);
	if (!t)
	{
		free (result);
		return (NULL);
	}
	result = join_free(result, t);
	*start = ++s;
	return (result);
}

char	*get_word(char **str, t_shell *sh)
{
	char	*s;
	char	*word;

	(void) sh;
	s = *str;
	while (*s != '\0' && *s != '$' && *s != '\'' && *s != '"')
		s++ ;
	word = ft_substr(*str, 0, s - *str);
	*str = s;
	return (word);
}
