#include <stdio.h>

int main(int argc, char *argv[], char **envp)//TODO 지우ㅜㅜ기
{
	int	i;
	i = 0;

	// printf("%s\n", envp[0]);

	// printf("%s=%s\n", argv[1], getenv(argv[1]));
	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}
