/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_non_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 08:17:52 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/22 08:55:15 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	runredir_non_fork(t_redir *redir, t_shell *sh)
{
	char	*file;
	int		fd;

	file = parse_token(redir->file, sh);
	if (!file)
		return (EXIT_FAILURE);
	if (redir->mode == '<')
		fd = open(file, O_RDONLY);
	else if (redir->mode == '>')
		fd = open(file, O_WRONLY|O_CREAT|O_TRUNC, 0644);
	else if (redir->mode == '+')
		fd = open(file, O_WRONLY|O_CREAT|O_APPEND, 0644);
	else
		fd = redir->fd;
	
	// debug
	// printf ("runredir_non_fork: fd: %d\n", fd);
	
	if (fd == -1)
	{
		perror (file);
		free (file);
		return (EXIT_FAILURE);
	}
	free (file);
	close (fd);
	return (0);
}

int	run_build_in_non_fork(t_exec *cmd, t_shell *sh)
{
	char	**argv;
	size_t	len;

	argv = ft_parser(cmd->argv, sh);
	if (argv == NULL)
		return (EXIT_FAILURE);
	len = ft_strlen(argv[0]);
	if (ft_strncmp(argv[0], "exit", len))
	{
		printf("%s: non_fork Build_in is inconstruction\n", argv[0]);
		return (0);
	}
	else if (ft_strncmp(argv[0], "cd", len))
	{
		printf("%s: non_fork Build_in is inconstruction\n", argv[0]);
		return (0);
	}
	else if (ft_strncmp(argv[0], "export", len))
	{
		printf("%s: non_fork Build_in is inconstruction\n", argv[0]);
		return (0);
	}
	else if (ft_strncmp(argv[0], "unset", len))
	{
		printf("%s: non_fork Build_in is inconstruction\n", argv[0]);
		return (0);
	}
	else
	{
		printf("%s: non_fork Build_in must fork\n", argv[0]);
		return (EXIT_FAILURE);
	}
}

int	runcmd_non_fork(t_cmd *cmd, t_shell *sh)
{
	t_redir	*redir;
	t_exec	*exec;

	// debug
	// printf("cmd->type: %d\n", cmd->type);

	if (cmd->type == REDIR)
	{
		redir = (t_redir *)cmd;
		
		// debug
		// printf("fd: %c\n", redir->mode);
		
		if (runredir_non_fork(redir, sh))
			return (EXIT_FAILURE);
		return (runcmd_non_fork(redir->cmd, sh));	
	}
	else if (cmd->type == EXEC)
	{
		exec = (t_exec *)cmd;
		return (run_build_in_non_fork(exec, sh));
	}
	return (EXIT_FAILURE);
}
