/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Blaze <Blaze@42lausanne.ch>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:42:26 by Blaze             #+#    #+#             */
/*   Updated: 2022/11/10 17:04:13 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_env(t_envp  *envp)
{
	int	i;

	i = -1;
	while (envp->env[++i])
	{
		ft_putstr_fd(envp->env[i], 1);
		ft_putstr_fd("\n", 1);
	}
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
	free(sub);
	while (env[++i])
	{
		if (ft_strnstr(env[i], var, n))
		{
			free(env[i]);
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
		if (j == 0 || j != key_len)
			continue ;
		if (ft_strncmp(env[i], key, key_len) == 0)
			return (&env[i][key_len + 1]);
	}
	return (NULL);
}

char	**init_envp(char **envp)
{
	char	**env;
	int		i;

	if (envp != NULL && *envp != NULL)
	{
		i = -1;
		while (envp[++i])
			;
		env = malloc(sizeof(char **) * (i + 1));
		if (!env)
			return (NULL);
		i = -1;
		while (envp[++i])
			env[i] = ft_strdup(envp[i]);
		//env[i-1] = ft_strdup("_=/usr/bin/env");
		env[i] = NULL;
	}
	else
	{
		env = malloc(sizeof(char **) * 4);
		if (!env)
			return (NULL);
		getcwd(env[0], 256);
		env[0] = ft_strjoin("PWD=", env[0]);
		env[1] = ft_strdup("SHLVL=1");
		env[2] = ft_strdup("_=/usr/bin/env");
		env[3] = NULL;
	}
	//ft_setenv("SHLVL", ft_itoa(ft_atoi(ft_getenv("SHLVL", env)) + 1), env);
	return (env);
}
