/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:19:09 by jleroux           #+#    #+#             */
/*   Updated: 2021/10/27 11:58:59 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	nb_words(char const *s, char c)
{
	unsigned int	start;
	unsigned int	end;
	unsigned int	nb;

	start = 0;
	nb = 0;
	while (s[start])
	{
		while (s[start] == c)
			start++;
		end = start;
		while (s[end] != c && s[end])
			end++;
		if (s[start])
			nb++;
		start = end;
	}
	return (nb);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	start;
	unsigned int	end;
	int				nb;
	char			**list;

	if (!s)
		return (NULL);
	start = 0;
	nb = 0;
	list = malloc((1 + nb_words(s, c)) * sizeof(char *));
	if (!list)
		return (NULL);
	while (s[start])
	{
		while (s[start] == c)
			start++;
		end = start;
		while (s[end] != c && s[end])
			end++;
		if (s[start])
			list[nb++] = ft_substr(s, start, end - start);
		start = end;
	}
	list[nb] = NULL;
	return (list);
}
