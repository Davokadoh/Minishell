/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:48:20 by jleroux           #+#    #+#             */
/*   Updated: 2022/11/13 16:50:06 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	path_error(char **paths, int i)
{
	if (!paths[i])
	{
		ft_free_tab(paths);
		return (1);
	}
	return (0);
}

static char	*get_path(char *program_name, char **envp)
{
	int		i;
	char	*path;
	char	**paths;

	path = ft_getenv("PATH", envp);
	if (!path)
		return (program_name);
	paths = ft_split(path, ':');
	path = NULL;
	i = -1;
	while (paths[++i])
	{
		paths[i] = ft_append(paths[i], "/");
		paths[i] = ft_append(paths[i], program_name);
		if (access(paths[i], F_OK & X_OK) == 0)
			break ;
	}
	if (path_error(paths, i))
		return (program_name);
	path = ft_strdup(paths[i]);
	ft_free_tab(paths);
	return (path);
}

static int	cmd_error(char *path)
{
	DIR	*dir;

	if (path == NULL || ft_strchr(path, '/') == NULL)
	{
		ft_putstr_fd("mish: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (CMD_NOT_FOUND);
	}
	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		ft_putstr_fd("mish: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": is a directory\n", 2);
		return (IS_A_DIR);
	}
	return (SUCCESS);
}

int	child(t_cmd *cmds, int i, char **ft_env)
{
	char	*path;
	int		error;

	if (cmds[i].piped)
		close(cmds[i + 1].input_fd);
	if (cmds[i].argv[0] != NULL && cmds[i].argv[0][0] != '/' &&
			cmds[i].argv[0][0] != '.')
		path = get_path(cmds[i].argv[0], ft_env);
	else
		path = cmds[i].argv[0];
	error = cmd_error(path);
	if (error)
	{
		ft_free(path);
		exit(error);
	}
	execve(path, cmds[i].argv, ft_env);
	perror(NULL);
	exit(CMD_NOT_FOUND);
}
