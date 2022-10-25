/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Blaze <Blaze@42lausanne.ch>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:01:25 by Blaze             #+#    #+#             */
/*   Updated: 2022/10/21 14:40:37 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct	s_envp  t_envp;
typedef struct s_cmd    t_cmd;

struct	s_cmd
{
    char	**argv;
    char	*input_name;
    char	*output_name;
    int		input_fd;
    int		output_fd;
	int		do_run;
};

extern int	g_errno;

void	welcome(void);
char	*rl_gets(void);
char	**lex(const char *str);
char	*expand(char **str);//, char **envp);
char	**split_metachar(char **tokens);
t_cmd	*parse(char **tokens);
int		execute(t_cmd *cmds, char **ft_env);




void    ft_pwd(void);


void	ft_free_tab(char **str);

char	**lex(const char *str);
char	*ft_getenv(char *var, char **env);
char    **init_envp(char **env);
void    ft_setenv(char *var, char *var2, char **env);
void    ft_env(char **env);
void    ft_pwd(void);
int     ft_echo(char **args);
int     builtin(char **tokens, char ***env);
char    **ft_export(char **args, char **env);
// utils
char **ft_increnv(char **env, char *new_entry);
char *malloc_substrcpy(char *variable, int start, int end);
char *get_variable_name(char *variable);
char *get_env_variable_value(char *variable);

#endif
