#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	printf("%s\n", getwd(NULL));
	printf("%d\n", chdir("/Users/jleroux/Workspace"));
	printf("%s\n", getwd(NULL));
	printf("%d\n", chdir("/Users/jleroux/Workspace/minishell"));
	printf("%s\n", getwd(NULL));
}
