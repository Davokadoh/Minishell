/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:50:55 by jleroux           #+#    #+#             */
/*   Updated: 2022/11/13 16:51:38 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	str = malloc((l1 + l2 - (end - start) + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, start + 1);
	if (l2)
		ft_strlcat(str, s2, ft_strlen(str) + l2 + 1);
	ft_strlcat(str, &s1[end], ft_strlen(str) + ft_strlen(&s1[end]) + 1);
	ft_free(s1);
	return (str);
}

static int	get_var_end(char *str)
{
	int	i;

	i = 1;
	if (ft_isdigit(str[i]))
		return (i);
	while (str[i] && str[i] != ' ' && str[i] != '$' && str[i] != '"'\
			&& str[i] != '\'' && !is_meta(str[i]) && str[i] != '='\
			&& str[i] != '/')
		i++;
	if (ft_isdigit(str[i]))
		i++;
	if (i - 1 < 0)
		return (0);
	return (i - 1);
}

static void	replace_env_var(char **line, char **ft_env, int i)
{
	char	*key;
	char	*val;

	key = ft_substr(&(*line)[i], 1, get_var_end(&(*line)[i]));
	if (!*key)
		return ;
	val = ft_getenv(key, ft_env);
	if (!val)
		val = NULL;
	*line = ft_strinsert(*line, val, i, i + ft_strlen(key) + 1);
	ft_free(key);
}

int	expand(int errno, char ***ft_env, char *original_line)
{
	int		i;
	int		s_quotes;
	int		d_quotes;
	char	*line;

	i = -1;
	s_quotes = 0;
	d_quotes = 0;
	line = strdup(original_line);
	while (line[++i])
	{
		if (line[i] == '\'' && !d_quotes)
			s_quotes = (s_quotes + 1) % 2;
		if (line[i] == '"' && !s_quotes)
			d_quotes = (d_quotes + 1) % 2;
		if (line[i] == '$' && line[i + 1] != '?' && !s_quotes)
			replace_env_var(&line, *ft_env, i);
		if (!line[i])
			break ;
	}
	errno = lexer(errno, ft_env, line);
	ft_free(line);
	return (errno);
}
