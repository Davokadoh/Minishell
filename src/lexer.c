#include "../include/minishell.h"

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

static int	get_token_end(char *str, size_t start)
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

static int	add_next_token(char ***tokens, char *str, size_t start)
{
	size_t	end;
	char	*new_str;

	while (str[start] == ' ') //while (is_whitespace() ?)
		start++;
	end = get_token_end(str, start);
	if (end - start)
	{
		new_str = ft_substr(str, start, end - start);
		*tokens = ft_push_str(tokens, new_str);
		ft_free(new_str);
	}
	if (is_meta(str[end]))
	{
		new_str = copy_meta(&str[end], &end);
		*tokens = ft_push_str(tokens, new_str);
		ft_free(new_str);
	}
	return (end);
}

int	lexer(int errno, t_envp *ft_env, char *str)
{
	size_t	i;
	char	**tokens;

	if (!str)
		return (4); //Find correct errno + define macro
	tokens = NULL;
	i = 0;
	while (str[i])
		i = add_next_token(&tokens, str, i);
	errno = parse(errno, ft_env, tokens);
	ft_free_tab(tokens);
	return (errno);
}
