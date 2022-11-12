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
		return (1);
	}
	return (0);
}

static char	*get_path(char *program_name, char **envp)
{
	int		i;
	char	*path;
	char	**paths;

	//Use ft_getenv instead!!!!!
	i = -1;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
			paths = ft_split(envp[i] + 5, ':');
	}
	//Use ft_getenv instead!!!!!
	i = -1;
	while (paths[++i])
	{
		paths[i] = ft_append(paths[i], "/"); //diff w/ ft_strjoin ?
		paths[i] = ft_append(paths[i], program_name); //diff w/ ft_strjoin ?
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
		return (127); //Change magic number to macro
	}
	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		ft_putstr_fd("mish: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": is a directory\n", 2);
		return (126); //Change magic number to macro
	}
	return (0); //Change magic number to macro
}

static int	run(t_cmd *cmd, char **ft_env)
{
	char	**argv;
	char	*path;
	int		status;
	int		error;

	argv = cmd->argv; //can be scraped
	status = 0;
	child_handler();
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		perror("Failed to fork");
		return (66); // Define a macro in .h ?
	}
	else if (cmd->pid == 0)
	{
		if (argv[0] != NULL && argv[0][0] != '/' && argv[0][0] != '.')
			path = get_path(argv[0], ft_env);
		else
			path = argv[0];
		error = cmd_error(path);
		if (error)
		{
			ft_free(path);
			exit(error);
		}
		execve(path, argv, ft_env);
		perror(NULL);
		exit(127); // Define a macro in .h ?
	}
	return (WEXITSTATUS(status));
}

static void	expand_errno(int errno, char **token)
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
			*token = ft_strinsert(token[0], ft_itoa(errno), i, i + 2);
	}
}

static char	*strip_quotes(char *token)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (token[++i])
	{
		while (token[i] && token[i] != '"' && token[i] != '\'')
			i++;
		j = i + 1;
		if (token[i] == '"')
			while (token[j] && token[j] != '"')
				j++;
		else if (token[i] == '\'')
			while (token[j] && token[j] != '\'')
				j++;
		else
			break ;
		tmp = malloc(sizeof(char *) * (ft_strlen(token) - 2));
		ft_strlcpy(tmp, token, i + 1);
		ft_strlcpy(&tmp[i], &token[i + 1], j - i);
		ft_strlcpy(&tmp[j - 1], &token[j + 1], ft_strlen(token) - j);
		token = realloc(token, sizeof(char *) * (ft_strlen(token) - 2)); //Illegal use of realloc
		ft_strlcpy(token, tmp, ft_strlen(tmp) + 1);
		ft_free(tmp);
		i = j - 2;
	}
	return (token);
}

static int	wait_all(int last, t_cmd *cmds, int errno)
{
	int	status;
	int	i;

	status = 0;
	waitpid(cmds[last].pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			errno = 130;
		else if (WTERMSIG(status) == SIGQUIT)
		{
			ft_putendl_fd("exit", 2);
			errno = 131;
		}
	}
	else
		errno = WEXITSTATUS(status);
	i = 0;
	while (i < last && waitpid(cmds[i].pid, &status, 0) != -1)
	{
		if (WIFSIGNALED(status) && WTERMSIG(status) != SIGPIPE)
			break ;
		i++;
	}
	return (errno);
}

int	execute(int errno, char ***ft_env, t_cmd *cmds)
{
	int		i;
	int		j;
	int		true_stdin;
	int		true_stdout;

	true_stdin = dup(0);
	true_stdout = dup(1);
	i = -1;
	while (cmds[++i].argv[0])
	{
		j = -1;
		while (cmds[i].argv[++j])
		{
			expand_errno(errno, &cmds[i].argv[j]);
			cmds[i].argv[j] = strip_quotes(cmds[i].argv[j]);
		}
		set_io(cmds[i].input_fd, cmds[i].output_fd, true_stdin, true_stdout);
		if (cmds[i].piped || !is_builtin(cmds[i].argv[0]))
		{
			//if (cmds[i].piped)
			//{
			//	shlvl = ft_itoa(ft_atoi(ft_getenv("SHLVL", env)) - 1);
			//	ft_setenv("SHLVL", shlvl, env);
			//	ft_free(shlvl);
			//}
			errno = run(&cmds[i], *ft_env);
			//if (cmds[i].piped)
			//{
			//	shlvl = ft_itoa(ft_atoi(ft_getenv("SHLVL", env)) + 1);
			//	ft_setenv("SHLVL", shlvl, env);
			//	ft_free(shlvl);
			//}
		}
		else
			errno = run_builtin(cmds[i].argv, ft_env);
		unset_io(cmds[i].input_fd, cmds[i].output_fd);
	}
	set_io(true_stdin, true_stdout, true_stdin, true_stdout);
	errno = wait_all(i - 1, cmds, errno);
	return (errno);
}
