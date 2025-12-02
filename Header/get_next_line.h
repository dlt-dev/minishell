/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:18:03 by aoesterl          #+#    #+#             */
/*   Updated: 2025/12/02 03:57:47 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "minishell.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <aio.h>
# include <fcntl.h> //int open(const char *pathname, int flags);
# include <unistd.h>

char	*gnl_strdup(char *str);
char	*strjoin(char *s1, char *s2);
char	*get_next_line(int fd);

/* ssize_t read(int fd, void *buf, size_t count);
la fonction read tente de lire count bits du descripteur 
de fichier fd dans le tampon commencant a buf. le read 
commence au decalage et le decalage est incremente
du nombre d'octet lu. si le decalage est egal ou superieur
 a la fin du fihcier, aucun octet n'est lu et read renvoie zero.

valeur de retour: le nombre de bytes lu est return. et 
la position fichier est avance par ce nombre.
S'il y a une erreur on retourne -1. si la valeur est
*/

#endif