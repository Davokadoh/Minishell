/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 09:43:56 by jleroux           #+#    #+#             */
/*   Updated: 2021/10/22 16:24:10 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int		start;
	size_t				end;

	if (!s1)
		return (NULL);
	start = 0;
	while (s1[start] && ft_is_in_set(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_is_in_set(s1[--end], set))
		;
	return (ft_substr(s1, start, end - start + 1));
}

/*
int	main(void)
{
	char	*s;
	char	*s1;
	char	*s2;

	s1 = "tripouille   xxx";
	s2 = " x";
	s = ft_strtrim(s1, s2);
	printf("%s\n", s);
	return (0);
}
*/
