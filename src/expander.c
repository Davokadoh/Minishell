#include "../minishell.h"

static char	*ft_strinsert(const char *str1, const char *str2, int start, int end)
{
	char	*ptr;
	char	*new_str;

	new_str = ft_substr(str1, 0, start);
	ptr = new_str;
	new_str = ft_strjoin(new_str, str2);
	ft_free(ptr);
	ptr = new_str;
	new_str = ft_strjoin(new_str, &str1[end]);
	ft_free(ptr);
	//ft_free(str1);
	//ft_free(str2);
	return (new_str);
}

static int	get_var_end(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '$' && str[i] != '"')
		i++;
	return (i);
}


char	*expand(char **str)
{
	int		i;
	char	*var;

	i = -1;
	while (str[0][++i])
	{
		if (str[0][i] == '$' && str[0][i + 1] != '?')
		{
			var = ft_substr(*str, i + 1, get_var_end(&str[0][i + 1]));
			*str = ft_strinsert(*str, getenv(var), i, i + ft_strlen(var) + 1);
			ft_free(var);
		}
	}
	return (*str);
}
