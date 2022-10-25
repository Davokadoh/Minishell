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
	int newLine;

	newLine = 1;
	if(ft_strncmp(*args,"echo",4) != 0)
		return (0);
	args++;
	if (ft_strncmp(*args,"-n", 2) == 0)
	{
		newLine = 0;
		args++;
	}
	while (*args)
	{
		printf("%s", *args);
		printf("\x20");
		args++;
	}
	if(newLine)
		printf("\n");
	return (1);
}
