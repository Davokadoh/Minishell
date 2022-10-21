/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btchiman <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:41:12 by btchiman          #+#    #+#             */
/*   Updated: 2022/10/21 17:22:07 by btchiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char **ft_increnv(char **env, char *new_entry)
{
	char **new_env;
	int	i;

	i = 0;
	while(env[i])
		i++;
	new_env = malloc(sizeof(char**)*i +2);
	i = 0;
	while(env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = ft_strdup(new_entry);
	new_env[i+1] = NULL;
	/*i = 0;
	while(env[i])
	{
		ft_free(env[i]);
		i++;
	}*/
	return (new_env);
}

char *malloc_substrcpy(char *variable, int start, int end)
{
    int len;
    int i;
    int j;
    char *name;

    i = 0;
    j = start;
    len = end - start;

    name = malloc(sizeof(char) * len + 1);
    while (i <= len)
    {
        name[i] = variable[j];
        i++;
        j++;
    }
    name[i] = '\0';
    return (name);
}


char *get_variable_name(char *variable)
{
	int		index;
	int		start;
	int		end;
	char	*name;

	index = 0;
	start = 0;
	if (!variable)
		return (NULL);
	while (variable[index])
	{
		if (variable[index] == '=')
		{
			end = index - 1;
			name = malloc_substrcpy(variable, start, end);
			return (name);
		}
		index++;
	}
	end = index;
	name = malloc_substrcpy(variable, start, end);
	return (name);
}

char *get_env_variable_value(char *variable)
{
	int		i;
	int		start;
	int		end;
	char	*value;

	i = 0;
	if (!variable)
		return (NULL);
	while (variable[i])
	{
		if (variable[i] == '=')
		{
			start = i + 1;
			end = ft_strlen(variable);
			value = malloc_substrcpy(variable, start, end);
			return (value);
		}
		i++;
	}
	return (NULL);
}

char **add_env_var(char *l_value, char *r_value, char **env)
{
    char *new_entry;
	char **new_env;
    int i;

    i = 0;
    new_entry = ft_strjoin(l_value,"=");
    new_entry = ft_strjoin(new_entry,r_value);
    new_env = ft_increnv(env,new_entry);
    ft_free(new_entry);
    return (new_env);
}
// ajoute un element au tableau de variable d'environnement et au tableau d'export
char **ft_export(char **args, char **env)
{
    char    *l_value;
    char    *r_value;
	char	**new_env;
	static char		**exp_lst;

	if (!exp_lst[0])
	{
		//exp_lst = init_exp(env);
	}
	else if (!args[1])
	{
		//print_export(exp_lst);
		exit(0);
	}
	else
	{
    	l_value = get_variable_name(args[1]);
    	r_value = get_env_variable_value(args[1]);
    	new_env = add_env_var(l_value,r_value,env);
		HOME=/Users/btchiman
		return (new_env);
	}
	/*int i = -1;
	while(new_env[++i])
		printf("%s\n",new_env[i]);*/
	exit(0);
}
 // TODO export loop
 /* print_export()
{

	HOME=/Users/btchiman
	LANG=en_US.UTF-8
	LESS=-R
	LOGNAME=btchiman
	LSCOLORS=Gxfxcxdxbxegedabagacad
	OLDPWD=/Users/btchiman
	PAGER=less
	PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin
	PWD=/Users/btchiman
	SHELL=/bin/zsh
	SHLVL=1
	SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.O8UBHvS7Fg/Listeners
	TERM=xterm-256color
	TERM_PROGRAM=Apple_Terminal
	TERM_PROGRAM_VERSION=433
	TERM_SESSION_ID=A0C14B45-2438-4230-BE52-23ADAF97F66C
	TMPDIR=/var/folders/zz/zyxvpxvq6csfxvn_n000c_ww0032q7/T/
	USER=btchiman
	XPC_FLAGS=0x0
	XPC_SERVICE_NAME=0
	ZSH=/Users/btchiman/.oh-my-zsh
}*/
