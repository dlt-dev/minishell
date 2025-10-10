/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:50:13 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/10 17:19:07 by aoesterl         ###   ########.fr       */
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

// typedef struct s_syntax
// { 
// 	char *blank;
// 	char *ifs;
// 	char *white_space;
// 	char *ctrl_operat;
// 	char *metachar;
// } t_syntax;

// typedef struct s_prompt
// { 
// 	char *user;
// 	char *ps_path;
// 	char *col_user;
// 	char *col_path;
// 	char *prompt;
// 	char *empty[1];
// }t_prompt;

// PS1 est le prompt princpal;l


#endif