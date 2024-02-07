#include <malloc.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char	*name;

	while (1)
	{
		name = readline("prompt -> ");
                add_history(name);
		printf("Hello, %s!\n", name);
                if (strcmp(name, "exit") == 0)
                {
                    free(name);
                    break;
                }
		free(name);
	}
        while (1) {
                ;
        }
	return (0);
}
