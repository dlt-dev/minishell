/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:40:27 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/10 00:22:17 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "unistd.h"
#include "stdio.h"






int display_prompt(char *prompt)
{
	prompt = getcwd(NULL, 0);
	


	
}



int main()
{ 	
	char *prompt;
	
	prompt= NULL;
	while(1)
	{ 
		display_prompt(prompt);
		
	}
	char* str;
	str = getcwd(NULL, 0);
	printf("%s\n", str);	
	return(0);
}

/**
 * @brief environnement pour tester plusieurs fonctions pour s'assurer qu'elles
 * fonctionnent bien avant de les incorporer dans le projet. si une fonction a
 * ete test et a l'air de bien fonctionner, on peut mettre un commentaire
 * GOODJOB sous la fonction: ce qui veut dire que la fonction a subit une
 * batterie de test.
 **/

