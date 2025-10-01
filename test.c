/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:40:27 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/01 19:50:08 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int lexing_quotes(char *str, t_list **tok, int *count)
{
	char c;
	char *p;
	int i;
	
	c = str[0];
	i = 1;
	while(str[i] != c && str[i] != '\0')
		i++;
	if(str[i] == c)
		p = ft_strndup(str, i + 1);
	else
		p = ft_strndup(str, i);
	if(p == NULL)
		return(ERROR);
	if(fill_in_lst(tok, p) == ERROR)
		return(ERROR);
	*count = ft_strlen(p);
	return(0);
}
// a tester 


int lexing_word(char *str, t_list **tok, int *count)
{ 
	int i;
	char *p;
	
	if(str == NULL)
		return(0);

	i = 0;
	while(is_separator(str[i]) == IS_NOT && str[i] != '\0')
		i++;
	p = ft_strndup(str, i);
	if(p == NULL)
		return(ERROR);
	if(fill_in_lst(tok, p) == ERROR)
		return(free(p), ERROR);
	*count = ft_strlen(p);
	return(0);
}


int lexing_spaces(char *str, t_list **tok, int *count)
{ 
	char *sep;
	int i;
	char *p;
	
	if(str == NULL)
		return(0);
	i = 0;
	sep = " \t\n\v\f\r";
	while(is_spaces(str[i]) == IS && str[i] != '\0')
		i++;
	p = ft_strndup(str, i);
	if(p == NULL)
		return(ERROR);
	if(fill_in_lst(tok, p) == ERROR)
		return(free(p), ERROR);
	*count = ft_strlen(p);
	return(0);
}
//plus ou moins goodjob



int	lexing_metachar(char *str, t_list **tok, int *count)
{
	int	i;
	char *p;
	
	if (str == NULL)
		return (0);
	i = 0;
	if (str[0] == '<' && str[1] == '<')
		p = ft_strdup("<<");
	else if (str[0] == '>' && str[1] == '>')
		p = ft_strdup(">>");
	else if (str[0] == '<')
		p = ft_strdup("<");
	else if (str[0] == '>')
		p = ft_strdup(">");
	else if (str[0] == '$')
		p = ft_strdup("$");
	else if (str[0] == '|')
		p = ft_strdup("|");
	if(p == NULL)
		return(ERROR);
	*count = ft_strlen(p);
	if(fill_in_lst(tok, p) == ERROR)
		return(free(p), ERROR);
	return(0);
}
	


void lexing(char *str, t_list **tok)//assigner les types?
{
	int i;
	char *tik;
	int value; 

	int size_tik;
	

	i = 0;
	size_tik = 0;
	while(str[i] != '\0')
	{
		if(is_spaces(str[i]) == IS)
			value = lexing_spaces(&str[i], tok, &size_tik);
		else if(is_separator (str[i]) == IS_NOT)
			value = lexing_word(&str[i], tok, &size_tik);
		else if(is_quote(str[i]) == IS)
			value = lexing_quotes(&str[i], tok, &size_tik);
		else if(is_metachar(str[i]) == IS)
			value = lexing_metachar(&str[i], tok, &size_tik);
		if(value == ERROR)
			free_exit(*tok, GEN_ERRNO, NULL);
		i += size_tik;
	}
}

int main (char **envp)
{ 
	t_list *tok;
	tok = NULL; 
	//char * a= ">>     <                 b$$$onjour \"je m'appelle \"michelle";
	//char * a= "     \'jhgasd dasjg awjdg$$$$$KH'  kdshd\"\"\"\"\"\"\"hjhjhjk&";
	char * a= "    "jyhgdsaj' uskefhiwuef";
	lexing(a, &tok);
	print_str_lst(tok);

}




/**
 * @brief environnement pour tester plusieurs fonctions pour s'assurer qu'elles
 * fonctionnent bien avant de les incorporer dans le projet. si une fonction a
 * ete test et a l'air de bien fonctionner, on peut mettre un commentaire
 * GOODJOB sous la fonction: ce qui veut dire que la fonction a subit une
 * batterie de test.
 **/

