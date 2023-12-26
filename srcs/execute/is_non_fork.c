/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_non_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 08:17:52 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/26 09:02:40 by pnamnil          ###   ########.fr       */
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
	if (redir->mode == '>' || redir->mode == '+')
		dup2 (fd, STDOUT_FILENO);
	close (fd);
	return (0);
}

int	run_build_in_non_fork(t_exec *cmd, t_shell *sh)
{
	char	**argv;
	int		ret;

	argv = ft_parser(cmd->argv, sh);
	if (argv == NULL)
		return (EXIT_FAILURE);

	/* this point can handle last command */
	
	if (!ft_strncmp(argv[0], "exit", -1))
		ret = ft_exit(argv, sh);
	else if (!ft_strncmp(argv[0], "cd", -1))
		ret = ft_cd(argv, sh);
	else if (!ft_strncmp(argv[0], "export", -1))
		ret = ft_export(argv, sh);
	else if (!ft_strncmp(argv[0], "unset", -1))
		ret = ft_unset(argv, sh);
	else
	{
		printf("%s: non_fork Build_in must fork\n", argv[0]);
		ret = 1;
	}
	free_split(argv);
	close (STDOUT_FILENO);
	dup(STDIN_FILENO);
	dup(STDOUT_FILENO);
	return (ret);
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
