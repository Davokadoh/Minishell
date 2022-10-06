#include "../inc/minishell.h"

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
		while (s[end] && (s[end] != ' ' || s_quote || d_quote))
		{
			if (s[end] == '"' && !s_quote)
				d_quote = (d_quote + 1) % 2;
			else if (s[end] == '\'' && !d_quote)
				s_quote = (s_quote + 1) % 2;
			end++;
		}
		list[nb++] = ft_substr(s, start, end - start);
		start = end;
	}
	list[nb] = NULL;
	return (list);
}
