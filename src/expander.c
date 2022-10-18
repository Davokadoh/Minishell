#include "../include/minishell.h"

static char	*ft_strinsert(const char *s1, const char *s2, int start, int end)
{
    char	*str;
    int		l1;
    int		l2;

    if (!s1 || !s2)
        return (NULL);
    str = (char *) malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(*s1) + 1);
    if (!str)
        return (NULL);
    l1 = ft_strlen(s1);
    l2 = ft_strlen(s2);
    ft_strlcpy(str, s1, l1 + 1);
    ft_strlcpy(&str[start], s2, l2 + 1);
    ft_strlcpy(&str[ft_strlen(str)], &s1[end], ft_strlen(&s1[end]) + l2 + 1);
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

char	*expand(char **tokens)
{
    int		i;
    char	*key;
    char	*val;
    char	*tmp;

    i = -1;
    while (tokens[0][++i])
    {
        if (tokens[0][i] == '$' && tokens[0][i + 1] != '?')
        {
            key = ft_substr(*tokens, i + 1, get_var_end(&tokens[0][i + 1]));
            tmp = getenv(key);
            if (!tmp)
            {
                ft_free(key);
                continue ;
            }
            val = ft_strdup(getenv(key));
            tmp = *tokens;
            *tokens = ft_strinsert(*tokens, val, i, i + ft_strlen(key) + 1);
            ft_free(tmp);
            ft_free(key);
            ft_free(val);
        }
    }
    return (*tokens);
}