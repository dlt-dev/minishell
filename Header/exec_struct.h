/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 17:06:42 by jdelattr          #+#    #+#             */
/*   Updated: 2025/11/03 15:27:47 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_STRUCT_H
# define EXEC_STRUCT_H

enum	e_redir_type
{
	SIMPLE_IN,
	SIMPLE_OUT,
	DOUBLE_IN,
	DOUBLE_OUT,
};

typedef struct s_redir
{
	char			*filename;
	int				redir_type;
	struct s_redir	*next;
}	t_redir;

typedef struct s_exec
{
	char			**cmds;
	struct s_redir	*redir;
	struct s_exec	*next;

	//int			**fd([0][1])in et out pour chaques cmds - 
	//par default ca sera stdin et stdout.(0 / 1)
	//int			**pipe; // [in][out] // tab de 2fd
	//The output of each command in the pipeline is
	//connected to the input of the next command via a pipe

}	t_exec;

#endif
