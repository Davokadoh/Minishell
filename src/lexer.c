#include "../include/minishell.h"

int	is_meta(const char ch)
{
	if (ch == '|')
		return (1);
	else if (ch == '<')
		return (1);
	else if (ch == '>')
		return (1);
	else
		return (0);
}

char	*copy_meta(const char *ch, unsigned int *end)
{
	if (ch[0] == '|' && ch[1] == '|')
	{
		*end += 2;
		return (ft_strdup("||"));
	}
	else if (ch[0] == '|')
	{
		*end += 1;
		return (ft_strdup("|"));
	}
	else if (ch[0] == '<' && ch[1] == '<')
	{
		*end += 2;
		return (ft_strdup("<<"));
	}
	else if (ch[0] == '<')
	{
		*end += 1;
		return (ft_strdup("<"));
	}
	else if (ch[0] == '>' && ch[1] == '>')
	{
		*end += 2;
		return (ft_strdup(">>"));
	}
	else if (ch[0] == '>')
	{
		*end += 1;
		return (ft_strdup(">"));
	}
	else
		return (NULL);

}

char	**lex(char const *s)
{
	unsigned int	start;
	unsigned int	end;
	unsigned int	s_quote;
	unsigned int	d_quote;
	unsigned int	nb;
	char			**list;

	if (!s)
		return (NULL);
	start = 0;
	nb = 0;
	s_quote = 0;
	d_quote = 0;
	list = malloc(1024);//(1 + nb_words(s, c)) * sizeof(char *));
	if (!list)
		return (NULL);
	while (s[start])
	{
		while (s[start] == ' ')
			start++;
		end = start;
		while (s[end] && ((s[end] != ' ' && !is_meta(s[end])) || s_quote || d_quote))
		{
			if (s[end] == '"' && !s_quote)
				d_quote = (d_quote + 1) % 2;
			else if (s[end] == '\'' && !d_quote)
				s_quote = (s_quote + 1) % 2;
			end++;
		}
		if (end - start)
			list[nb++] = ft_substr(s, start, end - start);
		if (is_meta(s[end]))
			list[nb++] = copy_meta(&s[end], &end);
		start = end;
	}
	list[nb] = NULL;
	return (list);
}
