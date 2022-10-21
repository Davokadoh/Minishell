#include "../include/minishell.h"

static t_cmd	new_cmd()
{
	t_cmd	cmd;

	cmd.argv = malloc(sizeof(char **) * 1024);
	cmd.argv[0] = NULL;
	cmd.input_fd = -1;
	cmd.output_fd = -1;
	cmd.do_run = 1;

	return (cmd);
}

static void	or(t_cmd *cmd)
{
	cmd->do_run = g_errno;
}

static void	add_pipe(t_cmd *cmds, int *a)
{
	int	pipefd[2];

	if (pipe(pipefd) != 0)
		perror("Pipe creation failed!");
	if (cmds[*a].output_fd == -1)
	{
		close(cmds[*a].output_fd);
		cmds[*a].output_fd = pipefd[1];
		cmds[++*a] = new_cmd();
		cmds[*a].input_fd = pipefd[0];
	}
	else
		cmds[++*a] = new_cmd();
}

//Need to unlink heredoc once cmd has been run
static void	heredoc(t_cmd *cmd, char *token)
{
	char	*line;
	int		pipefd[2];
	
	if (pipe(pipefd) != 0)
		perror("Pipe creation failed!");
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
	if (cmd->input_fd != -1)
		close(cmd->input_fd);
	cmd->input_fd = pipefd[0];
	ft_free(line);
}

static void	in(t_cmd *cmd, char *token)
{
	if (cmd->input_fd != -1)
		close(cmd->input_fd);
	if (!access(token, R_OK))
		cmd->input_fd = open(token, O_RDONLY);
}

static void	append(t_cmd *cmd, char *token)
{
	if (cmd->output_fd != -1)
		close(cmd->output_fd);
	if (!access(token, W_OK))
		cmd->output_fd = open(token, O_APPEND);
}

static void	out(t_cmd *cmd, char *token)
{
	if (cmd->output_fd != -1)
		close(cmd->output_fd);
	cmd->output_fd = open(token, O_CREAT, 0666);
}

static void	add_argv(t_cmd *cmd, char *token)
{
	int	i;

	i = -1;
	while(cmd->argv[++i])
		;
	cmd->argv[i] = ft_strdup(token);
	cmd->argv[++i] = NULL;
}

t_cmd	*parse(char **tokens)
{
	int		i;
	int		a;
	t_cmd	*cmds;

	i = -1;
	a = 0;
	cmds = malloc(100 * sizeof(t_cmd *) + 1);
	cmds[a] = new_cmd();
	while (tokens[++i])
	{
		if (tokens[i][0] == '|' && tokens[i][1] == '|')
			or(&cmds[a]);
		else if (tokens[i][0] == '|')
			add_pipe(cmds, &a);
		else if (tokens[i][0] == '<' && tokens[i][1] == '<')
			heredoc(&cmds[a], tokens[++i]);
		else if (tokens[i][0] == '<')
			in(&cmds[a], tokens[++i]);
		else if (tokens[i][0] == '>' && tokens[i][1] == '>')
			append(&cmds[a], tokens[++i]);
		else if (tokens[i][0] == '>')
			out(&cmds[a], tokens[++i]);
		else
			add_argv(&cmds[a], tokens[i]);
	}
	cmds[++a] = new_cmd();
	return (cmds);
}
