/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_chunk_buffer2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 01:00:24 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/20 21:24:44 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int cb_loop_append_str(t_cb* lst_buffer, char *str)
{
	size_t j;
	t_buffer *curr;
	
	j = 0;
	while(str[j] != '\0')
	{
		curr = lst_buffer->tail;
		while(curr->length < (curr->capacity - 1) && str[j] != '\0')
		{
			curr->buffer[curr->length] = str[j];
			curr->length++;
			j++;
			lst_buffer->total_len++;
		}
		curr->buffer[curr->length] = '\0';
		if(str[j] != '\0')
			if(add_back_buffer(lst_buffer) == ERROR)
				return(ERROR);
	}
	return(0);
}

int cb_append_str(t_cb *lst_buffer, char *str)
{
	if(lst_buffer->tail == NULL || lst_buffer->head == NULL)
		return(ERROR);
	if(lst_buffer->tail->length >= (lst_buffer->tail->capacity - 1))
	{
		if(add_back_buffer(lst_buffer) == ERROR)
			return(free_chunk_buffer(lst_buffer), ERROR);
	}
	if(cb_loop_append_str(lst_buffer, str) == ERROR)
		return(free_chunk_buffer(lst_buffer), ERROR);
	return(0);	
}

int cb_append_char(t_cb* lst_buffer, char c)
{
	size_t i;
	t_buffer *curr;
	
	if(lst_buffer->head == NULL || lst_buffer->tail == NULL)
		return(ERROR);
	if(lst_buffer->tail->length >= (lst_buffer->tail->capacity - 1))
	{
		if(add_back_buffer(lst_buffer) == ERROR)
			return(free_chunk_buffer(lst_buffer), ERROR);
	}
	curr = lst_buffer->tail;
	i = curr->length;
	curr->buffer[i] = c;
	i++;
	curr->length = i;
	lst_buffer->total_len++;
	curr->buffer[i] = '\0';
	return(0);
}

char *fusion_all_chunk(t_cb *lst_buffer)
{
	char *p;
	t_buffer *tmp;
	size_t  i;
	size_t j;
	
	i = 0;
	p = malloc(sizeof(char) * (lst_buffer->total_len + 1));
	if(p == NULL)
		return((free_chunk_buffer(lst_buffer)), NULL);
	tmp = lst_buffer->head;
	while(tmp != NULL)
	{
		j = 0;
		while(tmp->buffer[j] != '\0')
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

void printf_buffer (t_cb lst_buffer)
{
	while(lst_buffer.head != NULL)
	{
		printf("NODE:\n");
		printf("str: %s\n",lst_buffer.head->buffer);
		printf("length: %lu\n",lst_buffer.head->length);
		printf("capacity: %lu\n\n",lst_buffer.head->capacity);
		lst_buffer.head = lst_buffer.head->next;
	}
}