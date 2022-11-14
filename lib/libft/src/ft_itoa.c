/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 11:53:50 by jleroux           #+#    #+#             */
/*   Updated: 2021/10/28 10:13:23 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	int_size(unsigned int n)
{
	if (n > 9)
		return (int_size(n / 10) + 1);
	return (1);
}

static void	add_digit(unsigned int n, char *str)
{
	*str = n % 10 + 48;
	if (n > 9)
		add_digit((n / 10), --str);
	return ;
}

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	nbr;
	int				i;

	if (n < 0)
	{
		nbr = -n;
		i = int_size(nbr);
		i++;
	}
	else
	{
		nbr = n;
		i = int_size(nbr);
	}
	str = (char *) malloc(i * sizeof(char) + 1);
	if (!str)
		return (NULL);
	str[i] = 0;
	add_digit(nbr, &str[i - 1]);
	if (n < 0)
		*str = '-';
	return (str);
}

/*
#include <stdio.h>

int	main(void)
{
	printf("%s\n", ft_itoa(-2147483648));
	printf("%s\n", ft_itoa(-42));
	printf("%s\n", ft_itoa(-9));
	printf("%s\n", ft_itoa(-1));
	printf("%s\n", ft_itoa(0));
	printf("%s\n", ft_itoa(1));
	printf("%s\n", ft_itoa(9));
	printf("%s\n", ft_itoa(42));
	printf("%s\n", ft_itoa(2147483647));
}
*/
