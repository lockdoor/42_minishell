/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_non_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:22:02 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/22 08:50:00 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	build_in_list(char *argv, char *eargv)
int	build_in_list(char *cmd)
{
	size_t	len;
	// char	*cmd;

	// if (!argv)
	// 	return (0);
	// cmd = ft_substr(argv, 0, eargv - argv);
	if (!cmd)
	{
		perror ("build_in_list");
		return (0);
	}
	len = ft_strlen(cmd);
	if (len == 0)
		return (0);
	if (!ft_strncmp(cmd, "exit", len)
		|| !ft_strncmp(cmd, "cd", len)
		|| !ft_strncmp(cmd, "export", len)
		|| !ft_strncmp(cmd, "unset", len))
	{
		printf ("build_in_list: cmd: %s\n", cmd);
		// free (cmd);
		return (1);
	}
	// free (cmd);
	return (0);
}

int	is_build_in_non_fork(t_cmd *cmd)
{
	t_redir	*redir;
	t_exec	*exec;
	// int		ret;

	if (!cmd)
		return (0);
	if (cmd->type == REDIR)
	{
		redir = (t_redir *)cmd;
		return (is_build_in_non_fork(redir->cmd));
		// ret = is_build_in_non_fork(redir->cmd);
		// if (!ret && redir->mode == 'h')
		// 	close (redir->fd);
		// return (ret);		
	}
	else if (cmd->type == EXEC)
	{
		exec = (t_exec *)cmd;
		// return (build_in_list(exec->argv[0], exec->eargv[0]));
		return (build_in_list(exec->argv[0]));
	}
	return (0);
}

/*
t_cmd	*pre_parse_pipe(char **ps, char *es)
{
	t_cmd	*cmd;

	cmd = parse_exec(ps, es);
	if (cmd == NULL)
		return (NULL);
	if (peek(ps, es, "|"))
	{
		free_cmd(cmd);
		return (NULL);
	}
	return (cmd);
}
*/
/*
t_cmd	*is_non_fork(char *line)
{
	char	*es;
	t_cmd	*cmd;

	es = ft_strchr(line, 0);
	cmd = pre_parse_pipe(&line, es);
	if (is_build_in_non_fork(cmd))
	{
		null_terminate(cmd);
		return (cmd);
	}
	
	// debug
	printf ("is_non_fork: must fork\n");
	
	free_cmd(cmd);
	return (NULL);
}
*/