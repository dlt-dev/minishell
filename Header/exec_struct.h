/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 17:06:42 by jdelattr          #+#    #+#             */
/*   Updated: 2025/10/28 16:34:06 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_STRUCT_H
# define EXEC_STRUCT_H

enum redir_type
{
	SIMPLE_IN,
	SIMPLE_OUT,
	DOUBLE_IN,
	DOUBLE_OUT,
};

typedef struct s_redir // sije rencontre une redirection, je la stock ici puis dans la struct de comande + args qui correspond
{
	int redir_type;
	char *filename;
	//bool quotted; true si filname quoted
	struct  s_redir *next; // pour chainer pls redir - redir multiples
	//ou garder le dernier
}	t_redir;

typedef struct s_exec // stock les commandes entre les pipes
{
	char **cmds; // tb de tab des cmds
	struct s_redir *redir;
	struct s_exec *next;
}	t_exec;

/* typedef struct s_cmd_list // pas utile 
{
	t_cmd_node *command;
	
}	t_cmd_list; */

#endif
