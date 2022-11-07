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

//Returns 1 if str added, 0 if realloc failed
static int	ft_push_str(char ***array, char *str) //Move to libft ?
{
	size_t	i;

	i = 0;
	while ((*array)[i])
		i++;
	*array = realloc(*array, (i + 2) * sizeof(char **)); //Illegal function!!! create ft_realloc
	if (!(*array))
		return (0);
	(*array)[i] = str;
	(*array)[i + 1] = NULL;
	return (1);
}

static int	get_token_end(char *str, size_t start) //Move to libft with add ?
{
	size_t	s_quotes;
	size_t	d_quotes;

	s_quotes = 0;
	d_quotes = 0;
	while (str[start] && ((str[start] != ' ' && !is_meta(str[start])) || s_quotes || d_quotes))
	{
		if (str[start] == '"' && !s_quotes)
			d_quotes = (d_quotes + 1) % 2;
		else if (str[start] == '\'' && !d_quotes)
			s_quotes = (s_quotes + 1) % 2;
		start++;
	}
	return (start);
}

int	add_next_token(char ***tokens, char *str, size_t start) //Move to libft ?
{
	size_t	end;

	while (str[start] == ' ') //while (is_whitespace() ?)
		start++;
	end = get_token_end(str, start);
	if (end - start)
		ft_push_str(tokens, ft_substr(str, start, end - start));
	if (is_meta(str[end]))
		ft_push_str(tokens, copy_meta(&str[end], &end));
	return (end);
}

int	lexer(int errno, char ***ft_env, char *str)
{
	size_t	i;
	char	**tokens;

	if (!str)
		return (4); //Find correct errno
	tokens = ft_calloc(1, sizeof(char **)); //Not sure about the 0 here
	if (!tokens)
		return (4); //Find correct errno
	i = 0;
	while (str[i])
		i = add_next_token(&tokens, str, i);
	errno = parse(errno, ft_env, tokens);
	ft_free_tab(tokens);
	return (errno);
}
