/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 17:06:42 by jdelattr          #+#    #+#             */
/*   Updated: 2025/11/12 12:48:39 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_STRUCT_H
# define EXEC_STRUCT_H

typedef struct s_pipex
{
	char	**cmd1;
	char	**cmd2;
}	t_pipex;

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

	int fd_in;//je stock les derniers fd de mes open STDIN
	int fd_out;//je set a -1 par default STDOUT

}	t_exec;

#endif

/* \1
\2 
pour les parties non affichaches
*/