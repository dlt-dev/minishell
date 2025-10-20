/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_chunk_buffer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 00:57:54 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/21 00:27:19 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_chunk_buffer(t_cb *lst_buffer)
{
	t_buffer *tmp;
	
	if(lst_buffer->head == NULL && lst_buffer->tail == NULL)	
		return;
	tmp = lst_buffer->head;
	while(lst_buffer->head != NULL)
	{
		lst_buffer->head = lst_buffer->head->next; 
		free(tmp->buffer);
		free(tmp);
		tmp = lst_buffer->head;
	}
	lst_buffer->head = NULL;
	lst_buffer->tail = NULL;
	
}

t_buffer *new_buffer(size_t capacity)
{ 
	t_buffer *node;
	
	if(capacity == 0)
		return(NULL);
	node = malloc(sizeof(t_buffer));
	if(node == NULL)
		return(NULL);
	node->buffer = malloc(sizeof(char) * capacity);
	memset(node->buffer, 0, capacity);
	if(node->buffer == NULL)
		return(free(node), NULL);
	node->length = 0;
	node->capacity = capacity;
	node->next = NULL;
	return(node);
} 

int init_chunk_buffer(t_cb *lst_buffer, size_t capacity, size_t factor)
{
	t_buffer *node;
	
	*lst_buffer = (t_cb){0};
	if(capacity <= 0 || factor <= 0 || lst_buffer == NULL)
		return(ERROR);
	lst_buffer->capacity = capacity * factor;
	lst_buffer->factor = factor;
	node = new_buffer(lst_buffer->capacity);
	if(node == NULL)
		return(ERROR);
	lst_buffer->head = node;
	lst_buffer->tail = node;
	return(0);
}
/**
 * @brief 
 * @param init_chunk: initialise une liste de buffer et créé le premier
 * @param new_buffer creer un node avec un buffer de taille "capacity"
 * @param add_back_buffer ajoute le buffer a la fin de la liste
 */

// int main(int argc, char **argv)
// {
// 	char *str2;
	
// 	t_cb lst_buffer;
// 	init_chunk_buffer(&lst_buffer, 200, 2);
// 	cb_append_str(&lst_buffer, argv[1]);
// 	cb_append_str(&lst_buffer, argv[2]);
// 	cb_append_str(&lst_buffer, argv[3]);
// 	cb_append_str(&lst_buffer, argv[4]);

// 	while(lst_buffer.head != NULL)
// 	{
// 		printf("%s\n" , lst_buffer.head->buffer);
// 		lst_buffer.head = lst_buffer.head->next;
// 	}
// 	// printf_buffer(lst_buffer);
// 	// str2 = fusion_all_chunk(&lst_buffer);
	
// 	// printf("%s\n", str2);
// 	// free(str2);
// }