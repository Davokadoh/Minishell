/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Blaze <Blaze@42lausanne.ch>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:41:37 by Blaze             #+#    #+#             */
/*   Updated: 2022/11/02 18:17:12 by btchiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//TODO trier par ordre alpha et fusionner a la fin du precedent tableau !
char	**ft_increnv(char **env, char *new_entry)
{
	char	**new_env;
	int		i;

	i = -1;
	while (env[++i])
		;
	new_env = malloc(sizeof (char **) * (i + 2));
	if (!new_env)
		return (NULL);
	i = -1;
	while (env[++i])
		new_env[i] = ft_strdup(env[i]);
	new_env[i] = ft_strdup(new_entry);
	new_env[i + 1] = NULL;
	i = -1;
	while (env[++i])
		ft_free(env[i]);
	new_env = ft_triAlpha(new_env);
	return (new_env);
}

char	*malloc_substrcpy(char *variable, int start, int end)
{
	int		len;
	int		i;
	int		j;
	char	*name;

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

char	*get_variable_name(char *variable)
{
	char	*name;
	int		index;
	int		start;
	int		end;

	index = 0;
	start = 0;
	if (!variable)
		return (NULL);
	while (variable[index])
	{
		if (variable[index] == '=')
		{
			end = index;
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

char **ft_triAlpha(char **s)
{
	int j;
	int k;
	char *temp;

	j = 0;
	k = 1;
	while (s[j])
	{
		while(s[k]) // entre dans la boucle meme si s[k] = NULL
		{
			if (ft_strncmp(s[j],s[k], 5) > 0)
			{
				temp = ft_strdup(s[j]);
				s[j] = ft_strdup(s[k]);
				s[k] = ft_strdup(temp);
			}
			k++;
		}
		k = j +1;
		j++;
	}
	s[j] = NULL;
	return (s);
}