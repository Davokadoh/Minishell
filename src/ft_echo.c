/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btchiman <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:06:23 by btchiman          #+#    #+#             */
/*   Updated: 2022/11/01 15:00:00 by jleroux          ###   ########.fr       */
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
		if (args[i][j] != '\0')
		{
			n = 0;
			newLine = 1;
			break ;
		}
		i++;
	}
	if (newLine && n)
		i = 0;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if(newLine)
		ft_putstr_fd("\n", 1);
	return (1);
}
