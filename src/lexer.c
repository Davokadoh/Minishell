#include "../include/minishell.h"
#include <stdbool.h>

int	is_meta(const char ch)
{
	if (ch == ';')
		return (1);
	else if (ch == '|')
		return (1);
	else if (ch == '&')
		return (1);
	else if (ch == '<')
		return (1);
	else if (ch == '>')
		return (1);
	else
		return (0);
}

static char	*copy_meta(const char *token, size_t *end)
{
	if (token[0] != token[1])
	{
		*end += 1;
		return (ft_substr(token, 0, 1));
	}
	else
	{
		*end += 2;
		return (ft_substr(token, 0, 2));
	}
}

//Returns 1 if str added, 0 if nothing added
static int	ft_push_str(char **array, char *str)
{
	size_t	i;

	i = 0;
	while(array[i])
		i++;
	array = realloc(array, (i + 2) * sizeof(char **)); //Illegal function!!! create ft_realloc
	if (!array)
		return (0);
	array[i++] = str;
	array[i] = NULL;
	return (1);
}

static int	get_token_end(char *str)
{
	size_t	i;
	bool	s_quotes;
	bool	d_quotes;

	i = 0;
	s_quotes = 0;
	d_quotes = 0;
	while (str[i] && ((str[i] != ' ' && !is_meta(str[i])) || s_quotes || d_quotes))
	{
		if (str[i] == '"' && !s_quotes)
			d_quotes = !d_quotes;
		else if (str[i] == '\'' && !d_quotes)
			s_quotes = !s_quotes;
		i++;
	}
	return (i);
}

int	add_next_token(char **tokens, char *str, size_t start, size_t *nb)
{
	size_t	end;

	while (str[start] == ' ')
		start++;
	end = get_token_end(&str[start]);
	if (end - start)
		*nb += ft_push_str(tokens, ft_substr(str, start, end - start));
	if (is_meta(str[end]))
		*nb += ft_push_str(tokens, copy_meta(&str[end], &end));
	return (end);
}

int	lexer(int errno, char **ft_env, char *str)
{
	size_t	i;
	size_t	nb;
	char	**tokens;

	if (!str)
		return (4);
	tokens = ft_calloc(1, sizeof(char **));
	if (!tokens)
		return (4);
	i = 0;
	nb = 0;
	while (str[i])
		i = add_next_token(tokens, str, i, &nb);
	errno = parse(errno, ft_env, tokens);
	ft_free_tab(tokens);
	return (errno);
}
