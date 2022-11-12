#include "../include/minishell.h"

/*The following is a nice test
 *
 *
 * echo "echo slt
 * echo bjr" | (bash || ./minishell)
 */
static int	from_stdin(int errno, char ***ft_env)
{
	char	*line;

	parent_handler();
	line = readline(NULL);
	printf("\033[A\33[2K\r"); //Should use rl_newline
	fflush(0); // Illegal function!! Replace printf by ft_put_str_fd
	errno = syntax(errno, ft_env, line);
	ft_free(line);
	return (errno);
}

static int	interactive(int errno, char ***ft_env)
{
	char	*line;

	welcome();
	while (1)
	{
		parent_handler();
		line = rl_gets();
		if (!line || !*line) //rm !*line do stop exiting when empty line
		{
			ft_free(line);
			break ;
		}
		errno = syntax(errno, ft_env, line);
		ft_free(line);
	}
	rl_clear_history();
	printf("Goodbye!\n");
	return (errno);
}

int	main(int ac, char **av, char **envp)
{
	int		errno;
	char	**ft_env;

	errno = 0;
	ft_env = init_envp(envp);
	if (ac >= 3 && !ft_strncmp(av[1], "-c", 3))
	{
		parent_handler();
		errno = syntax(errno, &ft_env, av[2]);
	}
	else if (!isatty(0))
		errno = from_stdin(errno, &ft_env);
	else
		errno = interactive(errno, &ft_env);
	ft_free_tab(ft_env);
	return (errno);
}
