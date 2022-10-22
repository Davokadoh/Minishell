#include "../include/minishell.h"

static void	unset_io(int input_fd, int output_fd)
{
	close(input_fd);
	close(output_fd);
}

static void	set_io(int input_fd, int output_fd)
{
	if (input_fd != -1)
		dup2(input_fd, 0);
	if (output_fd != -1)
		dup2(output_fd, 1);
}

int	path_error(char **paths, int i)
{
	if (!paths[i])
	{
		ft_free_tab(paths);
		perror("command not found\n");
		return (1);
	}
	return (0);
}

char	*get_path(char *program_name, char **envp)
{
	int		i;
	char	*path;
	char	**paths;

	i = -1;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
			paths = ft_split(envp[i] + 5, ':');
	}
	i = -1;
	while (paths[++i])
	{
		paths[i] = ft_append(paths[i], "/");
		paths[i] = ft_append(paths[i], program_name);
		if (access(paths[i], F_OK | X_OK) == 0)
			break ;
	}
	if (path_error(paths, i))
	{
		ft_free_tab(paths);
		return (NULL);
	}
	path = ft_strdup(paths[i]);
	ft_free_tab(paths);
	return (path);
}

int	run(t_cmd cmd, int argc, char **argv, char **ft_env)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid != 0)
	{
		set_io(cmd.input_fd, cmd.output_fd);
		dprintf(0, "cmd:%s\n", cmd.argv[0]);
		if (execve(get_path(argv[0], ft_env), argv, ft_env) == -1)
		{
			perror(NULL);
			return (127);
		}
		return (0);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (0);
	}
}

int	tab_len(char **tab)
{
	int	i;
	
	i = -1;
	while (tab[++i])
		;
	return (i);
}

int	execute(t_cmd *cmds, char **ft_env)
{
	int	i;

	i = -1;
	while (cmds[++i].argv[0])
	{
		//if (is_builtin())
		//	run_builtin();
		//else
			g_errno = run(cmds[i], tab_len(cmds[i].argv), cmds[i].argv, ft_env);
		unset_io(cmds[i].input_fd, cmds[i].output_fd);
	}
	return (0);
}
