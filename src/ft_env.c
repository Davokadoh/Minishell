/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Blaze <Blaze@42lausanne.ch>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:42:26 by Blaze             #+#    #+#             */
/*   Updated: 2022/11/07 17:32:55 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		ft_putstr_fd(env[i], 1);
		ft_putstr_fd("\n", 1);
	}
}

void	ft_setenv(char *var, char *var2, char ***env)
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
char	*ft_getenv(char *key, char **env)
{
	int	i;
	int	j;
	int	key_len;

	i = -1;
	key_len = ft_strlen(key);
	while (env[++i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		if (j == 0)
			continue ;
		if (ft_strncmp(key, env[i], key_len) == 0)
			return (ft_substr(env[i], key_len + 1, ft_strlen(env[i])));
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
