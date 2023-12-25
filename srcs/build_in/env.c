/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 06:24:27 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/25 08:30:15 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **argv, t_shell *sh)
{
	t_list	*envlst;
	t_env	*env;

	if (argv_len(argv) > 1)
	{
		ft_putendl_fd("env: not handle any argument\n", 2);
		return (EXIT_FAILURE);
	}
	envlst = sh->env;
	while (envlst)
	{
		env = (t_env *) envlst->content;
		if (env->env)
			printf ("%s=%s\n", env->name, env->value);
		envlst = envlst->next;
	}
	return (0);
}
