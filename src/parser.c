#include "../include/minishell.h"

static int	syntax_error(char *token)
{
	//Maybe move to syntax_checker.c
	if (!token)
		token = "newline";
	ft_putstr_fd("msh: syntax error near unexpected token '", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
	return (2); //Change magic number to macro definition
}

static t_cmd	new_cmd(void)
{
	t_cmd	cmd;

	cmd.argv = ft_calloc(1, sizeof(char **));
	cmd.input_fd = 0;
	cmd.output_fd = 1;
	cmd.do_run = 1;
	cmd.piped = 0;
	cmd.pid = -1;
	return (cmd);
}

static int	or(t_cmd **cmds, int *cmd_index, char *token)
{
	int	i;

	if (!token || !ft_isalnum(token[0]))
		return (syntax_error(token));
	cmds[*cmd_index]->do_run = 1;
	i = -1;
	while (cmds[0][++i].argv[0])
		;
	if (cmds[0][i].argv[0] == NULL)
		ft_free_tab(cmds[0][i].argv);
	*cmds = realloc(*cmds, (i + 2) * sizeof(t_cmd));
	cmds[0][++*cmd_index] = new_cmd();
	cmds[0][*cmd_index + 1] = new_cmd();
	return (0); //Change magic number to macro definition
	//needs more work
}

static int	add_pipe(t_cmd **cmds, int *cmd_index, char *token)
{
	int	pipefd[2];
	int	i;

	//Need to find a way to check whether next token is compatible
	if (*cmd_index < 0)
		return (syntax_error(token));
	if (!cmds[0][*cmd_index].argv[0])
		return (syntax_error(token));
	if (pipe(pipefd) != 0)
	{
		perror("Pipe creation failed!"); //Maybe rewrite
		return (1); //Change magic number to macro definition
	}
	i = -1;
	while (cmds[0][++i].argv[0])
		;
	if (cmds[0][i].argv[0] == NULL)
		ft_free_tab(cmds[0][i].argv);
	*cmds = realloc(*cmds, (i + 2) * sizeof(t_cmd)); //Illegal use of realloc
	if (cmds[0][*cmd_index].output_fd == 1)
	{
		cmds[0][*cmd_index].piped = 1;
		cmds[0][*cmd_index].output_fd = pipefd[1];
		cmds[0][++*cmd_index] = new_cmd();
		cmds[0][*cmd_index].input_fd = pipefd[0];
	}
	else
		cmds[0][++*cmd_index] = new_cmd();
	cmds[0][*cmd_index + 1] = new_cmd();
	return (0);
}

//Close fd[0] once cmd has run ?
static int	heredoc(t_cmd *cmd, char *token)
{
	char	*line;
	int		pipefd[2];

	if (!token || !ft_isalnum(token[0]))
		return (syntax_error(token));
	if (!pipe(pipefd))
	{
		perror("Pipe creation failed!");
		return (3); //Change magic number to macro definition
	}
	while (1)
	{
		line = readline("> ");
		if (!ft_strncmp(line, token, ft_strlen(token) + 1))
			break ;
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 2);
		ft_free(line);
	}
	close(pipefd[1]);
	if (cmd->input_fd != 0)
		close(cmd->input_fd);
	cmd->input_fd = pipefd[0];
	ft_free(line);
	return (0); //Change magic number to macro definition
}

static int	in(t_cmd *cmd, char *token)
{
	if (!token || !ft_isalnum(token[0]))
		return (syntax_error(token));
	if (cmd->input_fd != 0)
		close(cmd->input_fd);
	if (!access(token, R_OK))
		cmd->input_fd = open(token, O_RDONLY);
	return (0);
}

static int	append(t_cmd *cmd, char *token)
{
	if (!token || !ft_isalnum(token[0]))
		return (syntax_error(token));
	if (cmd->output_fd != 1)
		close(cmd->output_fd);
	if (!access(token, W_OK))
		cmd->output_fd = open(token, O_APPEND);
	return (0); //Change magic number to macro definition
}

static int	out(t_cmd *cmd, char *token)
{
	if (!token || !ft_isalnum(token[0]))
		return (syntax_error(token));
	if (cmd->output_fd != 1)
		close(cmd->output_fd);
	cmd->output_fd = open(token, O_TRUNC | O_CREAT | O_WRONLY, 0666);
	return (0); //Change magic number to macro definition
}

static void	add_argv(t_cmd *cmd, char *token)
{
	int	i;

	i = -1;
	while (cmd->argv[++i])
		;
	cmd->argv = realloc(cmd->argv, (i + 2) * sizeof(char **));
	cmd->argv[i] = ft_strdup(token);
	cmd->argv[++i] = NULL;
}

static void	ft_free_cmds(t_cmd **cmds)
{
	size_t	i;

	i = -1;
	while ((*cmds)[++i].argv[0] != NULL)
		ft_free_tab((*cmds)[i].argv);
	ft_free_tab((*cmds)[i].argv);
	free((*cmds));
}

int		parse(int errno, t_envp *ft_env, char **tokens)
{
	int		new_errno;
	int		i;
	int		cmd_index;
	t_cmd	*cmds;

	cmds = ft_calloc(2, sizeof(t_cmd));
	cmds[0] = new_cmd();
	cmds[1] = new_cmd();
	if (!cmds)
		return (1);
	new_errno = 0;
	cmd_index = 0;
	i = -1;
	while (tokens && tokens[++i] && !new_errno)
	{
		if (tokens[i][0] == '|' && tokens[i][1] == '|')
			new_errno = or(&cmds, &cmd_index, tokens[i]);
		else if (tokens[i][0] == '|')
			new_errno = add_pipe(&cmds, &cmd_index, tokens[i]);
		else if (tokens[i][0] == '<' && tokens[i][1] == '<')
			new_errno = heredoc(&cmds[cmd_index], tokens[++i]);
		else if (tokens[i][0] == '<')
			new_errno = in(&cmds[cmd_index], tokens[++i]);
		else if (tokens[i][0] == '>' && tokens[i][1] == '>')
			new_errno = append(&cmds[cmd_index], tokens[++i]);
		else if (tokens[i][0] == '>')
			new_errno = out(&cmds[cmd_index], tokens[++i]);
		else
			add_argv(&cmds[cmd_index], tokens[i]); //Add error handling
	}
	i = -1;
	while (cmds[++i].argv[0])
		;
	if (cmds[i].argv[0] != NULL)
		cmds[++cmd_index] = new_cmd();
	if (new_errno)
	{
		if (cmds[0].argv[0] == NULL)
			ft_free_tab(cmds[1].argv);
		ft_free_cmds(&cmds);
		return (new_errno);
	}
	errno = execute(errno, ft_env, cmds);
	ft_free_cmds(&cmds);
	return (errno);
}
