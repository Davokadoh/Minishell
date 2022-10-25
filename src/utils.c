/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Blaze <Blaze@42lausanne.ch>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:41:37 by Blaze             #+#    #+#             */
/*   Updated: 2022/10/25 14:10:34 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char **ft_increnv(char **env, char *new_entry)
{
    char **new_env;
    int	i;

    i = 0;
    while(env[i])
        i++;
    new_env = malloc(sizeof(char**)*i +2);
    i = 0;
    while(env[i])
    {
        new_env[i] = ft_strdup(env[i]);
        i++;
    }
    new_env[i] = ft_strdup(new_entry);
    new_env[i+1] = NULL;
    return (new_env);
}

char *malloc_substrcpy(char *variable, int start, int end)
{
    int len;
    int i;
    int j;
    char *name;

    i = 0;
    j = start;
    len = end - start;

    name = malloc(sizeof(char) * len + 1);
    while (i <= len)
    {
        name[i] = variable[j];
        i++;
        j++;
    }
    name[i] = '\0';
    return (name);
}

char *get_variable_name(char *variable)
{
    int		index;
    int		start;
    int		end;
    char	*name;

    index = 0;
    start = 0;
    if (!variable)
        return (NULL);
    while (variable[index])
    {
        if (variable[index] == '=')
        {
            end = index - 1;
            name = malloc_substrcpy(variable, start, end);
            return (name);
        }
        index++;
    }
    end = index;
    name = malloc_substrcpy(variable, start, end);
    return (name);
}

char *get_env_variable_value(char *variable)
{
    int		i;
    int		start;
    int		end;
    char	*value;

    i = 0;
    if (!variable)
        return (NULL);
    while (variable[i])
    {
        if (variable[i] == '=')
        {
            start = i + 1;
            end = ft_strlen(variable);
            value = malloc_substrcpy(variable, start, end);
            return (value);
        }
        i++;
    }
    return (NULL);
}
