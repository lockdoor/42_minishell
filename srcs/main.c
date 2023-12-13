#include "minishell.h"

int	token_symbols(char **ps)
{
	char	*s;
	int		ret;

	s = *ps;
	ret = *s;
	s++ ;
	if (ret == '<' && *s == '<')
	{
		s++ ;
		ret = 'h';
	}
	else if (ret == '>' && *s == '>')
	{
		s++ ;
		ret = '+';
	}
	*ps = s;
	return (ret);
}

int	qoute(char **ps)
{
	char	*s;
	int		q;
	int		ret;

	ret = 0;
	s = *ps;
	q = *s;
	s++ ;
	while (*s && *s != q)
	{
		if (*s == '\'' || *s == '"')
			ret = qoute(&s);
		s++ ;
	}
	if (*s != q || ret)
		return (1);
	*ps = s;
	return (0);
}

int token_string(char **ps)
{
	char	*s;

	s = *ps;
	while (*s && !ft_strchr(WHITESPACE, *s) && !ft_strchr(SYMBOLS, *s))
	{
		if (*s == '\'' || *s == '"')
			if (qoute(&s))
			{
				ft_putendl_fd ("not found end qoute", 2);
				return (-1);
			}
		s++ ;
	}
	*ps = s;
	return ('a');
}

int	gettoken(char **ps, char *es, char **q, char **eq)
{
	char	*s;
	int		ret;

	s = *ps;
	while (s < es && ft_strchr(WHITESPACE, *s))
		s++;
	if (q)
		*q = s;
	ret = *s;
	if (ft_strchr(SYMBOLS, *s))
		ret = token_symbols(&s);
	else
		ret = token_string(&s);
	if (eq)
		*eq = s;
	*ps = s;
	return (ret);
}

int	showtoken(char	*line)
{
	char	*ps;
	char	*es;
	char	*q;
	char	*eq;
	int		type;

	ps = line;
	es = ft_strchr(ps, 0);
	while ((type = gettoken(&ps, es, &q, &eq)))
	{
		if (type == -1)
			return (-1);
		write (1, "type: ", 7);
		write (1, &type, 1);
		write (1, ", ", 2);
		write (1, "char: ", 7);
		write (1, q, eq - q);
		write (1, "\n", 1);
	}
	return (0);
}

int main(void)
{
	char *line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break;
		showtoken (line);
		free (line);
	}
	free (line);
	return (0);
}
