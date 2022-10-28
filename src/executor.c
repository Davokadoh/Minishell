#include "../include/minishell.h"

static void	set_io(int input_fd, int output_fd)
{
	if (input_fd != -1)
		dup2(input_fd, 0);
	if (output_fd != -1)
		dup2(output_fd, 1);
}

static int	path_error(char **paths, int i)
{
	if (!paths[i])
	{
		ft_free_tab(paths);
		perror("command not found\n");
		return (1);
	}
	return (0);
}

static char	*get_path(char *program_name, char **envp)
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

static int	run(t_cmd cmd, char **argv, char ***ft_env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Failed to fork\n");
		return (66);
	}
	else if (pid == 0)
	{
		set_io(cmd.input_fd, cmd.output_fd);
		execve(get_path(argv[0], *ft_env), argv, *ft_env);
		perror("Failed to execve\n");
		return (127);
	}
	return (0);
}
/*int is_builtin(char *cmd)
{
    if (!ft_strncmp(cmd, "echo", 4) || !ft_strncmp(cmd, "cd", 2) || !ft_strncmp(cmd, "pwd", 3)
    || !ft_strncmp(cmd, "export", 6) || !ft_strncmp(cmd, "unset", 5) || !ft_strncmp(cmd, "env", 3)
    || !ft_strncmp(cmd, "exit", 4))
        return (1);
    return (0);
}*/

int	execute(t_cmd *cmds, char ***ft_env)
{
	int	i;
	int	status;

	i = -1;
	status = 0;
	while (cmds[++i].argv[0])
	{
		if (is_builtin(cmds[i].argv[0]))
			g_errno = run_builtin(cmds[i].argv, ft_env);
		else
			g_errno = run(cmds[i], cmds[i].argv, ft_env);
	}
	wait(&status);
	return (0);
}
