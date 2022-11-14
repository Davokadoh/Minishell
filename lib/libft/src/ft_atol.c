/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <jleroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 14:37:46 by jleroux           #+#    #+#             */
/*   Updated: 2022/06/29 13:44:38 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

long int	ft_atol(const char *str)
{
	int				sign;
	long long int	nbr;

	sign = 1;
	nbr = 0;
	while (*str == 32 || (9 <= *str && *str <= 13))
		str++;
	if (*str == 43 || *str == 45)
	{
		if (*str == 45)
			sign = -1;
		str++;
	}
	while (48 <= *str && *str <= 57)
	{
		nbr *= 10;
		nbr += *str - '0';
		str++;
	}
	if (nbr > 4294967296 && sign == -1)
		return (0);
	if (nbr > 4294967296 && sign == 1)
		return (-1);
	return (nbr * sign);
}
