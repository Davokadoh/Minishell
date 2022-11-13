#include "../include/minishell.h"

void	set_io(int input_fd, int output_fd)
{
	if (input_fd != 0)
		dup2(input_fd, 0);
	if (output_fd != 1)
		dup2(output_fd, 1);
}

void	unset_io(int input_fd, int output_fd)
{
	if (input_fd != 0)
		close(input_fd);
	if (output_fd != 1)
		close(output_fd);
}
