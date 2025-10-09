/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:19:29 by jdelattr          #+#    #+#             */
/*   Updated: 2025/10/08 19:49:22 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int len_word(char *str)
{ 
	int i;
	char quote;
	
	i = 0;
	while(is_str(str[i], " \t\n|<>") == IS_NOT && str[i] != '\0')
	{ 
		if(str[i] == '\'' || str[i] == '\"')
		{ 
			quote = str[i];
			i++;
			while(str[i] != quote && str[i] != '\0')
				i++;
			if(str[i] == quote)
				i++;
		}
		else
			i++;
	}
	return(i);
}

int lexing_word (char *str, t_list** lst, int *count)
{
	int i;
	char *p;
	
	if(str == NULL)
		return(0);
	i = 0;
	i = len_word(str);
	p = ft_strndup(str, i);
	if(p == NULL)
		return(ERROR);
	*count = ft_strlen(p);
	if(fill_in_lst(lst, p) == ERROR)
		return(free(p), ERROR);
	return(0);
}

int	lexing_metachar(char *str, t_list **lst, int *count)
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
	else if (str[0] == '|')
		p = ft_strdup("|");
	if(p == NULL)
		return(ERROR);
	*count = ft_strlen(p);
	if(fill_in_lst(lst, p) == ERROR)
		return(free(p), ERROR);
	return(0);
}

void lexing(char *str, t_list **lst)
{
	int i;
	char *tokens;
	int value; 
	int size_tok;
	i = 0;
	size_tok = 0;
	while(str[i] != '\0')
	{
		if(is_str(str[i], " \t\n") == IS)
			size_tok = 1;
		else if(is_str(str[i], "<>|" ) == IS)
			lexing_metachar(&str[i], lst, &size_tok);
		else 
			lexing_word(&str[i], lst, &size_tok);
		if(value == ERROR)
			free_exit(*lst, GEN_ERRNO, NULL);
		i += size_tok;
	}
}



int main()
{ 
	t_list *lst;
	t_syntax syntax;
	
	lst = NULL; 
	//char * a= ">>     <                 b$$$onjour \"je m'appelle \"michelle";
	//char * a= "     \'jhgasd dasjg awjdg$$$$$KH'  kdshd\"\"\"\"\"\"\"hjhjhjk&";
	char * a= " <<< <<<<<  \"arthur\"\"oscar\"\"papa\"  $var\"jeanne\" arthur ";
	lexing(a, &lst);
	print_str_lst(lst);

}

// /**
//  * @brief 
//  * @param lexing recupere la ligne de commande et creer des char *malloc
//  * de lstens qui seront mis dans une t_list selon la categorie du lsten
//  * @param lexing_spaces si le caractere str[i] est un espace on arrive dans
//  * cette fonction. @param lexing_spaces malloc et remplit la liste avec un lsten
//  * d'espaces.
//  * @param lexing_quotes malloc + remplit les quotes
//  * @param is_pipe_bracket malloc + remplit les pipe < > | 
//  * @param lexing_dollar malloc + remplit les dollars (avec le nom de la variable)
//  * @param lexing_word malloc + remplit un mot (tout caractere different des precedents)
//  */