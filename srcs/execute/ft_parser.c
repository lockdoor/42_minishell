/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:26:55 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/29 16:44:30 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**error_parse_argv(char **argv, int i)
{
	while (i)
		free (argv[--i]);
	free (argv);
	return (NULL);
}

char	**ft_parser(char **argv, t_shell *sh)
{
	int		i;
	int		j;
	char	**parse_argv;

	parse_argv = (char **)malloc(sizeof(char *) * (argv_len(argv) + 1));
	if (!parse_argv)
		return (NULL);
	i = -1;
	j = 0;
	while (argv[++i])
	{
		if (ft_strchr(argv[i], '\'') || ft_strchr(argv[i], '"')
			|| ft_strchr(argv[i], '$'))
			parse_argv[j] = parse_token(argv[i], sh);
		else
			parse_argv[j] = ft_strdup(argv[i]);
		if (!parse_argv[j])
			return (error_parse_argv(parse_argv, i));
		if (parse_argv[j][0] == 0)
			free (parse_argv[j]);
		else
			j++ ;
	}
	parse_argv[j] = NULL;
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

char	*join_free(char *s_1, char *s_2)
{
	char	*result;

	if (!s_2 && *s_2 == 0)
	{
		if (s_2)
			free (s_2);
		return (s_1);
	}
	result = ft_strjoin(s_1, s_2);
	free (s_1);
	free (s_2);
	if (!result)
		perror ("join_free");
	return (result);
}

char	*get_env(char *name, t_shell *sh)
{
	t_env	*env;
	t_list	*lstenv;

	if (!name)
		return (NULL);
	lstenv = sh->env;
	while (lstenv)
	{
		env = (t_env *) lstenv->content;
		if (ft_strncmp(name, env->name, -1) == 0)
			break ;
		lstenv = lstenv->next;
	}
	free (name);
	if (!lstenv)
		return (ft_strdup(""));
	env = (t_env *) lstenv->content;
	return (ft_strdup(env->value));
}
