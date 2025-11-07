/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:17:54 by jdelattr          #+#    #+#             */
/*   Updated: 2025/11/04 11:30:40 by jdelattr         ###   ########.fr       */
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
#include <fcntl.h>
#include <signal.h>


#include "macro.h"
#include "struct.h"
#include "utils.h"
#include "chunk_buffer.h"
#include "exec_struct.h"

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

//Part7 : cmd_struct
int logical_struct(t_shell *shell, t_list *token);
void redir_management(t_exec *current, t_list *token, int type);
void print_syntax_error(t_exec *head, t_shell *shell, char *tok_content);
char *redir_name(int type); // TEST PRINT
void print_cmd_list(t_exec *head); // TEST PRINT

//PartX_free.c
void free_all(t_shell *shell);
void free_exit(t_shell *shell, int code, char *message);


#endif