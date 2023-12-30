/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 10:08:51 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/30 07:32:25 by pnamnil          ###   ########.fr       */
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
		if (*s == '?' || ft_isdigit(*s))
		{
			if (*s == '?')
				var = ft_itoa(sh->exit_code);
			else
				var = ft_strdup("");
			*str = ++s;
			return (var);
		}
		return (ft_strdup("$"));
	}
	while (ft_isalpha(*s) || *s == '_')
		s++ ;
	var = ft_substr(*str, 0, s - *str);
	*str = s;
	return (get_env(var, sh));
}

char	*parse_db_qoute(char **start, t_shell *sh)
{
	char	*result;
	char	*s;

	s = *start;
	result = ft_strdup("");
	*start = ++s;
	while (*s && *s != '"' && result)
	{
		if (*s == '$')
		{
			if (s != *start)
				result = join_free (result, ft_substr(*start, 0, s - *start));
			result = join_free (result, parse_var(&s, sh));
			*start = s;
		}
		else
			s++ ;
	}
	result = join_free(result, ft_substr(*start, 0, s - *start));
	if (*s == '"')
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
