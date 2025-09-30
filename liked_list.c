/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liked_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:19:29 by jdelattr          #+#    #+#             */
/*   Updated: 2025/09/30 17:18:45 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*lexing_quotes(char *str, int current_i)
{
	int	count;
	int i;
	int j;
	char *in_quote;

	i = current_i;
	j = 0;
	count = 0;
	while (str)
	{			
		if (str[i] == '\0')
		{
			//return (in_quote = malloc("\"")); // ne trouve pas de quote pour fermer la premiere, retourne char *str["]
			//malloc(1) "STR[I]" (?)
			//une " = un token ?
		}
		if (str[i] != "\"" || str[i] != "\'")
			i++;
		if(str[i] == "\"" || str[i] == "\'")
		{
			in_quote = malloc(sizeof(char) * (i - current_i) + 1);// malloc la taille de la section in quotes
			//je remplie avec le contenue des "";
			//copie de current_i a i
/* 			while (in_quote &&  inferieur a size) // EXTERNALISER
			{
				in_quote[j] = str[curent_i];
				j++;
				curent_i++;
			}
			in_quote[j] = '\0'; */
		}

	}
	return (in_quote);
}


int lexing_spaces(char *str, t_list **tok)
{ 
	char *sep;
	int i;
	char *p;

	i = 0;
	sep = " \t\n\v\f\r";
	while(is_separator(str[i]) == IS && str[i] != '\0')
		i++;
	p = ft_strndup(str, i);
	if(p == NULL)
		return(ERROR);
	if(fill_in_lst(tok, p) == ;
} 



void lexing(char *str, t_list **tok)
{
	int i;
	char *tik;

	i = 0;
	while(str[i] != '\0')
	{ 
		if(is_separator(str[i]) == IS)
			lexing_spaces(&str[i], tok);
		else if(str[i] == "\"" || str[i] == "\'")
			lexing_quotes(&str[i], tok);
		else if(is_pipe_bracket(&str[i]) == IS)
			lexing_like_pipe(&str[i], tok);
		else if(str[i] == "$")
			lexing_dollar(&str[i], tok);
		else if(is_different(&str[i]) == IS)
			lexing(&str[i], tok);
		if(str[i] == '\0')
			break;
		i++;
	}

}


int	main(int ac, char **av)
{
	char * command_line;
	t_list *tok;
	tok = NULL;
	while(1)
	{ 
		// command_line  = readline;
		lexing(command_line, &tok);

	}
}


espace = " \t\n\v\f\r" // si c'est autre chose qu'espace on arrete
quote = " \"\'" // si on touche au deuxieme quote on s'arrete
pipe = "|<>\t\n\v\f\r" // on regarde le caractere suivant et on s'arrete  toutde
// suite si autre chose qu'un pipe et   
dollars = "\t\n\v\"
different = " \t\n\v\f\r\'\'|<>$"