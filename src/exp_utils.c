/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btchiman <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 14:53:15 by btchiman          #+#    #+#             */
/*   Updated: 2022/11/13 14:53:29 by btchiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char **incr(char **new_env,char *l_value, char *new_entry)
{
		int i;

		i = -1;
		while( new_env && new_env[++i])
		{
			if(ft_strnstr(new_env[i],l_value,ft_strlen(l_value)))
			{
				new_env[i] = ft_strdup(new_entry);
				return (new_env);
			}	
		}
		new_env = ft_push_str(&new_env,new_entry);
		return (new_env);
}

char **init_exp(char **env)
{
    char **exp;
    int i;
    int j;
    
    i = -1;
    j = 0;
    while (env[++i])
        ;
    exp = malloc(sizeof(char **) * (i + 1));
	if(!exp)
		exit(0);
    while (env[j])
    {
		if(ft_strncmp(env[j],"_=",2) != 0)
		{
			exp[j] = ft_strdup(env[j]);//leaks
		}
        j++;
    }
	exp[j] = NULL;
	exp = ft_triAlpha(exp);
    return (exp);
}
