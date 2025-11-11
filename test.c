/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:40:27 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/11 16:04:05 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Header/minishell.h"
#include <unistd.h> 
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>



int ft_cd(char **argv)
{
	int i;
	char *path;
	char *message;

	message = "too many arguments";
	i = 1;
	while(argv[i] != NULL)
		i++;
	if(i > 2)
	{ 
		write(1, message, ft_strlen(message));
		message = "too many arguments";
		return(GEN_ERRNO);
	}	
	if(chdir(argv[1]) == ERROR)
	{ 
		perror(argv[1]);	
		return(GEN_ERRNO);
	}
	else
		printf("%s\n", getcwd(NULL, 0));
	return(0);
}

int main(int argc, char **argv, char **envp)
{ 
	ft_cd(&argv[1]);
	
}




// int routine_heredoc(char **argv, int pipefd[2])
// { 
// 	char *str;
	
// 	close(pipefd[0]);
// 	while(1)
// 	{
// 		str = readline(">");
// 		if(str == NULL)
// 			break;
// 		if(ft_strlen(str) == ft_strlen(argv[1]) && ft_strcmp(str, argv[1]) == 0)
// 		{
// 			free(str);
// 			break;	
// 		}
// 		write(pipefd[1], str, ft_strlen(str));
// 		write(pipefd[1], "\n", 1);
// 		free(str);
// 	}
// 	close(pipefd[1]);
// 	exit(0);
// }


// int handle_heredoc(char **argv)
// {	
// 	int pipefd[2];

// 	pipe(pipefd);
// 	pid_t pid_heredoc;
// 	pid_heredoc = fork();
	
// 	if(pid_heredoc == ERROR)
// 		return(ERROR);
// 	if(pid_heredoc == 0)
// 	{ 
// 		routine_heredoc(argv, pipefd);
// 	}
// 	waitpid(pid_heredoc, NULL, 0);
// 	close(pipefd[1]);
// 	return(pipefd[0]);
// }


// int main(int argc, char **argv)
// {
// 	int i;
// 	// if(argc != 2)
// 	// 	return;
// 	i = handle_heredoc(argv);
// 	return(i);
// } 




// int main ()
// {
// 	int i;
// 	char buffer[1000];
// 	i = read(0, buffer, 1000);
// 	if(read == ERROR)
// 		return(ERROR);
// 	buffer[i] = '\0';
// 	printf("%s", buffer);
	
// }




// int main (int argc, char ** argv)
// { 
// 	int fd;
// 	int i;

// 	// i = 0; 
// 	// fd = ("Header", O_RDONLY);
// 	// printf("%d", fd);
// 	// if(fd == ERROR)
// 	// 	perror("erreur");
// 	if(argc < 2)
// 		return(0);
// 	struct stat statbuf;
// 	stat(argv[1], &statbuf);
// 	if(S_ISREG(statbuf.st_mode) != 0)
// 		printf("c'est un fichier");
// 	if(S_ISDIR(statbuf.st_mode) != 0)
// 		printf("C'est un dossier");

// }
