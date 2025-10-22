/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part2_lexing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:19:29 by jdelattr          #+#    #+#             */
/*   Updated: 2025/10/22 18:46:01 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int len_word(char *str)
{ 
	int i;
	char quote;
	
	i = 0;
	while(is_char_in_str(str[i], " \t\n|<>") == IS_NOT && str[i] != '\0')
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

static int lexing_word(char *str, t_list** lst, int *count)
{
	int i;
	char *p;
	
	if(str == NULL)
		return(0);
	i = len_word(str);
	p = ft_strndup(str, i);
	if(p == NULL)
		return(ERROR);
	*count = ft_strlen(p);
	if(fill_in_lst(lst, p, WORD) == ERROR)
		return(free(p), ERROR);
	return(0);
}

static int	lexing_metachar(char *str, t_list **lst, int *count)
{
	char *p;
	
	p = NULL; 
	if (str == NULL)
		return (0);
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
	if(fill_in_lst(lst, p, META) == ERROR)
		return(free(p), ERROR);
	return(0);
}

int lexing(char *str, t_list **lst)
{
	int i;
	int value; 
	int size_tok;
	
	i = 0;
	size_tok = 0;
	value = 0;
	while(str[i] != '\0')
	{
		if(is_char_in_str(str[i], " \t\n") == IS)
			size_tok = 1;
		else if(is_char_in_str(str[i], "<>|" ) == IS)
			value = lexing_metachar(&str[i], lst, &size_tok);
		else 
			value = lexing_word(&str[i], lst, &size_tok);
		if(value == ERROR)
			return(ERROR);
		i += size_tok;
	}
	return(0);
}
