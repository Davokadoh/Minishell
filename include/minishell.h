/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Blaze <Blaze@42lausanne.ch>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:01:25 by Blaze             #+#    #+#             */
/*   Updated: 2022/11/13 18:39:09 by jleroux          ###   ########.fr       */
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

# define CMD_NOT_FOUND 127
# define IS_A_DIR 126
# define PIPE_ERR 11
# define SUCCESS 0

typedef struct s_envp	t_envp;
typedef struct s_cmd	t_cmd;

struct	s_cmd
{
	char	**argv;
	int		input_fd;
	int		output_fd;
	int		do_run;
	int		piped;
	pid_t	pid;
};

struct s_envp
{
	char **env;
	char **exp_init;
	char **exp_lst;
};


//Main logic
int		quotes(int errno, t_envp *ft_env, char *str);
int		expand(int errno, t_envp *ft_env, char *str);
int		lexer(int errno, t_envp *ft_env, char *str);
int		parse(int errno, t_envp *ft_env, char **tokens);
int		execute(int errno, t_envp *ft_envp, t_cmd *cmds);
int     is_builtin(char *cmd);
int     run_builtin(char **argv, t_envp *envp);
int		child(t_cmd *cmds, int i, char **ft_env);

void	expand_errno(int errno, char **token);
char	*strip_quotes(char *token);

//Signals
void	parent_handler(void);
void	child_handler(void);

//Utils
void	set_io(int input_fd, int output_fd);
void	unset_io(int input_fd, int output_fd);
int		is_meta(const char ch);
void	welcome(void);
char	*rl_gets(void);
char 	**ft_triAlpha(char **s);

//Builtins
char	*ft_getenv(char *var, char **env);
char    **init_envp(char **env);
void    ft_env(t_envp  *envp);
void    ft_setenv(char *var, char *var2, char **env);
int		ft_unset(char **args, t_envp  *envp);
int    	ft_export(char **args, t_envp  *envp);
int		ft_cd(char **args, char **env);
int		ft_echo(char **args);
void	ft_pwd(void);
int		ft_exit(char **argv);
char	**init_exp(char **env);
char	**incr(char **new_env,char *l_value, char *new_entry);

char	*ft_strinsert(char *s1, char *s2, int start, int end);
char	**ft_increnv(char **env, char *new_entry);
char	*malloc_substrcpy(char *variable, int start, int end); //How diff from ft_substr ? Move to libft ?
char	*get_variable_name(char *variable);
char	*get_env_variable_value(char *variable);

#endif
