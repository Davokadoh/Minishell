/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strrchr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 12:04:12 by jleroux           #+#    #+#             */
/*   Updated: 2021/10/19 13:50:03 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strrchr(const char *s, int c)
{
	const char	*start;

	start = s;
	while (*s != '\0')
		s++;
	while (s != start)
	{
		if (*s == (char) c)
			return ((char *) s);
		s--;
	}
	if (*s == (char) c)
		return ((char *) s);
	return (NULL);
}
