/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 12:02:30 by jleroux           #+#    #+#             */
/*   Updated: 2021/10/27 15:33:45 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int	i;

	if (!dst && !src)
		return (NULL);
	if (dst > src)
	{
		i = len;
		while (--i >= 0)
			((char *)dst)[i] = ((char *)src)[i];
	}
	else
	{
		i = -1;
		while (++i < (int) len)
			((char *)dst)[i] = ((char *)src)[i];
	}
	return (dst);
}
