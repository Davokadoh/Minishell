/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Blaze <Blaze@42lausanne.ch>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:57:03 by Blaze             #+#    #+#             */
/*   Updated: 2022/10/16 15:01:05 by Blaze            ###    42Lausanne.ch    */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void ft_pwd(void)
{
	char *buf;
	buf = getcwd(NULL,0);
	printf("%s\n",buf);
	free(buf);
}

int ft_echo(char *cmd)
{
    int i;
    int newLine;

    newLine = 1;
    i = 0;
    while (cmd[i] != '\0')
    {
        if (!ft_strncmp(&cmd[i],"-n", 2))
            newLine = 0;
        else
            write(1,&cmd[i],newLine);
        i++;
    }
    printf("\x20");
    return (write(1,"\n",newLine) == 2);
}
