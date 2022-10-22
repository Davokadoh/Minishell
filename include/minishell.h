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
# include "libft.h"

typedef struct	s_envp  t_envp;
typedef struct s_cmd    t_cmd;

struct s_envp
{
	char	*env[31];
};

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

char	*ft_getenv(char *var, t_envp *env);
t_envp  *init_envp(char **env);
void    ft_setenv(char *var, char *var2, t_envp *env);
void    ft_env(t_envp *env);
void    ft_pwd(void);
void    ft_echo(char *cmd);

void	ft_free_tab(char **str);
#endif
