
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 100

void	read_and_print_100(int fd)
{
	char	buf[BUFFER_SIZE + 1];	// stocke les caractères lus par read
	int	nb_read;	// stocke le retour de read

//	Lit 100 caractères du fichier
	nb_read = read(fd, buf, BUFFER_SIZE);
//	En cas d'erreur, on arrête tout
	if (nb_read == -1)
	{
		printf("Erreur de lecture !\n");
		return ;
	}
//	Ajoute le \0 à la fin de la chaîne
	buf[nb_read] = '\0';
//	Imprime ce que contient le buffer après la lecture, précédé
//	du déscripteur de fichier d'où provient le contenu
	printf("\e[36mfd %d : [\e[0m%s\e[36m]\e[0m\n", fd, buf);
	return ;
}

int	main(void)
{
	int fd1;	// descripteur de fichier à lire
	int fd2;	// second descripteur de fichier à lire



	int fd3 = open("catdoc", O_CREAT);

//	Ouvre le fichier cat.txt en mode lecture seule
	fd1 = open("cat.txt", O_RDONLY, O_CREAT);
//	Ouvre à nouveau le fichier cat.txt en mode lecture seule
	fd2 = open("cat.txt", O_RDONLY, O_CREAT);
	if (fd1 == -1 || fd2 == -1)
		return (1);
//	Imprime les 100 premiers caractères du descripteur 1
	read_and_print_100(fd1);
//	Imprime les 100 prochains caractères du descripteur 1
	read_and_print_100(fd1);
//	Imprime les 100 premiers caractères du descripteur 2
	read_and_print_100(fd2);
//	Ferme les descripteurs de fichier ouverts plut tôt
	close(fd1);
	close(fd2);
	return (0);
}
