/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Blaze <Blaze@42lausanne.ch>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:01:25 by Blaze             #+#    #+#             */
/*   Updated: 2022/10/24 15:15:01 by btchiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

typedef struct  s_cmd   t_cmd;
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
char	*expand(char **tokens);
char	**lex(const char *str);
char	*ft_getenv(char *var, char **env);
char    **init_envp(char **env);
void    ft_setenv(char *var, char *var2, char **env);
void    ft_env(char **env);
void    ft_pwd(void);
int     ft_echo(char **args);
void	ft_cd(char **args, char **env);
int     builtin(char **tokens, char ***env);
char    **ft_export(char **args, char **env);
char	**ft_unset(char **args, char **env);
void	ft_exit(void);

// utils
char **ft_increnv(char **env, char *new_entry);
char *malloc_substrcpy(char *variable, int start, int end);
char *get_variable_name(char *variable);
char *get_env_variable_value(char *variable);
