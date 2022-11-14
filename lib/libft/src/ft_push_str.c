/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:07:13 by jleroux           #+#    #+#             */
/*   Updated: 2022/11/10 11:34:04 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_copy_array(char **dst, char **src)
{
	int	i;

	i = -1;
	if (src)
		while (src[++i])
			dst[i] = ft_strdup(src[i]);
	return (dst);
}

char	**ft_push_str(char ***array, char *str)
{
	size_t	i;
	char	**new_array;

	i = 0;
	if (*array)
		while ((*array)[i])
			i++;
	new_array = ft_calloc((i + 2), sizeof(char **));
	if (!new_array)
		return (*array);
	new_array = ft_copy_array(new_array, *array);
	new_array[i] = ft_strdup(str);
	new_array[i + 1] = NULL;
	ft_free_tab(*array);
	return (new_array);
}
