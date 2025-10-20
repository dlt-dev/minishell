/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:40:27 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/20 22:03:28 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Header/minishell.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"

// void free_chunk_buffer(t_cb *lst_buffer)
// {
// 	t_buffer *tmp;
// 	if(lst_buffer->head == NULL && lst_buffer->tail == NULL)	
// 		return;
// 	tmp = lst_buffer->head;
// 	while(lst_buffer->head != NULL)
// 	{
// 		lst_buffer->head = lst_buffer->head->next; 
// 		free(tmp->buffer);
// 		free(tmp);
// 		tmp = lst_buffer->head;
// 	}
// 	lst_buffer->head = NULL;
// 	lst_buffer->tail = NULL;
	
// }

// t_buffer *new_buffer(size_t capacity)
// { 
// 	t_buffer *node;
	
// 	if(capacity == 0)
// 		return(NULL);
// 	node = malloc(sizeof(t_buffer));
// 	if(node == NULL)
// 		return(NULL);
// 	node->buffer = malloc(sizeof(char) * capacity);
// 	if(node->buffer == NULL)
// 		return(free(node), NULL);
// 	node->length = 0;
// 	node->capacity = capacity;
// 	node->next = NULL;
// 	return(node);
// } 

// int add_back_buffer(t_cb *lst_buffer)
// {
// 	t_buffer *node;
	
// 	if(lst_buffer->head == NULL || lst_buffer->tail == NULL)
// 		return(ERROR);
// 	lst_buffer->capacity *= lst_buffer->factor;
// 	node = new_buffer(lst_buffer->capacity);
// 	if(node == NULL)
// 		return(ERROR);
// 	lst_buffer->tail->next = node;
// 	lst_buffer->tail = node;
// 	return(0);
// }

// int init_chunk_buffer(t_cb *lst_buffer, size_t capacity, int factor)
// {
// 	t_buffer *node;
	
// 	*lst_buffer = (t_cb){0};
// 	if(capacity <= 0 || factor <= 0)
// 		return(ERROR);
// 	lst_buffer->capacity = capacity * factor;
// 	lst_buffer->factor = factor;
// 	node = new_buffer(capacity);
// 	if(node == NULL)
// 		return(ERROR);
// 	lst_buffer->head = node;
// 	lst_buffer->tail = node;
// 	return(0);
// }

// static int cb_loop_append_str(t_cb* lst_buffer, char *str)
// {
// 	size_t j;
// 	t_buffer *curr; types for ‘
	
// 	j = 0;
// 	while(str[j] != '\0')
// 	{
// 		curr = lst_buffer->tail;
// 		while(curr->length < (curr->capacity - 1) && str[j] != '\0')
// 		{
// 			curr->buffer[curr->length] = str[j];
// 			curr->length++;
// 			j++;
// 			lst_buffer->total_len++;
// 		}
// 		curr->buffer[curr->length] = '\0';
// 		if(str[j] != '\0')
// 			if(add_back_buffer(lst_buffer) == ERROR)
// 				return(ERROR);
// 	}
// 	return(0);
// }

// int cb_append_str(t_cb *lst_buffer, char *str)
// {
// 	if(lst_buffer->tail == NULL || lst_buffer->head == NULL)
// 		return(ERROR);
// 	if(lst_buffer->tail->length >= (lst_buffer->tail->capacity - 1))
// 	{
// 		if(add_back_buffer(lst_buffer) == ERROR)
// 			return(free_chunk_buffer(lst_buffer), ERROR);
// 	}
// 	if(cb_loop_append_str(lst_buffer, str) == ERROR)
// 		return(free_chunk_buffer(lst_buffer), ERROR);
// 	return(0);	
// }

// int cb_append_char(t_cb* lst_buffer, char c)
// {
// 	size_t i;
// 	t_buffer *curr;
	
// 	if(lst_buffer->head == NULL || lst_buffer->tail == NULL)
// 		return(ERROR);
// 	if(lst_buffer->tail->length >= (lst_buffer->tail->capacity - 1))
// 	{
// 		if(add_back_buffer(lst_buffer) == ERROR)
// 			return(free_chunk_buffer(lst_buffer), ERROR);
// 	}
// 	curr = lst_buffer->tail;
// 	i = curr->length;
// 	curr->buffer[i] = c;
// 	i++;
// 	curr->length = i;
// 	lst_buffer->total_len++;
// 	curr->buffer[i] = '\0';
// 	return(0);
// }

// char *fusion_all_chunk(t_cb *lst_buffer)
// {
// 	char *p;
// 	t_buffer *tmp;
// 	size_t  i;
// 	size_t j;
	
// 	i = 0;
// 	p = malloc(sizeof(char) * (lst_buffer->total_len + 1));
// 	if(p == NULL)
// 		return((free_chunk_buffer(lst_buffer)), NULL);
// 	tmp = lst_buffer->head;
// 	while(tmp != NULL)
// 	{
// 		j = 0;
// 		while(j < tmp->length)
// 		{
// 			p[i] = tmp->buffer[j];
// 			i++;
// 			j++;
// 		}
// 		tmp = tmp->next;
// 	}
// 	p[i] = '\0';
// 	free_chunk_buffer(lst_buffer);
// 	return(p);
// }

// void printf_buffer (t_cb lst_buffer)
// {
// 	while(lst_buffer.head != NULL)
// 	{
// 		printf("NODE:\n");
// 		printf("str: %s\n",lst_buffer.head->buffer);
// 		printf("length: %lu\n",lst_buffer.head->length);
// 		printf("capacity: %lu\n\n",lst_buffer.head->capacity);
// 		lst_buffer.head = lst_buffer.head->next;
// 	}
// }

/**
 * @brief 
 * @param init_chunk: initialise une liste de buffer et créé le premier
 * @param new_buffer creer un node avec un buffer de taille "capacity"
 * @param add_back_buffer ajoute le buffer a la fin
 * 
 */

int main(int argc, char **argv)
{
	char *str2;
	
	t_cb lst_buffer;
	init_chunk_buffer(&lst_buffer, 200, 2);
	cb_append_str(&lst_buffer, argv[1]);
	cb_append_str(&lst_buffer, argv[2]);
	cb_append_str(&lst_buffer, argv[3]);
	cb_append_str(&lst_buffer, argv[4]);

	while(lst_buffer.head != NULL)
	{
		printf("%s\n" , lst_buffer.head->buffer);
		lst_buffer.head = lst_buffer.head->next;
	}
	// printf_buffer(lst_buffer);
	// str2 = fusion_all_chunk(&lst_buffer);
	
	// printf("%s\n", str2);
	// free(str2);
}