#include "../include/minishell.h"

static t_cmd	new_cmd()
{
	t_cmd	cmd;

	cmd.argv = ft_calloc(1, sizeof(char **));
	cmd.input_fd = 0;
	cmd.output_fd = 1;
	cmd.do_run = 1;
	return (cmd);
}

static void	or(int errno, t_cmd *cmd)
{
	cmd->do_run = errno;
}

static int	add_pipe(t_cmd **cmds, int *cmd_index)
{
	int	pipefd[2];
	int i;

	if (!cmds[0][*cmd_index + 1].argv[0])
		return (2); //Change magic number to macro definition
	if (pipe(pipefd) != 0)
		perror("Pipe creation failed!");
	i = -1;
	while(cmds[0][++i].argv[0])
		;
	if (cmds[0][i].argv[0] == NULL)
		ft_free_tab(cmds[0][i].argv);
	*cmds = realloc(*cmds, (i + 2) * sizeof(t_cmd));
	if (cmds[0][*cmd_index].output_fd == 1)
	{
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

	if (!token)
		return (2); //Change magic number to macro definition
	if (!ft_isalnum(token[0]))
	{
		perror("Syntax error\n");
		return (2); //Change magic number to macro definition
	}
	if (!pipe(pipefd))
	{
		perror("Pipe creation failed!");
		return (2); //Change magic number to macro definition
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

static void	in(t_cmd *cmd, char *token)
{
	if (cmd->input_fd != 0)
		close(cmd->input_fd);
	if (!access(token, R_OK))
		cmd->input_fd = open(token, O_RDONLY);
}

static void	append(t_cmd *cmd, char *token)
{
	if (cmd->output_fd != 1)
		close(cmd->output_fd);
	if (!access(token, W_OK))
		cmd->output_fd = open(token, O_APPEND);
}

static void	out(t_cmd *cmd, char *token)
{
	if (cmd->output_fd != 1)
		close(cmd->output_fd);
	cmd->output_fd = open(token, O_TRUNC | O_CREAT | O_WRONLY, 0666);
}

static void	add_argv(t_cmd *cmd, char *token)
{
	int	i;

	i = -1;
	while(cmd->argv[++i])
		;
	cmd->argv = realloc(cmd->argv, (i + 2) * sizeof(char **));
	cmd->argv[i] = ft_strdup(token);
	cmd->argv[++i] = NULL;
}

#ifndef MALLOC_ERROR
# define MALLOC_ERROR 4
#endif

int		parse(int errno, char **ft_env, char **tokens)
{
	int		new_errno;
	int		i;
	int		cmd_index;
	t_cmd	*cmds;

	cmds = ft_calloc(2, sizeof(t_cmd));
	if (!cmds)
		return (ft_error(MALLOC_ERROR)); //Should move macro definition to header file
	i = -1;
	new_errno = 0;
	cmd_index = 0;
	while (tokens[++i] && !new_errno)
	{
		if (tokens[i][0] == '|' && tokens[i][1] == '|')
			or(errno, &cmds[cmd_index]); //Add error handling
		else if (tokens[i][0] == '|')
			new_errno = add_pipe(&cmds, &cmd_index); //Add error handling
		else if (tokens[i][0] == '<' && tokens[i][1] == '<')
			new_errno = heredoc(&cmds[cmd_index], tokens[++i]); //Add error handling
		else if (tokens[i][0] == '<')
			in(&cmds[cmd_index], tokens[++i]); //Add error handling
		else if (tokens[i][0] == '>' && tokens[i][1] == '>')
			append(&cmds[cmd_index], tokens[++i]); //Add error handling
		else if (tokens[i][0] == '>')
			out(&cmds[cmd_index], tokens[++i]); //Add error handling
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
		//ft_free_cmds(cmds);
		return (new_errno);
	}
	errno = execute(errno, ft_env, cmds);
	//ft_free_cmds(cmds);
	return (errno);
}
