/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part1_Prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:40:27 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/14 15:26:53 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int replace_by_tilde(t_valist *env , t_prompt *invite, int *len_home)
{
	int i;
	char *home;
	
	home = getenv_intern(env ,"HOME");
	if(home == NULL)
		return(1);
	i = ft_strlen(home);
	if(ft_strncmp(home, invite->cwd, i) == 0)
	{
		*len_home = i;
		return(0); 
	}
	return(1);
}


static int len_prompt(t_valist *env, t_prompt *invite, int *len_home)
{ 
	int i;
	
	i = 0;
	i += ft_strlen(invite->color_user);
	i += ft_strlen(invite->user);
	i += ft_strlen(" ");
	i += ft_strlen(invite->color_cwd);
	if(replace_by_tilde(env , invite, len_home) == 0)
		i+= ft_strlen("~");
	i += ft_strlen(invite->cwd + *len_home);
	i += ft_strlen(invite->color_reset);
	i += ft_strlen("$ ");
	return(i);
}


static char *create_prompt(t_valist *env ,t_prompt *invite)
{
	char *p;
	int len_home; 
	
	len_home= 0;
	p = malloc(sizeof(char ) * (len_prompt(env , invite, &len_home) + 1));
	if(p == NULL)
		return(NULL);
	p[0] = '\0';
	ft_strcat(invite->color_user, p);
	ft_strcat(invite->user, p);
	ft_strcat(" ", p);
	ft_strcat(invite->color_cwd, p);
	if(len_home != 0)
		ft_strcat("~", p);
	ft_strcat(&invite->cwd[len_home], p);
	ft_strcat(invite->color_reset, p);
	ft_strcat("$ ", p);
	return(p);	
}

int get_prompt(t_valist *env, t_prompt *invite)
{
	invite->user = getenv_intern(env , "USER");
	if(invite->user == NULL || *invite->user == '\0')
		invite->user = "Unknown";
	invite->cwd = getcwd(NULL, 0);
	if(invite->cwd == NULL)
		return(ERROR);
	invite->prompt = create_prompt(env , invite);
	free(invite->cwd);
	invite->cwd = NULL;
	if(invite->prompt == NULL)
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
