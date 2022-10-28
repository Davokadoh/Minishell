#include "../include/minishell.h"

char	*ft_strinsert(char *s1, char *s2, int start, int end)
{
	char	*str;
	int		l1;
	int		l2;

	if (!s1)
		return (NULL);
	l1 = ft_strlen(s1);
	if (!s2)
		l2 = 0;
	else
		l2 = ft_strlen(s2);
	str = (char *) malloc((l1 + l2  - (end - start) + 1) * sizeof(*s1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, start + 1);
	if (l2)
		ft_strlcat(str, s2, l2);
	ft_strlcat(str, &s1[end], ft_strlen(&s1[end]));
	ft_free(s1);
	ft_free(s2);
	return (str);
}

static int	get_var_end(char *str)
{
    int	i;

    i = 0;
    while (str[i] && str[i] != ' ' && str[i] != '$' && str[i] != '"')
        i++;
    return (i);
}

char	*expand(char *line, char **ft_env)
{
	int		i;
	int		s_quotes;
	int		d_quotes;
	char	*key;
	char	*val;

	i = -1;
	s_quotes = 0;
	d_quotes = 0;
	while (line[++i])
	{
		if (line[i] == '\'' && !d_quotes)
			s_quotes = (s_quotes + 1) % 2;
		if (line[i] == '"' && !s_quotes)
			d_quotes = (d_quotes + 1) % 2;
		printf("c:%c	single:%d	double:%d\n", line[i], s_quotes, d_quotes);
		if (line[i] == '$' && line[i + 1] != '?' && !s_quotes && !d_quotes)
		{
			key = ft_substr(&line[i], 1, get_var_end(&line[i + 1]));
			val = ft_getenv(key, ft_env);
			if (!val)
				val = NULL;
			line = ft_strinsert(line, val, i, i + ft_strlen(key) + 1);
			ft_free(key);
		}
	}
	return (line);
}
