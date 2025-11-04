/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:40:27 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/04 19:22:05 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Header/minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


int main (int argc, char ** argv)
{ 
	int fd;
	int i;

	i = 0; 
	fd = open("prout", O_RDONLY);
	char arthur[10000];
		read(fd, &arthur, 10000);
	printf("%s", arthur);
	// if(fd == ERROR)
	// 	perror("erreur");
	// if(argc < 2)
	// 	return(0);
	// struct stat statbuf;
	// stat(argv[1], &statbuf);
	// if(S_ISREG(statbuf.st_mode) != 0)
	// 	printf("c'est un fichier");
	// if(S_ISDIR(statbuf.st_mode) != 0)
	// 	printf("C'est un dossier");

}
