

 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <string.h>
 
 #define RED "\033[1;31m"
 #define BL "\033[1;34m"
 #define GR "\033[1;32m"
 #define YE "\033[1;33m"
 #define RST "\033[0m"

 #define BUFF_SIZE 42
 #define DEL " "

void	cell_split_line(char *line)
{
	//av
	char *tokens[6] = {0};
	int position;

	position = 0;
	for (char *tok  = strtok(line, DEL); tok; tok = strtok(NULL, DEL))
	{
		tokens[position++] = tok;
	}
	position = 0;
	while (tokens[position])
	{
		printf("%s\n", tokens[position++]);
	}

}

int main(int argc, char **argv)
{
	(void) argc;
	// char s[] = "ls -la file.txt dssds"$var dd d d "dsasas | cat";
	cell_split_line(argv[1]);

	return (0);
}

