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

#include "../include/minishell.h"
/*
 * // ajoute a la liste de variable d'environnement
int ft_export(char **args)
{
    //t_envp  *env;

}*/

/*
 * char	*get_variable_name(char *variable)
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

 char	*get_env_variable_value(char *variable)
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
		if (variable[i] == '=' && !(is_blank(variable[i + 1])))
		{
			start = i + 1;
			end = ft_strlen(variable);
			value = malloc_substrcpy(variable, start, end);
			if (is_value_null(value))
			{
				free(value);
				return (NULL);
			}
			return (value);
		}
		i++;
	}
	return (NULL);
}

 */