/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Blaze <Blaze@42lausanne.ch>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:57:03 by Blaze             #+#    #+#             */
/*   Updated: 2022/11/08 18:44:46 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "env", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 2) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 4) == 0)
		return (1);
	return (0);
}

int	run_builtin(char **argv, t_envp  *envp)
{
	if (ft_strncmp(argv[0], "env", 3) == 0)
		ft_env(envp);
	if (ft_strncmp(argv[0], "pwd", 3) == 0)
		ft_pwd();
	if (ft_strncmp(argv[0], "echo", 5) == 0)
		ft_echo(argv);
	if (ft_strncmp(argv[0], "export", 6) == 0)
		ft_export(argv, envp);
	if (ft_strncmp(argv[0], "unset", 5) == 0)
		ft_unset(argv, envp);
	if (ft_strncmp(argv[0], "cd", 2) == 0)
		ft_cd(argv, envp->env);
	if (ft_strncmp(argv[0], "exit", 4) == 0)
		ft_exit(argv);
	return (0);
}
