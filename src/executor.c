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
	if (input_fd != 1)
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

	i = -1;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
			paths = ft_split(envp[i] + 5, ':');
	}
	i = -1;
	while (paths[++i])
	{
		paths[i] = ft_append(paths[i], "/"); //diff w/ ft_strjoin ?
		paths[i] = ft_append(paths[i], program_name); //diff w/ ft_strjoin ?
		if (access(paths[i], F_OK) == 0)
			break ;
	}
	if (path_error(paths, i))
		return (NULL);
	path = ft_strdup(paths[i]);
	ft_free_tab(paths);
	return (path);
}

static int	is_dir(const char *path) //should be in libft
{
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}

static int cmd_error(char *path)
{
	int		err_code;
	int		dir;
	int		fd;

	err_code = 0,
	fd = open(path, O_RDONLY);
	dir = is_dir(path);
	if (ft_strchr(path, '/') == NULL)
		err_code = ft_error(127); // 127 SEEMS to be the errno for command not found
	else if (fd == -1 && !dir)
		err_code = ft_error(129); // Define a macro in .h ?
	else if (fd == -1 && dir)
		err_code = ft_error(123); // Define a macro in .h ?
	else if (fd != -1 && dir)
		err_code = ft_error(111); // Define a macro in .h ?
	if (fd)
		close(fd);
	return (err_code);
}

static int	run(char **argv, char **ft_env)
{
	pid_t	pid;
	char	*path;
	int		status;
	int		error;

	status = 0;
	pid = fork();
	if (pid == -1)
	{
		perror("Failed to fork");
		return (66); // Define a macro in .h ?
	}
	else if (pid == 0)
	{
		path = get_path(argv[0], ft_env);
		error = cmd_error(path);
		if (error)
		{
			ft_free(path);
			exit(error);
		}
		execve(path, argv, ft_env);
		exit(127); // Define a macro in .h ?
	}
	waitpid(pid, &status, 0);
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
		token = realloc(token, sizeof(char *) * (ft_strlen(token) - 2));
		ft_strlcpy(token, tmp, ft_strlen(tmp) + 1);
		token[ft_strlen(tmp)] = '\0'; //Maybe useless because we use strLcpy
		i = j - 2;
	}
	return (token);
}

static void	print_cmd(t_cmd cmd) //Just 4 testing, rm before eval
{
	int	i = -1;

	while (cmd.argv[++i])
		fprintf(stderr, "cmd.argv[%i]:%s\n", i, cmd.argv[i]);
	fprintf(stderr, "in:%d\n", cmd.input_fd);
	fprintf(stderr, "out:%d\n", cmd.output_fd);
	fprintf(stderr, "do_run:%d\n", cmd.do_run);
	fprintf(stderr, "\n");
}

int	execute(int errno, char **ft_env, t_cmd *cmds)
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
		print_cmd(cmds[i]);
		j = -1;
		while (cmds[i].argv[++j])
		{
			expand_errno(errno, &cmds[i].argv[j]);
			cmds[i].argv[j] = strip_quotes(cmds[i].argv[j]);
		}
		set_io(cmds[i].input_fd, cmds[i].output_fd, true_stdin, true_stdout);
		if (is_builtin(cmds[i].argv[0]))
			errno = run_builtin(cmds[i].argv, ft_env);
		else
			errno = run(cmds[i].argv, ft_env);
		unset_io(cmds[i].input_fd, cmds[i].output_fd);
	}
	set_io(true_stdin, true_stdout, true_stdin, true_stdout);
	return (errno);
}
