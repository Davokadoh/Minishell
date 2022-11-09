/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btchiman <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:03:53 by btchiman          #+#    #+#             */
/*   Updated: 2022/10/25 12:45:58 by btchiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// enleve un element de la liste d'env et exp
// retourne 0 en cas de succes et -1 en cas d'erreur
int ft_unset(char **args,char **env)
{
	int	i;
	int j;
	int k;
	char *name;

	i = 0;
	j = -1;
	k = -1;
	while(env[++k])
		;
	while(args[++i])
	{
		while(env[++j])
		{
			name = get_variable_name(args[i]);
			if(ft_strnstr(name,get_variable_name(env[j]),ft_strlen(env[j])))
			{
				while(env[j])
				{
					env[j] = env[j+1];
					j++;
				}
				env[j] = NULL;
			}
		}
		j = -1;
	}
	while(env[++j])
		;
	if( k > j)
		return(0);
	return (-1);
}
