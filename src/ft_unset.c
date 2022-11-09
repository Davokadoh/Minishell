/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btchiman <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:03:53 by btchiman          #+#    #+#             */
/*   Updated: 2022/11/09 10:56:38 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// enleve un element de la liste d'env
int	ft_unset(char **args, char ***env)
{
	char	**new_env;
	int		i;
	int		n;

	i = -1;
	new_env = NULL;
	if (ft_getenv(args[1], *env))
	{
		n = ft_strlen(args[1]);
		while ((*env)[++i])
			;
		new_env = malloc(sizeof(char **) * i - 1);
		i = -1;
		while ((*env)[++i])
		{
			if (!ft_strnstr((*env)[i], args[1], n))
				new_env[i] = ft_strdup((*env)[i]);
		}
		new_env[i] = NULL;
		*env = new_env;
		return (0);
	}
	*env = new_env;
	return (0);
}
