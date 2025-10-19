/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:40:27 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/19 23:48:09 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Header/minishell.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"

typedef struct s_buffer
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
	size_t total_len;
	int factor;
}t_lst_buffer;



void free_chunk_buffer(t_lst_buffer *lst_buffer)
{
	t_buffer *tmp;
	if(lst_buffer->head == NULL || lst_buffer->tail == NULL)	
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

t_buffer *new_buffer(size_t capacity, size_t factor)
{ 
	t_buffer *node;
	node = malloc(sizeof(t_buffer));
	if(node == NULL)
		return(NULL);
	node->buffer = malloc(sizeof(char) * capacity * factor);
	if(node->buffer == NULL)
		return(free(node), NULL);
	node->lenght = 0;
	node->capacity = capacity * factor;
	node->next = NULL;
	return(node);
} 

int add_back_buffer(t_lst_buffer *lst_buffer)
{
	t_buffer *node;
	if(lst_buffer == NULL)
		return(ERROR);
	lst_buffer->capacity *= lst_buffer->factor;
	node = new_buffer(lst_buffer->capacity, lst_buffer->factor);
	if(node == NULL)
		return(ERROR);
	lst_buffer->tail->next = node;
	lst_buffer->tail = node;
	return(0);
}

int cb_append_char(t_lst_buffer* lst_buffer, char c)
{
	size_t *i;
	t_buffer *curr_buffer;
	
	if(lst_buffer->head == NULL || lst_buffer->tail == NULL)
		return(ERROR);
	if(lst_buffer->tail->lenght >= lst_buffer->tail->capacity)
	{
		if(add_back_buffer(lst_buffer) == ERROR)
			return(free_chunk_buffer(lst_buffer), ERROR);
	}
	curr_buffer = lst_buffer->tail;
	i = &curr_buffer->lenght;
	curr_buffer->buffer[*i] = c;
	(*i)++;
	lst_buffer->total_len++;
	curr_buffer->buffer[*i] = '\0';
}

static int cb_loop_append_str(t_lst_buffer* lst_buffer, char *str)
{
	size_t *i;
	size_t j;
	t_buffer *curr_buffer;
	
	j = 0;
	while(str[j] != '\0')
	{
		curr_buffer = lst_buffer->tail;
		i = &curr_buffer->lenght;
		while(curr_buffer->lenght < curr_buffer->capacity && str[j] != '\0')
		{
			curr_buffer->buffer[*i] = str[j];
			(*i)++;
			j++;
			lst_buffer->total_len++;
		}
		if(curr_buffer->lenght == curr_buffer->capacity)
			curr_buffer->buffer[*i] = '\0';
		if(str[j] != '\0')
			if(add_back_buffer(lst_buffer) == ERROR)
				return(ERROR);
	}
	curr_buffer->buffer[*i] = '\0';
	return(0);
}


int cb_append_str(t_lst_buffer *lst_buffer, char *str)
{
	if(lst_buffer->tail == NULL || lst_buffer->head == NULL)
		return(ERROR);
	if(lst_buffer->tail->lenght >= lst_buffer->tail->capacity)
	{
		if(add_back_buffer(lst_buffer) == ERROR)
			return(free_chunk_buffer(lst_buffer), ERROR);
	}
	if(cb_loop_append_str(lst_buffer, str) == ERROR)
		return(free_chunk_buffer(lst_buffer), ERROR);
	return(0);	
}


int init_chunk_buffer(t_lst_buffer *lst_buffer, size_t capacity, int factor)
{
	t_buffer *node;
	*lst_buffer = (t_lst_buffer){0};
	lst_buffer->capacity = capacity;
	lst_buffer->factor = factor;
	node = new_buffer(capacity, factor);
	if(node == NULL)
		return(ERROR);
	lst_buffer->head = node;
	lst_buffer->tail = node;
	return(0);
}

char *fusion_all_chunk(t_lst_buffer *lst_buffer)
{
	char *p;
	t_buffer *tmp;
	int  i;
	int j;
	
	i = 0;
	p = malloc(sizeof(char) * (lst_buffer->total_len + 1));
	if(p == NULL)
		return((free_chunk_buffer(lst_buffer)), NULL);
	tmp = lst_buffer->head;
	while(tmp != NULL)
	{
		j = 0;
		while(j < tmp->lenght)
		{
			p[i] = tmp->buffer[j];
			i++;
			j++;
		}
		tmp = tmp->next;
	}
	p[i] = '\0';
	free_chunk_buffer(lst_buffer);
	return(p);
}

void printf_buffer (t_lst_buffer lst_buffer)
{
	while(lst_buffer.head != NULL)
	{
		printf("NODE:\n");
		printf("str: %s\n",lst_buffer.head->buffer);
		printf("lenght: %lu\n",lst_buffer.head->lenght);
		printf("capacity: %lu\n\n",lst_buffer.head->capacity);
		lst_buffer.head = lst_buffer.head->next;
	}
}

int main()
{
		char *str1 = "bonjour je mappelle michel aehaejwajkewaehaehekja"
	"dawwakdakjd ddawdawjkldadlkadhj "
	"dawdawdjadlklj daw dlkawjdalk dajkl dawdawjkldalwdalkjddlk dlda"
	" jldadj lkjdwladjawlkdj daw dakldalk dj dlkawjdalk 	dawdkadlkadaldja"
	" dlawjdawldjalkd jdjaw dladjlkdjawlkjdlka";
	char *str2;
	
	t_lst_buffer lst_buffer;
	init_chunk_buffer(&lst_buffer, 10, 2);
	cb_append_str(&lst_buffer, str1);
	// printf_buffer(lst_buffer);
	str2 = fusion_all_chunk(&lst_buffer);
	printf("%s\n", str2);
	free(str2);
	
	
}