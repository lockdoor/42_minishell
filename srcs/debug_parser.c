/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 09:10:45 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/14 10:38:52 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_pipe(char **ps, char *s);
void	parse_exec(char **ps, char *s);
void	parse_redir(char **ps, char *s);

void	panic(char *s)
{
	write (2, s, ft_strlen(s));
	exit (1);
}

void	print_token(char *q, char *eq)
{
	write (1, "[", 1);
	if (eq)
		write (1, q, eq - q);
	else
		write (1, q, ft_strlen(q));
	write (1, "]", 1);
}

void	parsecmd(char *s)
{
	char	*es;

	es = ft_strchr(s, 0);
	parse_pipe(&s, es);
	write (1, "\n", 1);
}

void	parse_pipe(char **ps, char *es)
{
	parse_exec(ps, es);
	if (peek(ps, es, "|"))
	{
		print_token ("|", NULL);
		gettoken (ps, es, NULL, NULL);
		parse_pipe(ps, es);
	}
}

void	parse_exec(char **ps, char *es)
{
	char	*q;
	char	*eq;
	int		token;

	parse_redir(ps, es);
	write (1, "[", 1);
	while (peek(ps, es, SYMBOLS) == 0)
	{
		token = gettoken(ps, es, &q, &eq);
		if (token == 0)
			break ;
		if (token != 'a')
			panic ("error no command");
		else
			print_token(q, eq);
	}
	write (1, "]", 1);
}

void	parse_redir(char **ps, char *es)
{
	char	*q;
	char	*eq;
	int		token;
	if (peek(ps, es, "<>"))
	{
		write (1, "[", 1);
		token = gettoken(ps, es, NULL, NULL);
		if (token == '<')
			print_token ("<", NULL);
		else if (token == '>')
			print_token (">", NULL);
		else if (token == '+')
			print_token (">>", NULL);
		else
			print_token ("<<", NULL);
		token = gettoken(ps, es, &q, &eq);
		if (token != 'a')
			panic ("error no file");
		else
			print_token (q, eq);
		write (1, "]", 1);
		parse_redir (ps, es);
	}
}
