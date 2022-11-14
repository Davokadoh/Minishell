#include "../include/minishell.h"

static int	from_stdin(int errno, t_envp *ft_env)
{
	char	*line;

	parent_handler();
	line = readline(NULL);
	while (line)
	{
		printf("\033[A\33[2K\r"); //Should use rl_newline
		fflush(0); // Illegal function!! Replace printf by ft_put_str_fd
		errno = quotes(errno, ft_env, line);
		ft_free(line);
		line = readline(NULL);
	}
	return (errno);
}

static int	interactive(int errno, t_envp *ft_env)
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
		errno = quotes(errno, ft_env, line);
		ft_free(line);
	}
	rl_clear_history();
	printf("Goodbye!\n");
	return (errno);
}

int	main(int ac, char **av, char **envp)
{
	int		errno;
	t_envp  env_ex;
	
	env_ex.env = init_envp(envp);
	errno = 0;
	if (ac >= 3 && !ft_strncmp(av[1], "-c", 3))
	{
		parent_handler();
		errno = quotes(errno, &env_ex, av[2]);
	}
	else if (!isatty(0))
		errno = from_stdin(errno, &env_ex);
	else
		errno = interactive(errno, &env_ex);
	//ft_free_tab(env_ex.env);
	//ft_free_tab(env_ex.exp_init);
	//ft_free_tab(env_ex.exp_lst);
	return (errno);
}
