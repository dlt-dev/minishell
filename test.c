/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:40:27 by aoesterl          #+#    #+#             */
/*   Updated: 2025/09/30 19:49:12 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int lexing_spaces(char *str, t_list **tok)
{ 
	char *sep;
	int i;
	char *p;
	if(str == NULL)
		return(0);
	i = 0;
	sep = " \t\n\v\f\r";
	while(is_separator(str[i]) == IS && str[i] != '\0')
		i++;
	p = ft_strndup(str, i);
	if(p == NULL)
		return(ERROR);
	if(fill_in_lst(tok, p) == ERROR)
		return(ERROR);
	return(0);
}

int main()
{
	t_list *lst;
	lst = NULL;

	char *a = "  prout";
	char *b = " 			 ok eae k ";
	char *c = "";
	char *d = NULL;
	lexing_spaces(a, &lst);
	lexing_spaces(b, &lst);
	lexing_spaces(c, &lst);
	lexing_spaces(d, &lst);
	print_str_lst(lst);
	ft_free_lst(lst);
}




/**
 * @brief environnement pour tester plusieurs fonctions pour s'assurer qu'elles
 * fonctionnent bien avant de les incorporer dans le projet. si une fonction a
 * ete test et a l'air de bien fonctionner, on peut mettre un commentaire
 * GOODJOB sous la fonction: ce qui veut dire que la fonction a subit une
 * batterie de test.
 */