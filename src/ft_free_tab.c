#include <stdlib.h>
#include "../include/minishell.h"

void	ft_free_tab(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (*str[i])
			ft_free(str[i]);
	}
}