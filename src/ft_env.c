/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Blaze <Blaze@42lausanne.ch>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:42:26 by Blaze             #+#    #+#             */
/*   Updated: 2022/10/27 16:17:13 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
}

void	ft_setenv(char *var, char *var2, char **env)
{
	int		i;
	int		n;
	char	*sub;
	char	*sub2;

	i = -1;
	n = ft_strlen(var);
	sub = ft_strjoin(var, "=");
	sub2 = ft_strjoin(sub, var2);
	while (env[++i])
	{
		if (ft_strnstr(env[i], var, n))
		{
			env[i] = sub2;
			break ;
		}
	}
}

// fonction ft_getenv qui doit chercher dans notre copie de envp
char	*ft_getenv(char *var, char **env)
{
	int	i;
	int	n2;

	i = -1;
	n2 = ft_strlen(var);
	while (env[++i])
	{
		if (ft_strnstr(env[i], var, n2))
			return (ft_substr(env[i], n2 + 1, ft_strlen(env[i])));
	}
	return (NULL);
}

char	**init_envp(char **envp)
{
	char	**env;
	int		i;

	i = -1;
	while (envp[++i])
		;
	env = malloc(sizeof(char **) * (i + 1));
	if (!env)
		return (NULL);
	i = -1;
	if (*envp != NULL)
	{
		while (envp[++i])
			env[i] = ft_strdup(envp[i]);
		env[i] = NULL;
	}
	else
	{
		getcwd(env[0], 256);
		env[0] = ft_strjoin("PWD=", env[0]);
		env[1] = ft_strdup("SHLVL=1");
		env[2] = ft_strdup("_=/usr/bin/env");
	}
	return (env);
}
