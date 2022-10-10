/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Blaze <Blaze@42lausanne.ch>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:01:25 by Blaze             #+#    #+#             */
/*   Updated: 2022/10/07 15:18:40 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

typedef struct	s_envp  t_envp;
typedef struct s_cmd    t_cmd;
struct s_envp
{
    char	*key[3];
    char	*value[3];
};
struct	s_cmd
{
    char	*argv;
    char	*input_name;
    char	*output_name;
    int		input_fd;
    int		output_fd;
};

char	*rl_gets(void);
void	welcome(void);
char	*expand(char **str);
char	**lex(const char *str);
