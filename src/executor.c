/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:20:31 by jleroux           #+#    #+#             */
/*   Updated: 2022/11/13 16:49:05 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	run(t_cmd *cmds, int i, char **ft_env)
{
	int		status;

	status = 0;
	child_handler();
	cmds[i].pid = fork();
	if (cmds[i].pid == -1)
	{
		perror("Failed to fork");
		return (PIPE_ERR);
	}
	else if (cmds[i].pid == 0)
		child(cmds, i, ft_env);
	return (WEXITSTATUS(status));
}

static int	wait_all(int last, t_cmd *cmds, int errno)
{
	int	status;

	status = 0;
	while (last >= 0 && waitpid(cmds[last].pid, &status, 0) != -1)
	{
		if (cmds[last - 1].piped)
			close(cmds[last].input_fd);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT)
				errno = 130;
			else if (WTERMSIG(status) == SIGQUIT)
			{
				ft_putendl_fd("exit", 2);
				errno = 131;
			}
			last--;
		}
		else
			errno = WEXITSTATUS(status);
	}
	return (errno);
}

static int	execute_cmd(int errno, char ***ft_env, t_cmd *cmds, int i)
{
	char	*shlvl;

	if (cmds[i].piped || !is_builtin(cmds[i].argv[0]))
	{
		if (cmds[i].piped)
		{
			shlvl = ft_itoa(ft_atoi(ft_getenv("SHLVL", *ft_env)) - 1);
			ft_setenv("SHLVL", shlvl, *ft_env);
			ft_free(shlvl);
		}
		errno = run(cmds, i, *ft_env);
		if (cmds[i].piped)
		{
			shlvl = ft_itoa(ft_atoi(ft_getenv("SHLVL", *ft_env)) + 1);
			ft_setenv("SHLVL", shlvl, *ft_env);
			ft_free(shlvl);
		}
	}
	else
		errno = run_builtin(cmds[i].argv, ft_env);
	return (errno);
}

static void	prep_argv(int errno, t_cmd *cmd)
{
	int	j;

	j = -1;
	while (cmd->argv[++j])
	{
		expand_errno(errno, &cmd->argv[j]);
		cmd->argv[j] = strip_quotes(cmd->argv[j]);
	}
}

int	execute(int errno, char ***ft_env, t_cmd *cmds)
{
	int		i;
	int		true_stdin;
	int		true_stdout;

	true_stdin = dup(0);
	true_stdout = dup(1);
	i = -1;
	while (cmds[++i].argv[0])
	{
		prep_argv(errno, &cmds[i]);
		set_io(cmds[i].input_fd, cmds[i].output_fd);
		errno = execute_cmd(errno, ft_env, cmds, i);
		unset_io(cmds[i].input_fd, cmds[i].output_fd);
		set_io(true_stdin, true_stdout);
	}
	unset_io(true_stdin, true_stdout);
	errno = wait_all(i - 1, cmds, errno);
	return (errno);
}
