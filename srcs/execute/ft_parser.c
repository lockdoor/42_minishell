/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:26:55 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/17 16:00:13 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	argv_len(char **argv)
{
	int	i;

	i = -1;
	while (argv[i])
		i++ ;
	return (i);
}

char	**error_parse_argv(char **argv, int i)
{
	while (i)
		free (argv[i--]);
	free (argv);
	return (NULL);
}

char	**ft_parser(char **argv, t_shell *sh)
{
	int		i;
	char	**parse_argv;

	parse_argv = (char **)malloc(sizeof(char *) * (argv_len(argv) + 1));
	i = -1;
	while (argv[++i])
	{
		if (ft_strchr(argv[i], '\'') || ft_strchr(argv[i], '"')
			|| ft_strchr(argv[i], '$'))
			parse_argv[i] = parse_token(argv[i], sh);
		else
			parse_argv[i] = ft_strdup(argv[i]);
		if (!parse_argv[i])
			return (error_parse_argv(parse_argv, i));
	}
	return (parse_argv);
}

char	*parse_token(char *s, t_shell *sh)
{
	char	*result;
	char	*t;
	char	*(*func)(char **, t_shell *);

	result = ft_strdup("");
	while (*s && result)
	{
		if (*s == '$')
			func = &parse_var;
		else if (*s == '\'')
			func = &parse_qoute;
		else if (*s == '"')
			func = &parse_db_qoute;
		else
			func = &get_word;
		t = func(&s, sh);
		if (!t)
		{
			free (result);
			return (NULL);
		}
		result = join_free(result, t);
	}
	return (result);
}

char	*join_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free (s1);
	free (s2);
	if (!result)
		perror ("join_free");
	return (result);
}

char	*get_env(char *name, t_shell *sh)
{
	size_t	len;
	t_env	*env;
	t_list	*lstenv;

	lstenv = sh->env;
	len = ft_strlen(name);
	while (lstenv)
	{
		env = (t_env *) lstenv->content;
		if (ft_strncmp(name, env->name, len) == 0)
			break ;
		lstenv = lstenv->next;
	}
	free (name);
	if (!lstenv)
		return (ft_strdup(""));
	env = (t_env *) lstenv->content;
	return (ft_strdup(env->value));
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