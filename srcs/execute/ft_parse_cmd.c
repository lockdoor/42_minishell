/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 10:41:04 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/26 11:14:51 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* useful for other funtion */
t_env	*find_env(t_list *lst, char *s)
{
	t_env	*env;

	while (lst)
	{
		env = (t_env *)lst->content;
		if (!ft_strncmp(s, env->name, -1))
			return (env);
		lst = lst->next;
	}
	return (NULL);
}

static char	**ft_make_path(t_list *lst)
{
	t_env	*env;
	char	**path;

	env = find_env(lst, "PATH");
	if (!env)
		return (NULL);
	path = ft_split(env->value, ':');
	if (!path)
	{
		perror("ft_make_path");
		return (NULL);
	}
	return (path);
}

static void	free_cmd_path(char *cmd, char **path)
{
	free (cmd);
	free_split(path);
}

static char	*ft_parse_cmd_2(char *cmd, char **path)
{
	char	*tmp;
	int		i;

	i = -1;
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], cmd);
		if (!tmp)
		{
			perror ("ft_parse_cmd");
			free_cmd_path (cmd, path);
			return (NULL);
		}
		if (access(tmp, F_OK) == 0)
		{
			free_cmd_path (cmd, path);
			return (tmp);
		}
		free (tmp);
	}
	ft_putstr_fd (cmd + 1, 2);
	ft_putendl_fd (": command not found", 2);
	free_cmd_path (cmd, path);
	return (NULL);
}

char	*ft_parse_cmd(char	*cmd, t_list *env)
{
	char	**path;
	char	*tmp;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup (cmd));
	tmp = ft_strjoin("/", cmd);
	if (!tmp)
	{
		perror ("ft_parse_cmd");
		return (NULL);
	}
	path = ft_make_path(env);
	// if (!path)
	// {
	// 	free (tmp);
	// 	return (NULL);
	// }
	if (!path || !*path)
	{
		return (ft_strdup(cmd));
	}
	return (ft_parse_cmd_2(tmp, path));
}
