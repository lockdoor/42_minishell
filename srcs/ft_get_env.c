/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:02:45 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/28 07:46:49 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*ft_set_env_2(char *s, t_env *env);

static void	get_env_error(t_env *env, t_list **lst)
{
	free_env(env);
	ft_lstclear(lst, &free_env);
	perror ("ft_get_env");
}

t_list	*ft_get_env(char **environment)
{
	t_list	*lst;
	t_list	*new;
	t_env	*env;
	int		i;

	i = -1;
	lst = NULL;
	while (environment[++i])
	{
		env = ft_set_env(environment[i]);
		if (!env)
		{
			ft_lstclear(&lst, &free_env);
			break ;
		}
		new = ft_lstnew(env);
		if (!new)
		{
			get_env_error(env, &lst);
			break ;
		}
		ft_lstadd_back(&lst, new);
	}
	return (lst);
}

t_env	*ft_set_env(char *s)
{
	t_env	*env;

	env = (t_env *) ft_calloc (1, sizeof(t_env));
	if (!env)
	{
		perror ("ft_set_env");
		return (NULL);
	}
	return (ft_set_env_2(s, env));
}

static t_env	*ft_set_env_2(char *s, t_env *env)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++ ;
	env->name = ft_substr(s, 0, i);
	if (!env->name)
	{
		free (env);
		perror ("ft_set_env_2");
		return (NULL);
	}
	if (s[i] == '=')
	{
		s = &s[++i];
		env->value = ft_strdup(s);
		if (!env->value)
		{
			free (env->name);
			free (env);
			perror ("ft_set_env_2");
			return (NULL);
		}
	}
	return (env);
}
