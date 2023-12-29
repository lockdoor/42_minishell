/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 08:44:49 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/29 07:54:35 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	this function read only argv[1]
	if no argv[1] it goto HOME in export
		if not found HOME it print cd: HOME not set then return 1
	if argv[1] == ~ it goto home (not handle for this)
	if argv[1] == .. it up 1 level (not handle for this)
	every time change dir it take current to OLDPWD
	and set PWD with new dir
	if argv[1] == - it back to OLDPWD in export
		it print OLDPWD 1 time
		if not found OLDPWD it print cd: OLDPWD not set then return 1
	if not found path it print stderr: [path]: No such file or directory
	then return 1;
*/
int	error_cd_not_set(char *s)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(s, 2);
	ft_putendl_fd(" not set", 2);
	return (EXIT_FAILURE);
}

int	set_old_pwd(t_shell *sh)
{
	t_env	*pwd;
	char	*env;
	char	cur[100];
	int		m;

	m = 0;
	pwd = find_env(sh->env, "PWD");
	if (!pwd || !pwd->value)
		return (error_cd_not_set("PWD"));
	env = ft_strjoin("OLDPWD=", pwd->value);
	if (!env)
		env = "OLDPWD=";
	else
		m = 1;
	set_export (env, sh);
	if (m)
		free (env);
	ft_strlcpy (cur, "PWD=", 100);
	if (!getcwd(cur + 4, 100))
		perror ("set_old_pwd: getcwd:");
	set_export (cur, sh);
	return (0);
}

int	cd_special(t_shell *sh, char *s)
{
	t_env	*env;

	env = find_env(sh->env, s);
	if (!env)
		return (error_cd_not_set(s));
	if (chdir(env->value))
	{
		perror("cd");
		return (EXIT_FAILURE);
	}
	set_old_pwd(sh);
	return (0);
}

int	cd_normal(t_shell *sh, char *s)
{
	if (chdir(s))
	{
		perror("cd");
		return (EXIT_FAILURE);
	}
	set_old_pwd(sh);
	return (0);
}

int	ft_cd(char **argv, t_shell *sh)
{
	int		len;

	len = argv_len(argv);
	if (len == 1)
		return (cd_special(sh, "HOME"));
	if (len > 1)
	{
		if (!ft_strncmp(argv[1], "-", -1))
			return (cd_special(sh, "OLDPWD"));
		else
			return (cd_normal(sh, argv[1]));
	}
	return (0);
}
