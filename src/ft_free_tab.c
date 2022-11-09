#include <stdlib.h>
#include "../include/minishell.h"

void	ft_free_tab(char **str)
{
	int	i;

	if (!str)
		return ;
	i = -1;
	while (str[++i])
	{
		if (str[i][0])
			ft_free(str[i]);
	}
	ft_free(str);
}
