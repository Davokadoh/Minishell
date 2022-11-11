/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Blaze <Blaze@42lausanne.ch>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:01:25 by Blaze             #+#    #+#             */
/*   Updated: 2022/11/11 15:39:07 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <dirent.h>
# include <termios.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/include/libft.h"

void	rl_replace_line (const char *text, int clear_undo);

typedef struct	s_envp  t_envp;
typedef struct s_cmd    t_cmd;

struct	s_cmd
{
    char	**argv;
    char	*input_name; //Unused
    char	*output_name; //Unused
    int		input_fd;
    int		output_fd;
	int		do_run; //Unused yet
	int		piped;
	pid_t	pid; //Unused yet
};

struct s_envp
{
	char **env;
	char **exp_init;
	char **exp_lst;
};

//Should be moved to libft
void	ft_free_tab(char **str);
char	*ft_strinsert(char *s1, char *s2, int start, int end);

//Main logic
int		syntax(int errno, t_envp *ft_env, char *str);
int		expand(int errno, t_envp *ft_env, char *str);
int		lexer(int errno, t_envp *ft_env, char *str);
int		parse(int errno, t_envp *ft_env, char **tokens);
int		execute(int errno, t_envp *ft_envp, t_cmd *cmds);

int     is_builtin(char *cmd);
int     run_builtin(char **argv, t_envp *envp);

//Utils
int		is_meta(const char ch);
char	**split_metachar(char **tokens); //Unused ?
void	welcome(void);
char	*rl_gets(void);
char **ft_triAlpha(char **s);

//Builtins
char	*ft_getenv(char *var, char **env);
char    **init_envp(char **env);
void    ft_env(char **env);
void    ft_setenv(char *var, char *var2, char **env);
int		ft_unset(char **args, t_envp  *envp);
int    	ft_export(char **args, t_envp  *envp);
int		ft_cd(char **args, char **env);
int     ft_echo(char **args);
void    ft_pwd(void);
int		ft_exit(char **argv);

// utils //Are they just that tho ?
char **ft_increnv(char **env, char *l_value, char *new_entry); //This could be in category builtins, no ?
char *malloc_substrcpy(char *variable, int start, int end); //How diff from ft_substr ? Move to libft ?
char *get_variable_name(char *variable); //What is that ? Move to builtins too ?
char *get_env_variable_value(char *variable); //Same as the above

#endif
