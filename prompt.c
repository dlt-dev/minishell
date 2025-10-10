/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 23:53:24 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/10 00:13:11 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Header/minishell.h"



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

t_struct 

T_WORD //()
T_NL //(new line)
T_EOF //(end of file)

T_GT //(GET TOKEN)

T_AMPER //(&)Traitement de l’attente Si on ne rencontre pas le token T_AMPER (&), on doit, dans la fonction
// n(), attendre la fin du fils lancé avant de redonner la main à l’utilisateur.



 */

//UTILS.C

void printbanner(void)
{
	printf(
		"\033[33m        \\   |   /        \n"
		"\033[33m          .-*-.\n"
		"\033[33m     ☼  (  SUN  )  ☼    \033[95mWELCOME :)\n"
		"\033[33m          `-*-´         \033[95mdans le ...\n"
		"\033[37m    ´   .   ´   .   ´   .\n"
		"\033[37m  .   ´    `   .   ´    `\n"
		"\033[34m~~~~><(((º>~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
		"\033[34m~~~~~~~~~~~~~    ⛵    ~~~~~><(((º>~~~~~~~\n"
		"\033[34m~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
		"\033[93m######### 🐚 ###############*##########*###\n"
		"\033[93m######*############### 🐚 #####*###########\n"
		"\033[1;95m       minishell de Arthur & Jeanne \n"
		"\033[36m\n"
		"\033[0m\n"
	);
}

typedef enum
{

 	T_WORD 1
	T_PIPE 2
	T_AND 3

} 

 	IF (T_DAT-> TYPE > T_DATA−>TYPE -> NEXTE)
	{
 		
	}

T_DATA
{
 	TYPE -> T_WORD (1) 
 	NEXT
	PREV


}

char	*get_cwd(char *buff, size_t size)// pour avoir le path en ligne de commande
{
	char	*result;

	result = getcwd(buff, size);
	if (!result)
		perror(RED"get_cwd failed"RST);
	return (result);
} 

//CELL.C

void	my_malloc(size_t size)
{
	void *ptr;

	if (size == 0)
		return (NULL);
	ptr = malloc(size);
	if (!ptr)
	{
		perror(RED"MALLOC FAILED"RST);
		exit ;
	}
	return (ptr);

}

void	my_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	new_ptr = realloc(ptr, size);
	if (!new_ptr && size != 0)
	{
		perror(RED"REALLOC FAILED"RST);
		exit ;
	}
	return (new_ptr);
}

char	**cell_split_line(char *line) //////////////// en cours !!!!!!
{
	char **tokens;
	unsigned int position = 0;
	size_t buff_size = BUFF_SIZE;

	tokens = my_malloc(BUFF_SIZE * sizeof (*tokens));

	for (char *token = strtok(line, DEL); token; token = strtok(NULL, DEL))
	{
		tokens[position++] = token;
		if (position >= buff_size)
		{
			buff_size *= 2;

		}

	}
	tokens[position++] = NULL;//valeur sentinelle, liste chainee ???
	return (tokens);

}

char	*cell_read_line(void)
{
	char	*buff;
	size_t	bufsize;
	char	cwd[BUFF_SIZE];

	buff = NULL;
	get_cwd(cwd, sizeof(cwd));
	printf(YE"%s"BL" $> "RST, cwd);//printf(YE"[miniminishell] \033[34m$> ");//ligne de com - printf(YE"%s"" $> ", cwd)
	if (getline(&buff, &bufsize, stdin) == -1)// si getline ne fct pas
	{
		// end of file ???
		buff = NULL;
		printf(RED"getline failed"RST);
	}
	return (buff);
}

void	cell_split_line(char *line)
{
	char *token[6] = {0};
	int position;

	position = 0;
	for (char *token  = strtok(line, DEL); token; token = strtok(NULL, DEL))
	{
		token[position++] = token;
	}
	position = 0;
	while (token[position])
	{
		printf("%s\n", token[position++]);
	}

}

 // MINIMINISHELL.C

//la fct main boucle sur l'appel a la fct commande()
/* main() {
Répéter
token = commande();
si token == T_EOF
break;
} */

 int main(int ac , char **av)
 {
	(void)ac;
	(void)av;
	char *line;

	printbanner();
	while (1)
	{
		line = cell_read_line();
		printf("%s\n", line);
	}
	return (0);
 }
