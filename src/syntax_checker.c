#include "../include/minishell.h"

int	unclosed_quote(const char *str)
{
	int	i;
	int	s_quotes;
	int	d_quotes;

	i = 0;
	s_quotes = 0;
	d_quotes = 0;
	while (str[++i] && !s_quotes && !d_quotes)
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

#ifndef STDOUT
# define STDOUT 2
#endif

size_t	ft_error(int errno)
{
	//this function belong in libft!!!
	//including the preprocessor instructions
	ft_putendl_fd(strerror(errno), STDOUT);
	return (errno);
}

int	syntax(int errno, char **ft_env, char *line)
{
	if (unclosed_quote(line))
		return (ft_error(3));
	errno = expand(errno, ft_env, line);
	ft_free(line);
	return (errno);
}
