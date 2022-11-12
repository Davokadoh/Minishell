#include "../include/minishell.h"

//TODO si la valuer de gauche existe deja , remplacez !
char **incr(char **new_env,char *l_value, char *new_entry)
{
		int i;

		i = -1;
		/*while (new_env[++i])
			;
		new_env = ft_push_str() //realloc(new_env, (i + 2) * sizeof(char **));*/
		i = -1;
		while( new_env && new_env[++i])
		{
			if(ft_strnstr(new_env[i],l_value,ft_strlen(l_value)))
			{
				new_env[i] = ft_strdup(new_entry);
				return (new_env);
			}	
		}
		/*new_env[i] = ft_strdup(new_entry);
		new_env[i + 1] = NULL;*/
		new_env = ft_push_str(&new_env,new_entry);
		return (new_env);
}

char	**ft_increnv(char **env, char *l_value, char *new_entry)// env[0]
{
	static char	**new_env;
	int		i;
	
	if (!new_env)
	{
		i = -1;
		while (env[++i])
			;
		new_env = malloc(sizeof (char **) * (i + 2));
		if (!new_env)
			return (NULL);
		i = -1;
		while(env[++i])
			new_env[i] = ft_strdup(env[i]);
		new_env[i] = ft_strdup(new_entry);
		new_env[i + 1] = NULL;
		i = -1;
		while (env[++i])
			ft_free(env[i]);
		return (new_env);
	}
	else
		new_env = incr(new_env,l_value, new_entry);
	return (new_env);
}

char **init_exp(char **env)
{
    char **exp;
    int i;
    int j;
    
    i = -1;
    j = 0;
    while (env[++i])
        ;
    exp = malloc(sizeof(char **) * (i + 1));
	if(!exp)
		exit(0);
    while (env[j])
    {
		if(ft_strncmp(env[j],"_=",2) != 0)
			exp[j] = ft_strdup(env[j]);
        j++;
    }
	exp[j] = NULL;
	exp = ft_triAlpha(exp);
    return (exp);
}