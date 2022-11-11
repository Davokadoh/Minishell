#include "../include/minishell.h"

int	unclosed_quote(const char *str)
{
	int	i;
	int	s_quotes;
	int	d_quotes;

	i = -1;
	s_quotes = 0;
	d_quotes = 0;
	while (str[++i])
	{
		if (str[i] == '\'' && !d_quotes)
			s_quotes = (s_quotes + 1) % 2; // replace with bool add ?
		if (str[i] == '"' && !s_quotes)
			d_quotes = (d_quotes + 1) % 2; // replace with bool add ?
	}
	if (s_quotes || d_quotes)
		return (1);
	return (0);
}

int	syntax(int errno, t_envp *ft_env, char *line)
{
	if (unclosed_quote(line))
	{
		ft_putstr_fd("Closing quote not found\n", 2);
		return (1);
	}
	errno = expand(errno, ft_env, line);
	return (errno);
}
