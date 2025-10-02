/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:19:29 by jdelattr          #+#    #+#             */
/*   Updated: 2025/10/01 19:12:06 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// // a mettre en int pour pouvoir lexer et avoir un return
// char	*lexing_quotes(char *str, int current_i) 
// {
// 	int	count;
// 	int i;
// 	int j;
// 	char *in_quote;

// 	i = current_i;
// 	j = 0;
// 	count = 0;
// 	while (str)
// 	{			
// 		if (str[i] == '\0')
// 		{
// 			//return (in_quote = malloc("\"")); // ne trouve pas de quote pour fermer la premiere, retourne char *str["]
// 			//malloc(1) "STR[I]" (?)
// 			//une " = un token ?
// 		}
// 		if (str[i] != "\"" || str[i] != "\'")
// 			i++;
// 		if(str[i] == "\"" || str[i] == "\'")
// 		{
// 			in_quote = malloc(sizeof(char) * (i - current_i) + 1);// malloc la taille de la section in quotes
// 			//je remplie avec le contenue des "";
// 			//copie de current_i a i
// /* 			while (in_quote &&  inferieur a size) // EXTERNALISER
// 			{
// 				in_quote[j] = str[curent_i];
// 				j++;
// 				curent_i++;
// 			}
// 			in_quote[j] = '\0'; */
// 		}

// 	}
// 	return (in_quote);
// }

// int lexing_quotes(char *str, t_list **tok, int *count)
// {
// 	char c;
// 	char *p;
// 	int i;
	
// 	c = str[0];
// 	i = 1;
// 	while(str[i] != c && str[i] != '\0')
// 		i++;
// 	if(str[i] == c)
// 		p = ft_strndup(str, i + 1);
// 	else
// 		p = ft_strndup(str, i);
// 	if(p == NULL)
// 		return(ERROR);
// 	if(fill_in_lst(tok, p) == ERROR)
// 		return(ERROR);
// 	*count = ft_strlen(p);
// 	return(0);
// }
// // a tester 


// int lexing_word(char *str, t_list **tok, int *count)
// { 
// 	int i;
// 	char *p;
	
// 	if(str == NULL)
// 		return(0);

// 	i = 0;
// 	while(is_separator(str[i]) == IS_NOT && str[i] != '\0')
// 		i++;
// 	p = ft_strndup(str, i);
// 	if(p == NULL)
// 		return(ERROR);
// 	if(fill_in_lst(tok, p) == ERROR)
// 		return(free(p), ERROR);
// 	*count = ft_strlen(p);
// 	return(0);
// }


// int lexing_spaces(char *str, t_list **tok, int *count)
// { 
// 	char *sep;
// 	int i;
// 	char *p;
	
// 	if(str == NULL)
// 		return(0);
// 	i = 0;
// 	sep = " \t\n\v\f\r";
// 	while(is_spaces(str[i]) == IS && str[i] != '\0')
// 		i++;
// 	p = ft_strndup(str, i);
// 	if(p == NULL)
// 		return(ERROR);
// 	if(fill_in_lst(tok, p) == ERROR)
// 		return(free(p), ERROR);
// 	*count = ft_strlen(p);
// 	return(0);
// }
// //plus ou moins goodjob



// int	lexing_metachar(char *str, t_list **tok, int *count)
// {
// 	int	i;
// 	char *p;
	
// 	if (str == NULL)
// 		return (0);
// 	i = 0;
// 	if (str[0] == '<' && str[1] == '<')
// 		p = strdup("<<");
// 	else if (str[0] == '>' && str[1] == '>')
// 		p = strdup(">>");
// 	else if (str[0] == '<')
// 		p = strdup("<");
// 	else if (str[0] == '>')
// 		p = strdup(">");
// 	else if (str[0] == '$')
// 		p = strdup("$");
// 	else if (str[0] == '|')
// 		p = strdup("|");
// 	if(p == NULL)
// 		return(ERROR);
// 	*count = ft_strlen(p);
// 	if(fill_in_lst(tok, p) == ERROR)
// 		return(free(p), ERROR);
// 	return(0);
// }
	


// void lexing(char *str, t_list **tok)
// {
// 	int i;
// 	char *tik;
// 	int value; 

// 	int size_tik;
	

// 	i = 0;
// 	size_tik = 0;
// 	while(str[i] != '\0')
// 	{
// 		if(is_spaces(str[i]) == IS)
// 			value = lexing_spaces(&str[i], tok, &size_tik);
// 		else if(is_separator (&str[i]) == IS_NOT)
// 			value = lexing_word(&str[i], tok, &size_tik);
// 		else if(is_quote(&str[i]) == IS)
// 			value = lexing_quotes(&str[i], tok, &size_tik);
// 		else if(is_metachar(&str[i], tok, &size_tik) == IS)
// 			value = lexing_metachar(&str[i], tok, &size_tik);
// 		if(value == ERROR)
// 			free_exit(*tok, GEN_ERRNO, NULL);
// 		i + size_tik;
// 	}
// }


// int	main(int ac, char **av)
// {
// 	char * command_line;
// 	t_list *tok;
// 	tok = NULL;
// 	while(1)
// 	{ 
// 		// command_line  = readline;
// 		lexing(command_line, &tok);
		
		
// 	}
// }

// /**
//  * @brief 
//  * @param lexing recupere la ligne de commande et creer des char *malloc
//  * de tokens qui seront mis dans une t_list selon la categorie du token
//  * @param lexing_spaces si le caractere str[i] est un espace on arrive dans
//  * cette fonction. @param lexing_spaces malloc et remplit la liste avec un token
//  * d'espaces.
//  * @param lexing_quotes malloc + remplit les quotes
//  * @param is_pipe_bracket malloc + remplit les pipe < > | 
//  * @param lexing_dollar malloc + remplit les dollars (avec le nom de la variable)
//  * @param lexing_word malloc + remplit un mot (tout caractere different des precedents)
//  */