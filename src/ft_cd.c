/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btchiman <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:41:59 by btchiman          #+#    #+#             */
/*   Updated: 2022/11/02 18:30:02 by btchiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_cd(char **args, char **env)
{
    char	*path;
    char	*oldpwd;
    char	*pwd;
	int		errno;

    if (args[1] == NULL)
    {
        path = ft_getenv("HOME", env);
        if (path == NULL)
            return ;
    }
    else if (ft_strncmp(args[1], "-",1) == 0)
    {
        path = ft_getenv("OLDPWD", env);
        if (path == NULL)
            return ;
    }
    else
        path = args[1];
    oldpwd = ft_getenv("PWD", env);
    pwd = getcwd(NULL, 0);
    ft_setenv("OLDPWD", oldpwd, env);
    ft_setenv("PWD", pwd, env);
    errno = chdir(path);
    free(oldpwd);
    free(pwd);
	return (errno);
}
