/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 13:55:24 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/22 08:52:42 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_command(char *s, t_shell *sh)
{
	perror (s);
	free_shell(sh);
	exit (EXIT_FAILURE);
}

static void	redirect_input(char *file, t_shell *sh)
{
	int	fd;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit_command(file, sh);

	// debug
	// printf("redirect_input: fd: %d\n", fd);
	
	dup2 (fd, STDIN_FILENO);
	close (fd);
}

static void	redirect_output(char *file, t_shell *sh)
{
	int	fd;

	fd = open(file, O_WRONLY|O_CREAT|O_TRUNC, 0644);
	if (fd == -1)
	exit_command(file, sh);
	dup2 (fd, STDOUT_FILENO);
	close (fd);
}

static void	redirect_output_appand(char *file, t_shell *sh)
{
	int	fd;

	fd = open (file, O_WRONLY|O_CREAT|O_APPEND, 0644);
	if (fd == -1)
	exit_command(file, sh);
	dup2 (fd, STDOUT_FILENO);
	close (fd);
}

static void	redirect_input_heredoc(int fd)
{
	// debug
	printf("redirect_input_heredoc: fd: %d\n", fd);
	
	if (dup2(fd, STDIN_FILENO))
	{
		perror ("redirect_input_heredoc");
	}
	close (fd);
}

void	run_redir(t_cmd *cmd, t_shell *sh)
{
	t_redir	*redir;
	char	*file;

	redir = (t_redir *)cmd;
	/* parse variable before use filename */
	file = parse_token(redir->file, sh);
	if (!file)
		exit_command("run_redir", sh);
	// file = redir->file;
	if (redir->mode == '<')
		redirect_input(file, sh);
	else if (redir->mode == '>')
		redirect_output(file, sh);
	else if (redir->mode == '+')
		redirect_output_appand(file, sh);
	else if (redir->mode == 'h')
		redirect_input_heredoc(redir->fd);
	free (file);
	runcmd(redir->cmd, sh);
}
