/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:39:13 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/26 07:16:00 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd *cmd)
{
	t_redir	*redir;
	t_pipe	*pipe;

	if (!cmd)
		return ;
	if (cmd->type == EXEC)
	{
		free (cmd);
		cmd = NULL;
	}
	else if (cmd->type == REDIR)
	{
		redir = (t_redir *)cmd;
		if (redir->mode == 'h')
			close(redir->fd);
		free_cmd((t_cmd *)redir->cmd);
		free (cmd);
		cmd = NULL;
	}
	else if (cmd->type == PIPE)
	{
		pipe = (t_pipe *)cmd;
		free_cmd(pipe->left);
		free_cmd(pipe->right);
		free (cmd);
		cmd = NULL;
	}
}

void	free_env(void *data)
{
	t_env	*env;

	if (!data)
		return ;
	env = (t_env *) data;
	free (env->name);
	if (env->value)
		free (env->value);
	free (env);
}

void	free_shell(t_shell *sh)
{
	free_cmd(sh->cmd);
	ft_lstclear(&sh->env, &free_env);
	free (sh);
}

void	free_split(char **sp)
{
	int	i;

	i = -1;
	while (sp[++i])
		free(sp[i]);
	free(sp);
}
