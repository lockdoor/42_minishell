/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 10:08:51 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/29 08:09:38 by pnamnil          ###   ########.fr       */
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

/* loop if alphanum and under_scholl */
char	*parse_var(char **str, t_shell *sh)
{
	char	*s;
	char	*var;

	s = *str;
	*str = ++s ;
	if (!ft_isalpha(*s) && *s != '_')
	{
		if (*s == 0 || *s == ' ')
			return (ft_strdup("$"));
		if (*s == '?' || ft_isdigit(*s))
		{
			if (*s == '?')
				var = ft_itoa(sh->exit_code);
			else
				var = ft_strdup("");
			*str = ++s;
			return (var);
		}
	}
	while (ft_isalpha(*s) || *s == '_')
		s++ ;
	var = ft_substr(*str, 0, s - *str);
	*str = s;
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
