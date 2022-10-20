/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btchiman <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:41:12 by btchiman          #+#    #+#             */
/*   Updated: 2022/10/18 17:41:36 by btchiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
//TODO creer un nouveau tableau de longeur envp +1 mettre la nouvelle entree
// dans le nouveau tableau et dans un tableau export puis liberer l'ancien tableau envp

char **add_env_var(char *l_value, char *r_value, char **env)
{
    char *new_entry;
    int i;

    i = 0;
    new_entry = ft_strjoin(l_value,"=");
    new_entry = ft_strjoin(new_entry,r_value);
    env = realloc(env,sizeof  (env) +1 );
    while(env[i])
        i++;
    env[i] = new_entry;
    ft_free(new_entry);
    return (env);
}
// ajoute un element au tableau de variable d'environnement et au tableau d'export
char **ft_export(char **args, char **env)
{
    char    *l_value;
    char    *r_value;

    args++;
    l_value = get_variable_name(args[0]);
    r_value = get_env_variable_value(args[0]);
    if(l_value && r_value)
        env = add_env_var(l_value,r_value,env);
    return (env);
}

 // TODO export loop
 // print_export()
