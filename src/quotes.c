/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:35:31 by jleroux           #+#    #+#             */
/*   Updated: 2022/11/13 16:35:33 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	unclosed_quote(const char *str)
{
	int	i;
	int	s_quotes;
	int	d_quotes;

	i = -1;
	s_quotes = 0;
	d_quotes = 0;
	while (str[++i])
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

int	quotes(int errno, char ***ft_env, char *line)
{
	if (unclosed_quote(line))
	{
		ft_putstr_fd("Closing quote not found\n", 2);
		return (1);
	}
	errno = expand(errno, ft_env, line);
	return (errno);
}

void	expand_errno(int errno, char **token)
{
	int				i;
	unsigned int	s_quotes;

	s_quotes = 0;
	i = -1;
	while (token[0][++i])
	{
		if (token[0][i] == '\'')
			s_quotes = (s_quotes + 1) % 2;
		if (token[0][i] == '$' && token[0][i + 1] == '?' && !s_quotes)
			*token = ft_strinsert(token[0], ft_itoa(errno), i, i + 2);
	}
}

char	*strip_quotes(char *token)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (token[++i])
	{
		while (token[i] && token[i] != '"' && token[i] != '\'')
			i++;
		j = i + 1;
		if (token[i] == '"')
			while (token[j] && token[j] != '"')
				j++;
		else if (token[i] == '\'')
			while (token[j] && token[j] != '\'')
				j++;
		else
			break ;
		tmp = malloc(sizeof(char *) * (ft_strlen(token) - 2));
		ft_strlcpy(tmp, token, i + 1);
		ft_strlcpy(&tmp[i], &token[i + 1], j - i);
		ft_strlcpy(&tmp[j - 1], &token[j + 1], ft_strlen(token) - j);
		token = ft_realloc(token, sizeof(char *) * (ft_strlen(token) - 2));
		ft_strlcpy(token, tmp, ft_strlen(tmp) + 1);
		ft_free(tmp);
		i = j - 2;
	}
	return (token);
}
