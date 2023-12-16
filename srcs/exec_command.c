/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:44:02 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/15 13:59:43 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	px_make_path(t_pipex *pipex, char **envp)
{
	while (*envp && ft_memcmp(*envp, "PATH=", 5))
		envp++ ;
	if (*envp == NULL)
	{
		pipex->path = NULL;
		return ;
	}
	if (*envp[0] == 0)
	{
		pipex->path = NULL;
		return ;
	}
	pipex->path = ft_split(*envp + 5, ':');
	if (!pipex->path)
	{
		px_exit_error (MALLOC_ERROR, pipex, EXIT_FAILURE);
		return ;
	}
}

/* if not found in path it's exit command not found */
static void	px_join_path(t_pipex *pipex)
{
	char	**path;
	char	*cmd;

	pipex->cmd = ft_strjoin ("/", *pipex->argv);
	if (!pipex->cmd)
		px_exit_error (MALLOC_ERROR, pipex, EXIT_FAILURE);
	path = pipex->path;
	while (*path)
	{
		cmd = ft_strjoin (*path, pipex->cmd);
		if (!cmd)
			px_exit_error (MALLOC_ERROR, pipex, EXIT_FAILURE);
		if (access(cmd, F_OK) == 0)
		{
			free (pipex->cmd);
			pipex->cmd = cmd;
			return ;
		}
		free (cmd);
		path++ ;
	}
	px_exit_cmd_not_found(*pipex->argv, pipex);
}

/*
**	1.	if no argv in zsh: permission denied, bash: command not found
**	2.	if have path sent this command to execve
**	3	in case no path
**	3.1	if file exited sent this command to execve
**	3.2 if not exited it's error command not found exit: 127
*/

/* if command -eq "" in zsh: permission denied, bash: command not found */

void	px_parse_cmd(t_pipex *pipex, char *argv, char **envp)
{
	pipex->argv = px_split (argv, 32);
	if (!pipex->argv)
		px_exit_error (MALLOC_ERROR, pipex, EXIT_FAILURE);
	if (!*pipex->argv)
		px_exit_cmd_not_found ("", pipex);
	if (ft_strchr(*pipex->argv, '/'))
	{
		pipex->cmd = ft_strdup(*pipex->argv);
		if (!pipex->cmd)
			px_exit_error (MALLOC_ERROR, pipex, EXIT_FAILURE);
		return ;
	}
	px_make_path (pipex, envp);
	if (!pipex->path || !*pipex->path)
	{
		pipex->cmd = ft_strdup(*pipex->argv);
		if (!pipex->cmd)
			px_exit_error (MALLOC_ERROR, pipex, EXIT_FAILURE);
		return ;
	}
	px_join_path (pipex);
}

void	px_execute_cmd(t_pipex *pipex, char **envp)
{
	char	*argv[3];

	if (execve(pipex->cmd, pipex->argv, envp) == -1)
	{
		if (errno == ENOEXEC)
		{
			argv[0] = "/bin/bash";
			argv[1] = pipex->cmd;
			argv[2] = NULL;
			execve ("/bin/bash", argv, envp);
		}
		perror (pipex->cmd);
		px_free_pipex (pipex);
		if (errno == EACCES)
			exit (126);
		else
			exit (127);
	}
}

void	execute_command(char **strs)
{
	
	px_parse_cmd(pipex, argv[3], envp);
	px_execute_cmd (pipex, envp);
}