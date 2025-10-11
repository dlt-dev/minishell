/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:40:27 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/11 13:36:42 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_prompt(t_prompt *prompt)
{ 
	*prompt = (t_prompt){0};
	prompt->color_reset = RESET;
	prompt->color_user = YELL_PS;
	prompt->color_cwd = BLUE_PS;
	prompt->empty = "\0";
}

int len_prompt(t_prompt *prompt)
{ 
	int i;
	int home_lenght;

	home_lenght = 0;
	i = 0;
	i += ft_strlen(prompt->color_user);
	i += ft_strlen(prompt->user);
	i += ft_strlen(" ");
	i += ft_strlen(prompt->color_cwd);
	if(prompt->home != NULL)
	{
		if(ft_strncmp(prompt->home, prompt->cwd, ft_strlen(prompt->home)) == 0)
		{ 
			home_lenght = ft_strlen(prompt->home);
			i+= ft_strlen("~");
		}
	}	
	prompt->pos_cwd = home_lenght;
	i += ft_strlen(prompt->cwd + home_lenght);
	i += (ft_strlen(prompt->color_reset) * 2);
	i += ft_strlen("$ ");
	return(i);
}


char *create_prompt(t_prompt *prompt)
{
	char *p;
	
	p = malloc(sizeof(char ) * (len_prompt(prompt) + 1));
	if(p == NULL)
		return(NULL);
	p[0] = '\0';
	ft_strcat(prompt->color_user, p);
	ft_strcat(prompt->user, p);
	ft_strcat(prompt->color_reset, p);
	ft_strcat(" ", p);
	ft_strcat(prompt->color_cwd, p);
	if(prompt->pos_cwd != 0)
		ft_strcat("~", p);
	ft_strcat(&prompt->cwd[prompt->pos_cwd], p);
	ft_strcat(prompt->color_reset, p);
	ft_strcat("$ ", p);
	return(p);	
}

int get_prompt(t_prompt *prompt)
{
	prompt->user = getenv("USER");
	if(prompt->user == NULL)
		prompt->user = prompt->empty;
	prompt->home = getenv("HOME");
	prompt->cwd = getcwd(NULL, 0);
	if(prompt->cwd == NULL)
		return(ERROR);
	prompt->prompt = create_prompt(prompt);
	free(prompt->cwd);
	prompt->cwd = NULL;
	if(prompt->prompt == NULL)
		return(ERROR);
	return(0);
}



int ft_prompt(t_prompt *prompt)
{ 	
	init_prompt(prompt);
	if(get_prompt(prompt) == ERROR)
		return(ERROR);
	return(0);
}

/**
 * @brief environnement pour tester plusieurs fonctions pour s'assurer qu'elles
 * fonctionnent bien avant de les incorporer dans le projet. si une fonction a
 * ete test et a l'air de bien fonctionner, on peut mettre un commentaire
 * GOODJOB sous la fonction: ce qui veut dire que la fonction a subit une
 * batterie de test.
 **/

