/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:02:45 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/15 14:26:30 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*ft_set_env(char *s);
static t_env	*ft_set_env_2(char *s, t_env *env);

void	ft_free_env(void *data)
{
	t_env	*env;

	env = (t_env *) data;
	free (env->name);
	free (env->value);
	free (env);
}

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
			ft_lstclear(&lst, &ft_free_env);
			break;
		}
		new = ft_lstnew(env);
		if (!new)
		{
			ft_free_env(env);
			ft_lstclear(&lst, &ft_free_env);
			perror ("ft_get_env");
			break ;
		}
		ft_lstadd_back(&lst, new);
	}
	return (lst);
}

static t_env	*ft_set_env(char *s)
{
	t_env	*env;

	env = (t_env *) malloc (sizeof(t_env));
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
	while (s[i] != '=')
		i++ ;
	env->name = ft_substr(s, 0, i);
	if (!env->name)
	{
		free (env);
		perror ("ft_set_env_2");
		return (NULL);
	}
	s = &s[++i];
	env->value = ft_strdup(s);
	if (!env->value)
	{
		free (env->name);
		free (env);
		perror ("ft_set_env_2");
		return (NULL);
	}
	return (env);
}
