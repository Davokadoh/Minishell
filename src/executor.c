#include "../include/minishell.h"

static void	set_io(int input_fd, int output_fd, int true_stdin, int true_stdout)
{
	if (input_fd != 0)
		dup2(input_fd, 0);
	else
		dup2(true_stdin, 0);
	if (output_fd != 1)
		dup2(output_fd, 1);
	else
		dup2(true_stdout, 1);
}

static void	unset_io(int input_fd, int output_fd)
{
	if (input_fd != 0)
		close(input_fd);
	if (output_fd != 1)
		close(output_fd);
}

static int	path_error(char **paths, int i)
{
	if (!paths[i])
	{
		ft_free_tab(paths);
		perror("Command not found");
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
		return (NULL);
	path = ft_strdup(paths[i]);
	ft_free_tab(paths);
	return (path);
}

static int	run(char **argv, char ***ft_env)
{
	pid_t	pid;
	char	*path;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
	{
		perror("Failed to fork");
		return (66);
	}
	else if (pid == 0)
	{
		path = get_path(argv[0], *ft_env);
		if (!path)
			return (67);
		execve(path, argv, *ft_env);
		perror("Failed to execve");
		return (127);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

/*
int is_builtin(char *cmd)
{
    if (!ft_strncmp(cmd, "echo", 4) || !ft_strncmp(cmd, "cd", 2) || !ft_strncmp(cmd, "pwd", 3)
    || !ft_strncmp(cmd, "export", 6) || !ft_strncmp(cmd, "unset", 5) || !ft_strncmp(cmd, "env", 3)
    || !ft_strncmp(cmd, "exit", 4))
        return (1);
    return (0);
}
*/

static void	expand_errno(char **token)
{
	int				i;
	unsigned int	s_quotes;

	s_quotes = 0;
	i = -1;
	while (token[0][++i])
	{
		if (token[0][i] == '\'')
			s_quotes = (s_quotes + 1) % 2;
		if (token[0][i] == '$' && token[0][i + 1] == '?' && !s_quotes)
			*token = ft_strinsert(token[0], ft_itoa(g_errno), i, i + 2);
	}
}
/*
static char	*strip_quotes(char *token)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1; 
	while (token[++i]) // -> heap-buffer-overflow
	{
		while (token[i] && token [i] != '"' && token [i] != '\'')
			i++;
		j = i + 1;
		if (token[i] == '"')
			while (token[j] && token [j] != '"')
				j++;
		else if (token[i] == '\'')
			while (token[j] && token [j] != '\'')
				j++;
		else
			continue ;
		tmp = malloc(sizeof(char *) * (ft_strlen(token) - 2));
		ft_strlcpy(tmp, token, i + 1);
		ft_strlcpy(&tmp[i], &token[i + 1], j - i);
		ft_strlcpy(&tmp[j - 1], &token[j + 1], ft_strlen(token) - j);
		token = realloc(token, sizeof(char *) * (ft_strlen(token) - 2));
		ft_strlcpy(token, tmp, ft_strlen(tmp) + 1);
		token[ft_strlen(tmp)] = '\0';
		i = j - 2;
	}
	return (token);
}*/

int	execute(t_cmd *cmds, t_envp  *ft_env)
{
	int	i;
	int	j;
	int	true_stdin;
	int	true_stdout;

	true_stdin = dup(0);
	true_stdout = dup(1);
	i = -1;
	while (cmds[++i].argv[0])
	{
		j = -1;
		while (cmds[i].argv[++j])
		{
			expand_errno(&cmds[i].argv[j]);
			//cmds[i].argv[j] = strip_quotes(cmds[i].argv[j]);
		}
		set_io(cmds[i].input_fd, cmds[i].output_fd, true_stdin, true_stdout);
		if (is_builtin(cmds[i].argv[0]))
			g_errno = run_builtin(cmds[i].argv, ft_env);
		else
			g_errno = run(cmds[i].argv, &ft_env->env);
		unset_io(cmds[i].input_fd, cmds[i].output_fd);
	}
	wait(NULL);
	return (g_errno);
}
