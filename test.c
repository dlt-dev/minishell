/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:40:27 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/10 19:20:25 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Header/minishell.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"

#define YELL_PS "\033[33;1m"
#define BLUE_PS "\033[34;1m"

typedef struct s_prompt
{ 
	int pos_cwd;
	char *user;
	char *cwd;
	char *empty;
	char *home;
	char *prompt;

	char *color_user;
	char *color_cwd;
	char *color_reset;
}t_prompt;

// void write_str(char *str)
// { 
// 	if(str == NULL)
// 		return;
// 	write(1, str, ft_strlen(str));
// }

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void init_prompt(t_prompt *prompt)
{ 
	*prompt = (t_prompt){0};
	prompt->color_reset = RESET;
	prompt->color_user = YELL_PS;
	prompt->color_cwd = BLUE_PS;
	prompt->empty = "\0";
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] != '\0' && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int len_prompt(t_prompt *prompt)
{ 
	int i;
	int count_slash;

	count_slash = 0;
	i = 0;
	i += ft_strlen(prompt->color_user);
	i += ft_strlen(prompt->user);
	i += ft_strlen(prompt->color_cwd);
	if(prompt->home != NULL)
	{ 	
		if(ft_strncmp(prompt->home, prompt->cwd, ft_strlen(prompt->home)) == 0)
		{ 
			prompt->pos_cwd = ft_strlen(prompt->home);
			i+= ft_strlen(prompt->cwd + prompt->pos_cwd);
		}
	}
	i += ft_strlen(&prompt->cwd[j]);
	i += (ft_strlen(prompt->color_reset) * 2);
	return(i);
}

void ft_strcat(char *src, char *dest)
{
	int i;
	int j;
	if(src == NULL || dest == NULL)
		return;
	j = 0; 
	i = 0;
	while(dest[i] != '\0')
		i++;
	while(src[j] != '\0')
	{ 
		dest[i] = src[j];
		j++;
		i++; 
	}
	dest[i] = '\0';
}


char *create_prompt(t_prompt *prompt)
{
	int i;
	int count;
	char *p;
	
	i = 0;
	count = 0;
	p = malloc(sizeof(char ) * (len_prompt(prompt) + 1));
	if(p == NULL)
		return(NULL);
	p[0] = '\0';
	ft_strcat(prompt->color_user, p);
	ft_strcat(prompt->user, p);
	ft_strcat(prompt->color_reset, p);
	ft_strcat(prompt->color_cwd, p);
	ft_strcat(&prompt->cwd[prompt->pos_cwd], p);
	ft_strcat(prompt->color_reset, p);
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



int main()
{ 	
	t_prompt prompt;
	init_prompt(&prompt);
	if(get_prompt(&prompt) == ERROR)
		return(ERROR);
	printf("%s", prompt.prompt);
	return(0);
}

/**
 * @brief environnement pour tester plusieurs fonctions pour s'assurer qu'elles
 * fonctionnent bien avant de les incorporer dans le projet. si une fonction a
 * ete test et a l'air de bien fonctionner, on peut mettre un commentaire
 * GOODJOB sous la fonction: ce qui veut dire que la fonction a subit une
 * batterie de test.
 **/

