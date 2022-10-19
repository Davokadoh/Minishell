/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Blaze <Blaze@42lausanne.ch>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:57:03 by Blaze             #+#    #+#             */
/*   Updated: 2022/10/19 12:17:02 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_pwd(void)
{
	char *buf;
	buf = getcwd(NULL,0);
	printf("%s\n",buf);
	free(buf);
}

void ft_echo(char *cmd)
{
    int i;
    i = 0;
    while (cmd[i] != '\0')
    {
        if (cmd[i] == '$')
        {
            i++;
            while (cmd[i] != ' ' && cmd[i] != '\0')
            {
                printf("%c",cmd[i]);
                i++;
            }
        }
        else
        {
            printf("%c",cmd[i]);
            i++;
        }
    }
    printf("\n");
}
