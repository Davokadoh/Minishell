#include "../include/minishell.h"

int	g_errno;

#define TEST 0

static void	print_tab(char **tokens, char *part_name)
{
	int	i;

	if (TEST)
	{
		printf("%s", part_name);
		i = -1;
		while (tokens[++i])
			printf("'%s'\n", tokens[i]);
		printf("\n");
	}
}

static int	launch_minishell(char *line, char ***ft_env)
{
	char	**tokens;
	t_cmd	*cmds;
	int		i;
	
	//Warning: Check some syntax errors beforehand
	if (TEST)
		printf("LINE:\n%s\n\n", line);
	line = expand(ft_strdup(line), *ft_env);
	if (TEST)
		printf("EXPANDER:\n%s\n\n", line);
	tokens = lex(line);
	ft_free(line);
	print_tab(tokens, "LEXER:\n");
	i = -1;
	cmds = parse(tokens);
	ft_free_tab(tokens);
	if (TEST)
	{
		i = -1;
		printf("PARSER:\n");
		while (cmds[++i].argv[0])
			print_tab(cmds[i].argv, "PARSER cmd:\n");
	}
	execute(cmds, ft_env);
	if (TEST)
	{
		i = -1;
		printf("EXEC:\n");
		while (cmds[++i].argv[0])
			print_tab(cmds[i].argv, "EXEC cmd:\n");
	}
	i = -1;
	while (cmds[++i].argv[0])
		ft_free_tab(cmds[i].argv);
	ft_free_tab(cmds[i].argv);
	ft_free(cmds);
	return (0);
}

//Warnings!
//env -i ./minishell
int	main(int ac, char **av, char **envp)
{
	char	*line;
	char	**ft_env;

	ft_env = init_envp(envp);
	if (ac >= 3 && !ft_strncmp(av[1], "-c", 3))
	{
		g_errno = launch_minishell(av[2], &ft_env);
		ft_free_tab(ft_env);
		return (g_errno);
	}
	if (!isatty(0))
	{
		line = readline(NULL);
		printf("\033[A\33[2K\r");
		fflush(0);
		g_errno = launch_minishell(line, &ft_env);
		ft_free(line);
		ft_free_tab(ft_env);
		return (g_errno);
	}
	welcome();
	while (1)
	{
		line = rl_gets();
		if (!line || !*line) //rm !*line do stop exiting
		{
			ft_free(line);
			break ;
		}
		g_errno = launch_minishell(line, &ft_env);
		ft_free(line);
	}
	ft_free_tab(ft_env);
	//rl_clear_history();
	printf("Goodbye!\n");
	return (g_errno);
}
