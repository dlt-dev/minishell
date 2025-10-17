/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:40:27 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/17 18:30:18 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Header/minishell.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"

typedef struct sl_buffer
{ 
	char *buffer;
	size_t lenght;
	size_t capacity;
	struct s_buffer *next;
}t_buffer;

typedef struct s_ptr_buffer
{
	t_buffer *head;
	t_buffer *tail;
	size_t capacity;
	int factor;
}t_lst_buffer;

void init_chunk_buffer(t_lst_buffer *lst_buffer, size_t capacity, int factor)
{ 
	*lst_buffer = (t_lst_buffer){0};
	lst_buffer->capacity = capacity;
	lst_buffer->factor = factor;
}

t_buffer *new_buffer(size_t capacity, size_t factor)
{ 
	t_buffer *node;
	node = malloc(sizeof(t_buffer));
	if(node == NULL)
		return(NULL);
	node->buffer = malloc(sizeof(char) * capacity * factor);
	if(node->buffer == NULL)
		return(NULL);
	node->next = NULL;
	return(node);
} 


void first_buffer(t_lst_buffer *lst_buffer, size_t *capacity, size_t factor)
{
	t_buffer *node;
	node = new_buffer(capacity, factor);
	if(node == NULL)
		return(NULL);
	node->lenght = 0;
	node->capacity = (*capacity) * factor;
	lst_buffer->head = node;
	lst_buffer->tail = node;
	(*capacity) *= factor;
}

void bfufer_ 

int main()
{
	t_lst_buffer lst_buffer;
	init_chunk_buffer(&lst_buffer, 10, 2);
	first_buffer(&lst_buffer, lst_buffer.capacity, lst_buffer.factor);




	
	char *str1 = "bonjour je mappelle michel aehaejwajkewaehaehekja"
	"dawwakdakjd ddawdawjkldadlkadhj "
	"dawdawdjadlklj daw dlkawjdalk dajkl dawdawjkldalwdalkjddlk dlda"
	" jldadj lkjdwladjawlkdj daw dakldalk dj dlkawjdalk 	dawdkadlkadaldja"
	" dlawjdawldjalkd jdjaw dladjlkdjawlkjdlka";
	char *str2;
	
	
}