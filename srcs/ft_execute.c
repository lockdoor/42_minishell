/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 07:11:17 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/17 08:20:28 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_make_path(t_list *lst)
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

void ft_free_split(char **sp)
{
	int	i;

	i = -1;
	while (sp[++i])
		free(sp[i]);
	free(sp);
}

char	*ft_parse_cmd_2(char *cmd, char **path)
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
			free (cmd);
			ft_free_split(path);
			return (NULL);
		}

		// debug
		// printf ("ft_parse_cmd_2: %s\n", tmp);
		
		if (access(tmp, F_OK) == 0)
		{
			free (cmd);
			ft_free_split(path);
			return (tmp);
		}
		free (tmp);
	}
	ft_free_split(path);
	ft_putstr_fd (cmd + 1, 2);
	ft_putendl_fd (": command not found", 2);
	free (cmd);
	return (NULL);
}

char	*ft_parse_cmd(char	*cmd, t_list *env)
{
	char	**path;
	char	*tmp;

	tmp = ft_strjoin("/", cmd);
	if (!tmp)
	{
		perror ("ft_parse_cmd");
		return (NULL);
	}
	path = ft_make_path(env);
	if (!path)
	{
		free (tmp);
		return (NULL);
	}
	// debug
	// printf ("ft_parse_cmd: %s\n", cmd);
	
	return (ft_parse_cmd_2(tmp, path));
}

void	ft_execute(t_cmd *cmd, t_shell *sh)
{
	t_exec	*exec;
	char	*parse_cmd;
	char	*argv[3];

	if (!cmd)
		exit (0);
	exec = (t_exec *)cmd;
	parse_cmd = ft_parse_cmd(*exec->argv, sh->env);
	if (!parse_cmd)
	{
		free_shell(sh);
		exit (1);
	}
	if (execve(parse_cmd, exec->argv, NULL))
	{
		if (errno == ENOEXEC)
		{
			argv[0] = "/bin/bash";
			argv[1] = *argv;
			argv[2] = NULL;
			execve ("/bin/bash", argv, NULL);
		}
		perror (*exec->argv);
		free (parse_cmd);
		free_shell (sh);
		// px_free_pipex (pipex);
		if (errno == EACCES)
			exit (126);
		else
			exit (127);
	}
	// exit (1);
}
