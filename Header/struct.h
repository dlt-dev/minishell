/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:50:13 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/09 11:51:12 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

enum token_type
{
	WORD, //(WORD)
	META, //(new line)
	PIPE, //(end of file)
	REDIR,
};

typedef struct s_list
{ 
	char *content;
	int type;
	struct s_list *previous;
	struct s_list *next;
}	t_list;

typedef struct s_syntax
{ 
	char *blank;
	char *ifs;
	char *white_space;
	char *ctrl_operat;
	char *metachar;
} t_syntax;

#endif