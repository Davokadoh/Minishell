/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btchiman <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:41:59 by btchiman          #+#    #+#             */
/*   Updated: 2022/11/10 13:34:49 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_cd(char **args, char **env)
{
	char	*path;
	char	*oldpwd;
	char	*pwd;
	int		errno;

	errno = 0;
	if (args[1] == NULL)
	{
		path = ft_getenv("HOME", env);
		if (path == NULL)
			return (errno); //We return errno but its set to 0 ???
	}
	else if (ft_strncmp(args[1], "-", 1) == 0)
	{
		path = ft_getenv("OLDPWD", env);
		if (path == NULL)
			return (errno);
	}
	else
		path = args[1];
	oldpwd = getcwd(NULL, 0);
	errno = chdir(path);
	pwd = getcwd(NULL, 0);
	ft_setenv("OLDPWD", oldpwd, env);
	ft_setenv("PWD", pwd, env);
	if (errno == -1)
	{
		errno = 1;
		perror(NULL);
	}
	free(oldpwd);
	free(pwd);
	return (errno);
}
