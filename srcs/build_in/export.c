/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 10:17:21 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/26 07:33:40 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void *dup_env(void *data)
{
	t_env	*env;
	t_env	*envcpy;

	env = (t_env *)data;
	envcpy = ft_calloc(1, sizeof(t_env));
	if (!envcpy)
		return (NULL);
	envcpy->name = ft_strdup(env->name);
	if (!envcpy->name)
	{
		free (envcpy);
		return (NULL);
	}
	if (env->value)
	{
		envcpy->value = ft_strdup(env->value);
		if (!envcpy->value)
		{
			free (envcpy->name);
			free (envcpy);
			return (NULL);
		}
	}
	return ((void *)envcpy);
}

static int	cmp(void *d_1, void *d_2)
{
	t_env	*env_1;
	t_env	*env_2;

	env_1 = (t_env *) d_1;
	env_2 = (t_env *) d_2;
	if (ft_strncmp(env_1->name, env_2->name, -1) > 0)
		return (1);
	return (0);
}

static void	sort_env(t_list *envlst)
{
	int	i;
	int	j;
	t_env	*env;
	t_list	*lst;

	i = ft_lstsize(envlst);
	while (--i)
	{
		j = i;
		lst = envlst;
		while (j-- && lst)
		{
			if (cmp(lst->content, lst->next->content))
			{
				env = lst->content;
				lst->content = lst->next->content;
				lst->next->content = env;
			}				
			lst = lst->next;
		}
	}
}

static int	get_export(t_shell *sh)
{
	t_list	*lst;
	t_list	*envlst;
	t_env	*env;

	envlst = ft_lstmap(sh->env, &dup_env, &free_env);
	if (!envlst)
		return (EXIT_FAILURE);
	sort_env(envlst);
	lst = envlst;
	while (lst)
	{
		env = (t_env *)lst->content;
		if (env->value)
			printf ("declare -x %s=\"%s\"\n", env->name, env->value);
		else
			printf ("declare -x %s\n", env->name);
		lst = lst->next;
	}
	ft_lstclear(&envlst, &free_env);
	return (0);
}

int	ft_export(char **argv, t_shell *sh)
{
	int		len;
	
	len = argv_len(argv);
	if (len == 1)
		return (get_export(sh));
	if (len > 1)
		return (set_exports(argv, sh));
	return (0);
}
