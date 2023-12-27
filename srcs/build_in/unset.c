/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 08:48:44 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/27 06:42:15 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*rm_node(t_list *lst, char *argv)
{
	t_env	*env;
	t_list	*next;

	if (!lst)
		return (NULL);
	env = (t_env *)lst->content;
	if (!ft_strncmp(env->name, argv, -1))
	{
		next = lst->next;
		free_env (env);
		free (lst);
		return (next);
	}
	lst->next = rm_node(lst->next, argv);
	return (lst);
}

int	ft_unset(char **argv, t_shell *sh)
{
	int		i;

	i = 0;
	while (argv[++i])
		sh->env = rm_node(sh->env, argv[i]);
	return (0);
}
