/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:17:54 by jdelattr          #+#    #+#             */
/*   Updated: 2025/10/27 19:16:35 by aoesterl         ###   ########.fr       */
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
void flag_word(t_list*lst);
void put_flags (t_list *lst);

//Part4: Expansion
int	handle_single_quotes(t_cb *lst_buffer, char *str); 
int handle_double_quotes(t_shell *shell, t_cb* lst_buffer, char *str);
int handle_dollar(t_shell* shell, t_cb* lst_buffer, char *str);
int	expand_shell_param(t_shell *shell, t_list *lst);

//Part5: Word_splitting 
int split_param(t_shell *shell, t_list *curr_node, t_list *prev_node);
int count_word_hdle_quotes(char *str);
char **word_splitting(char *str, int count_word);



//PartX_free.c
void free_all(t_shell *shell);
void free_exit(t_shell *shell, int code, char *message);


#endif