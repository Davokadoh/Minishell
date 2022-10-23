#include "../include/minishell.h"

//int	g_errno = 0;

#define test 0
void	print_tab(char **tokens, char *part_name)
{
	if (test)
	{
		printf("%s:\n", part_name);
		for (int i = 0; tokens[i]; i++)
			printf("%s\n", tokens[i]);
		printf("\n");
	}
}

static int	launch_minishell(char *line, char **envp)
{
	char	**tokens;
	t_cmd	*cmds;
	int i = -1;

	tokens = lex(line); //Warning: Check some syntax errors beforehand
	print_tab(tokens, "LEXER");
	while (tokens[++i])
		expand(&tokens[i]);//, envp);
	print_tab(tokens, "EXPANDER");
	cmds = parse(tokens); //Create a list of cmds w/ corresponding i/o
	ft_free_tab(tokens);
	ft_free(tokens);
	i = -1;
	if (test)
	{
		printf("PARSER:\n");
		while (cmds[++i].argv[0])
		{
			int j = -1;
			while (cmds[i].argv[++j])
				printf("cmd[%i] argv[%i] %s\n", i, j, cmds[i].argv[j]);
		}
		printf("\n");
	}
	else
		while (cmds[++i].argv[0])
			;
	execute(cmds, envp);
	i = -1;
	while (cmds[++i].argv[0])
	{
		ft_free_tab(cmds[i].argv);
		ft_free(cmds[i].argv);
	}
	ft_free_tab(cmds[i].argv);
	ft_free(cmds[i].argv);
	ft_free(cmds);

	return (0);
}

//Warnings!
//env -i ./minishell
int	main(int ac, char **av, char **envp)
{
	char	*line;
	int		line_counter;

	if (ac >= 3 && !ft_strncmp(av[1], "-c", 3))
		return (launch_minishell(av[2], envp));
	if (!isatty(0))
	{
		line = readline(NULL);
		g_errno = launch_minishell(line, envp);
		ft_free(line);
		printf("\033[A\33[2K\r");
		fflush(0);
		return (g_errno);
	}
	welcome();
	line_counter = 0;
	while (line_counter < 3)
	{
		line = rl_gets();
		if (!line || !*line)
		{
			ft_free(line);
			break ;
		}
		g_errno = launch_minishell(line, envp);
		ft_free(line);
		line_counter++;
	}
	rl_clear_history();
	printf("Goodbye!\n");
	return (g_errno);
}
