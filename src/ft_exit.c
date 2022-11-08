/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btchiman <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:07:50 by btchiman          #+#    #+#             */
/*   Updated: 2022/11/08 20:23:52 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	num_req(char **argv)
{
	ft_putstr_fd("msh : line 0: exit: ", 2);
	ft_putstr_fd(argv[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	return (255);
}

int	ft_exit(char **argv)
{
	int	errno;

	errno = 0;
	if (!argv[1])
		return (0);
	if ((argv[1][0] == '+' || argv[1][0] == '-') && ft_isdigit(argv[1][1]) \
			&& !argv[2])
		errno = ft_atol(argv[1]);
	else if (ft_isdigit(argv[1][0]) && !argv[2])
		errno = ft_atol(argv[1]);
	else if (argv[1][0] != '+' && argv[1][0] != '-' && !ft_isdigit(argv[1][0]))
		errno = num_req(argv);
	else if (argv[2])
	{
		ft_putstr_fd("msh : line 0: exit: too many arguments\n", 2);
		errno = 1;
	}
	if (errno == 0 && (argv[1][0] != '0'\
				&& (argv[1][1] == '\0' || argv[1][1] != '0')))
		errno = num_req(argv);
	printf("TEST\n");
	return (errno);
}
