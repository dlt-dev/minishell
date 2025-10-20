/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:17:54 by jdelattr          #+#    #+#             */
/*   Updated: 2025/10/21 01:00:43 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h> 
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "macro.h"
#include "struct.h"
#include "utils.h"
#include "chunk_buffer.h"

//Part0: init_variable
int init_variable(t_shell *shell, int argc, char **argv, char **envp);

//Part1: Prompt
int get_prompt(t_prompt *invite);

//Part2: lexing
int lexing(char *str, t_list **lst);

//Part3: Put_flag
void put_flags (t_list *lst);

//Part4: Expansion
int length_name(char *name);
int expand_shell_param(t_shell *shell, t_list *lst);

#endif