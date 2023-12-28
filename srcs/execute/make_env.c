/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 07:57:49 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/28 09:11:59 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_env(t_env *env)
{
	char	*s;
	char	*t;

	t = ft_strjoin(env->name, "=");
	if (!t)
		return (NULL);
	s = ft_strjoin(t, env->value);
	free (t);
	if (!s)
		return (NULL);
	return (s);
}

static char	**free_char_env(char **env, int i)
{
	while (i--)
		free (env[i]);
	free (env);
	return (NULL);
}

// debug
// void	print_split(char **str)
// {
// 	int i;

// 	i = -1;
// 	while (str[++i])
// 		printf ("%s\n", str[i]);
// }

/* only get variable with value */
char	**make_char_env(t_list *lst)
{
	int		i;
	char	**char_env;
	char	*s;
	t_env	*env;

	i = ft_lstsize(lst);
	char_env = (char **) ft_calloc (sizeof(char *), i + 1);
	if (!char_env)
		return (NULL);
	i = 0;
	while (lst)
	{
		env = (t_env *)lst->content;
		if (env->value)
		{
			s = join_env(env);
			if (!s)
				return (free_char_env(char_env, i));
			char_env[i++] = s;
		}
		lst = lst->next;
	}
	return (char_env);
}
