/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 10:41:04 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/17 11:26:39 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_make_path(t_list *lst)
{
	t_env	*env;
	char	**path;
	if (!lst)
		return (NULL);
	while (lst)
	{
		env = (t_env *)lst->content;
		if (!ft_strncmp(env->name, "PATH", ft_strlen(env->name)))
		{
			path = ft_split(env->value, ':');
			if (!path)
			{
				perror("ft_make_path");
				return (NULL);
			}
			return (path);
		}
		lst = lst->next;
	}
	return (NULL);
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
