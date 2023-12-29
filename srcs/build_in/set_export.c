/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 07:26:41 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/29 08:06:03 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_token_error(char *s)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(s, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	free (s);
	return (EXIT_FAILURE);
}

static int	found_env(t_list *lst, t_env *env)
{
	t_env	*oldenv;

	while (lst)
	{
		oldenv = (t_env *) lst->content;
		if (!ft_strncmp(oldenv->name, env->name, -1))
		{
			free_env(oldenv);
			lst->content = env;
			return (TRUE);
		}
		lst = lst->next;
	}
	return (FALSE);
}

static int	check_variable_name(char *s)
{
	if (!ft_isalpha(*s) && *s != '_')
		return (FALSE);
	while (*s && *s != '=')
	{
		if (ft_isalnum(*s) || *s == '_')
			s++ ;
		else
			return (FALSE);
	}
	return (*s == 0 || *s == '=');
}

int	set_export(char *argv, t_shell *sh)
{
	char	*parse;
	t_env	*env;
	t_list	*new;

	parse = parse_token(argv, sh);
	if (!parse)
		return (EXIT_FAILURE);
	if (!check_variable_name(parse))
		return (export_token_error(parse));
	env = ft_set_env(parse);
	free (parse);
	if (!env)
		return (EXIT_FAILURE);
	if (!found_env(sh->env, env))
	{
		new = ft_lstnew((void *)env);
		if (!new)
		{
			free_env(env);
			return (EXIT_FAILURE);
		}
		ft_lstadd_back(&sh->env, new);
	}
	return (0);
}

int	set_exports(char **argv, t_shell *sh)
{
	int		i;

	i = 0;
	while (argv[++i])
	{
		if (set_export(argv[i], sh))
			return (EXIT_FAILURE);
	}
	return (0);
}
