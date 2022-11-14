/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 12:01:28 by jleroux           #+#    #+#             */
/*   Updated: 2021/10/28 10:26:08 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_length;
	size_t	src_length;

	dst_length = ft_strlen(dst);
	src_length = ft_strlen(src);
	if (dst_length > size - 1 || size == 0)
		return (src_length + size);
	while (*dst != '\0' && --size > 0)
		dst++;
	while (*src != '\0' && --size > 0)
		*dst++ = *src++;
	*dst = '\0';
	return (dst_length + src_length);
}
