/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:40:19 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/13 23:36:43 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS _H

#include <stddef.h>
#include "struct.h"

//utils_lst.c
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
int fill_in_lst(t_list **lst, char *content, int type, int flag_quote);
void print_str_lst(t_list *lst);

//utils_libft1.c
size_t	ft_strlen(char *str);
char	*ft_strdup(char *s);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void ft_strcat(char *src, char *dest);
char *ft_strndup(char *str, int size);

//utils_libft2.c
int is_str(char c, char *sep);
void write_str(char *str); 


//free_exit.c
void ft_free_lst(t_list **lst);
void ft_free_str(char **str);
void free_all(t_shell *shell);
void free_exit(t_shell *shell, int code, char *message);

#endif