/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liked_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:19:29 by jdelattr          #+#    #+#             */
/*   Updated: 2025/09/29 20:38:20 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define IS_NOT 0
#define IS 1
#define MODE_QUOTES 2
#define MODE_GEN 3

seize_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst == NULL)
		return;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}



char	create_list(char *str)
{

}

int is_separator (char c)
{  
	int i;
	char sep[7];
	
	i = 0;
	sep = " \t\n\v\f\r";
	while(sep[i] != '\0') 
	{ 
		if(c == sep[i])
			return(IS);
		i++; 
	}
	return(IS_NOT);
}

int determine_mode(char *str)
{ 
	int i;
	 
	i = 0;
	while(is_separator(str[i]) == IS_NOT && str[i] != '\0')
	{ 
		if(str[i] == "\"" || str[i] == "\'")
			return(MODE_QUOTES);
		i++;
	}
	return(MODE_GEN);
}

int fill_in_lst(char *tik, t_list **tok)
{ 
	*tok = lst_new((char *)tik);
	if(lst)

}

char	*parsing_quotes(char *str, int current_i)
{
	int	count;
	int i;
	int j;

	i = current_i;
	j = 0;
	count = 0;
	while (str)
	{			
		if (str[i] == \0)
		{
			//return (in_quote = malloc("\"")); // ne trouve pas de quote pour fermer la premiere, retourne char *str["]
			//malloc(1) "STR[I]" (?)
			//une " = un token ?
		}
		if (str[i] != "\"" || str[i] != "\'")
			i++;
		if(str[i] == "\"" || str[i] == "\'")
		{
			in_quote = malloc(sizeof(char) * (i - current_i) + 1)// malloc la taille de la section in quotes
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
	return (in_quote)

}


void lexing(char *str, t_list **tok)
{
	int i;
	char *tik

	i = 0;
	while(str[i] != '\0')
	{ 
		while (is_separator(str[i]) == IS && str[i] != '\0')
			 i++;
		if(str[i] == '\0')
			break;
		if(str[i] == "\"" || str[i] == "\'")
			parsing_quotes(&str[i])
		if(determine_mode(&str[i]) == MODE_QUOTES)
			parsing_quotes(&str[i]);
		if(determine_mode(&str[i]) == MODE_GEN)
			tik =	parsing_normal(&str[i]);
		fill_in_lst(tik, tok);
		i++;
	}

}

int	main(int ac, char **av)
{
	char * command_line;
	t_list *tok;
	while(1)
	{ 
		command_line  = readline;
		lexing(command_line, &tok);

	}
}


vvvv"dawdaw dwadwadwa "vvv 

