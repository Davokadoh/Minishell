#include "../include/minishell.h"

/*The following is a nice test
 *
 *
 * echo "echo slt
 * echo bjr" | (bash || ./minishell)
 */
static int	from_stdin(int errno, t_envp *ft_env)
{
	char	*line;

	line = readline(NULL);
	printf("\033[A\33[2K\r"); //Should use rl_newline
	fflush(0); // Illegal function!! Replace printf by ft_put_str_fd
	errno = syntax(errno, ft_env, line);
	ft_free(line);
	return (errno);
}

static int	interactive(int errno, t_envp *ft_env)
{
	char	*line;
	welcome();
	while (1)
	{
		line = rl_gets();
		if (!line || !*line) //rm !*line do stop exiting when empty line
		{
			ft_free(line);
			break ;
		}
		errno = syntax(errno, ft_env, line);
		ft_free(line);
	}
	//rl_clear_history();
	printf("Goodbye!\n");
	return (errno);
}

void	sig_parrent(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	parrent_handler(void)
{
	struct termios	terminos;

	tcgetattr(0, &terminos);
	terminos.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &terminos);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &sig_parrent);
}

int	main(int ac, char **av, char **envp)
{
	int		errno;
	t_envp  env_ex;
	
	env_ex.env = init_envp(envp);
	errno = 0;
	parrent_handler();
	if (ac >= 3 && !ft_strncmp(av[1], "-c", 3))
		errno = syntax(errno, &env_ex, av[2]);
	else if (!isatty(0))
		errno = from_stdin(errno, &env_ex);
	else
		errno = interactive(errno, &env_ex);
	ft_free_tab(env_ex.env);
	ft_free_tab(env_ex.exp_init);
	ft_free_tab(env_ex.exp_lst);
	return (errno);
}
