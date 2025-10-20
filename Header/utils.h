/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:40:19 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/21 01:00:34 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS _H

#include <stddef.h>
#include "struct.h"

//Utils_lenght.c
size_t	ft_strlen(char *str);
int	length_name(char *name);
int len_number (int nb);


//utils_libft1.c
char *ft_strdup(char *s);
char *ft_strndup(char *str, int size);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void ft_strcat(char *src, char *dest);

//utils_libft2.c
int is_str(char c, char *sep);
void write_str(char *str);
void *ft_memset(void* str, int c, size_t n); 


//utils_lst.c
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
int fill_in_lst(t_list **lst, char *content, int type);
void lst_del_one(t_list *node);

//utils_lst2.c
void node_exchange(t_list **lst, t_list *curr_node, t_list *prev_node, t_list *new_node);

//Utils_print_lst.c
void print_var_lst(t_valist *var);
void print_str_lst(t_list *lst);

//utils_va_lst.c
t_valist *var_new(char *name, char *value);
void var_addback(t_valist **var, t_valist *new);
int var_in_lst(t_valist **var, char *name, char *value);
void ft_free_var(t_valist **var);

//ParX_free.c
void ft_free_lst(t_list **lst);
void ft_free_str(char **str);
void free_all(t_shell *shell);
void free_exit(t_shell *shell, int code, char *message);

#endif