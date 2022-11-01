/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btchiman <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:06:23 by btchiman          #+#    #+#             */
/*   Updated: 2022/10/25 14:09:46 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_echo (char **args)
{
	int	i;
	int	j;
	int	n;
	int newLine;

	n = 0;
	newLine = 1;
	if (!args[0])
		return (127);
	i = 1;
	while (args[i] && args[i][0] == '-')
	{
		j = 0;
		while (args[i][++j] == 'n')
		{
			n = 1;
			newLine = 0;
		}
		if (args[i][j] != '\0' && args[i][j] != ' ')
			newLine = 1;
		i++;
	}
	if (newLine && n)
		i--;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf("\x20");
		i++;
	}
	if(newLine)
		printf("\n");
	return (1);
}
