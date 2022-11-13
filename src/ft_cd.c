/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btchiman <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:41:59 by btchiman          #+#    #+#             */
/*   Updated: 2022/11/13 17:03:52 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*get_path(char **args, char **env)
{
	char	*path;

	if (args[1] == NULL)
		path = ft_getenv("HOME", env);
	else if (ft_strncmp(args[1], "-", 1) == 0)
		path = ft_getenv("OLDPWD", env);
	else
		path = args[1];
	return (path);
}

int	ft_cd(char **args, char **env)
{
	char	*path;
	char	*oldpwd;
	char	*pwd;
	int		errno;

	errno = 0;
	path = get_path(args, env);
	if (!path)
		return (0);
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
