#include "../inc/minishell.h"

char	*rl_gets(void)
{
    static char	*line_read = (char *) NULL;
    static char	*previous_line;
    char		*prmpt;

    prmpt = ft_strjoin(getenv("USER"), "@minishell> ");
    line_read = readline(prmpt);
    ft_free(prmpt);
    if (line_read && *line_read)
    {
        if (!previous_line)
            add_history(line_read);
        else
        if (ft_strncmp(previous_line, line_read, ft_strlen(line_read)))
            add_history(line_read);
        ft_free(previous_line);
        previous_line = ft_strdup(line_read);
    }
    return (line_read);
}

void	welcome(void)
{
    printf("<>=======() \n");
    printf("(/\\___   /|\\\\          ()==========<>_ \n");
    printf("      \\_/ | \\\\        //|\\   ______/ \\) \n");
    printf("        \\_|  \\\\      // | \\_/ \n");
    printf("          \\|\\/|\\_   //  /\\/ \n");
    printf("           (oo)\\ \\_//  / \n");
    printf("           //_/\\_\\/ /  |\n");
    printf("          @@/  |=\\  \\  |\n");
    printf("                \\_=\\_ \\ | \n");
    printf("                   \\==\\ \\|\\_ \n");
    printf("                  __(\\===\\(  )\\\n");
    printf("                (((~) __(_/   | \n");
    printf("                     (((~) \\  / \n");
    printf("                 |.------------.|\n");
    printf("                 ||            ||\n");
    printf("                 ||   ENTER    ||\n");
    printf("                 ||    THE     || \n");
    printf("                 ||  MINISHELL ||\n");
    printf("                 |+------------+|\n");
}
