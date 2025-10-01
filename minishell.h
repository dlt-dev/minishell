/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:17:54 by jdelattr          #+#    #+#             */
/*   Updated: 2025/09/29 17:59:41 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unsitd.h> 
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>


enum token_type
{
	T_WORD //(WORD)
	T_NL //(new line)
	T_EOF //(end of file)_
	T_PIPE
	T_REDIR_IN
	T_REDIR_OUT
	T_
};

typedef struct s_list
{ 
	char *token;
	int type;
	t_list *previous;
	t_list *next;
}	t_list; 

#endif