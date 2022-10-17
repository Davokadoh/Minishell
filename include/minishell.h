/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Blaze <Blaze@42lausanne.ch>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:01:25 by Blaze             #+#    #+#             */
/*   Updated: 2022/10/03 13:56:19 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

typedef struct  s_envp  t_envp;
typedef struct  s_cmd   t_cmd;
struct s_envp
{
    char    *env[31];
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
char	*ft_getenv(char *var, t_envp *env);
t_envp  *init_envp(char **env);
void    ft_setenv(char *var, char *var2, t_envp *env);
void    ft_env(t_envp *env);
void    ft_pwd(void);
void    ft_echo(char *cmd);