/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btchiman <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:06:23 by btchiman          #+#    #+#             */
/*   Updated: 2022/11/07 17:32:32 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_echo(char **args)
{
	int	i;
	int	j;
	int	n;
	int	new_line;

	n = 0;
	new_line = 1;
	if (!args[0])
		return (127);
	i = 1;
	while (args[i] && args[i][0] == '-')
	{
		j = 0;
		while (args[i][++j] == 'n')
		{
			n = 1;
			new_line = 0;
		}
		if (args[i][j] != '\0')
		{
			n = 0;
			new_line = 1;
			break ;
		}
		i++;
	}
	if (new_line && n)
		i = 0;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (new_line)
		ft_putstr_fd("\n", 1);
	return (1);
}
