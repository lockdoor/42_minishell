/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:02:45 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/25 18:02:13 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*ft_set_env_2(char *s, t_env *env);

t_list	*ft_get_env(void)
{
	t_list	*lst;
	t_list	*new;
	t_env	*env;
	int		i;

	i = -1;
	lst = NULL;
	while (environ[++i])
	{
		env = ft_set_env(environ[i]);
		if (!env)
		{
			ft_lstclear(&lst, &free_env);
			break;
		}
		new = ft_lstnew(env);
		if (!new)
		{
			free_env(env);
			ft_lstclear(&lst, &free_env);
			perror ("ft_get_env");
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
	env->env = TRUE;
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
	if (s[i] == 0)
		env->value = NULL;
	else
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
