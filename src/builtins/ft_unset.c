/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btchiman <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:03:53 by btchiman          #+#    #+#             */
/*   Updated: 2022/10/24 15:07:10 by btchiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char **ft_unset(char **args,char **env)
{
    int i;
	char **new_env;

    i = -1;
    args++;
    while(env[++i]);
    new_env = malloc(sizeof(char *) * i);
    i = -1;
    while (env[++i])
    {
        if (ft_strncmp(env[i], *args, ft_strlen(*args)) == 0)
        {
            while (env[++i])
                new_env[i] = env[i];
            new_env[i] = NULL;
            return (new_env);
        }
    }

	return (env);
}
