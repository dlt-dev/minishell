/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 17:06:42 by jdelattr          #+#    #+#             */
/*   Updated: 2025/10/31 18:59:44 by jdelattr         ###   ########.fr       */
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

typedef struct s_redir // si je rencontre une / des redirection, je la stock ici
{
	char *filename;
	struct  s_redir *next; // si redir multiples
}	t_redir;

typedef struct s_exec // stock les commandes entre les pipes
{
	char **cmds; // tab de tab des cmds
	struct s_redir *redir;
	struct s_exec *next;
}	t_exec;

#endif
