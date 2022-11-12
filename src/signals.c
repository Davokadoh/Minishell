#include "../include/minishell.h"

static void	sig_parent(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	parent_handler(void)
{
	struct termios	terminos;

	tcgetattr(0, &terminos);
	terminos.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &terminos);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &sig_parent);
}

static	void	sig_child(int sig)
{
	(void) sig;
	parent_handler();
}

void	child_handler(void)
{
	struct termios	terminos;

	tcgetattr(0, &terminos);
	terminos.c_lflag &= ~ECHOCTL;
	//tcsetattr(0, TCSANOW, &terminos); //If uncommented valgrind says uninit byte(s)
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, &sig_child);
}
