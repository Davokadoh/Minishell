/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_array_size.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:11:18 by jleroux           #+#    #+#             */
/*   Updated: 2022/11/10 10:17:30 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Returns -1 when there is no array
int	ft_str_array_size(char **array)
{
	int	i;

	i = -1;
	if (array)
		while (array[++i])
			i++;
	return (i);
}
