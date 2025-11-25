/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_chunk_buffer2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 01:00:24 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/25 21:14:06 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_back_buffer(t_cb *lst_buffer)
{
	t_buffer	*node;

	if (lst_buffer->head == NULL || lst_buffer->tail == NULL)
		return (ERROR);
	lst_buffer->capacity *= lst_buffer->factor;
	node = new_buffer(lst_buffer->capacity);
	if (node == NULL)
		return (ERROR);
	lst_buffer->tail->next = node;
	lst_buffer->tail = node;
	return (0);
}

static int	cb_loop_append_str(t_cb *lst_buffer, char *str)
{
	size_t		i;
	t_buffer	*curr;

	i = 0;
	while (str[i] != '\0')
	{
		curr = lst_buffer->tail;
		while (curr->length < (curr->capacity - 1) && str[i] != '\0')
		{
			curr->buffer[curr->length] = str[i];
			curr->length++;
			i++;
			lst_buffer->total_len++;
		}
		curr->buffer[curr->length] = '\0';
		if (str[i] != '\0')
		{
			if (add_back_buffer(lst_buffer) == ERROR)
				return (ERROR);
		}
	}
	return (0);
}

int	cb_append_str(t_cb *lst_buffer, char *str)
{
	if (lst_buffer->tail == NULL || lst_buffer->head == NULL)
		return (ERROR);
	if (lst_buffer->tail->length >= (lst_buffer->tail->capacity - 1))
	{
		if (add_back_buffer(lst_buffer) == ERROR)
			return (free_chunk_buffer(lst_buffer), ERROR);
	}
	if (cb_loop_append_str(lst_buffer, str) == ERROR)
		return (free_chunk_buffer(lst_buffer), ERROR);
	return (0);
}

int	cb_append_char(t_cb *lst_buffer, char c)
{
	t_buffer	*curr;

	if (lst_buffer->head == NULL || lst_buffer->tail == NULL)
		return (ERROR);
	if (lst_buffer->tail->length >= (lst_buffer->tail->capacity - 1))
	{
		if (add_back_buffer(lst_buffer) == ERROR)
			return (free_chunk_buffer(lst_buffer), ERROR);
	}
	curr = lst_buffer->tail;
	curr->buffer[curr->length] = c;
	curr->length++;
	lst_buffer->total_len++;
	curr->buffer[curr->length] = '\0';
	return (0);
}

char	*fusion_all_chunk(t_cb *lst_buffer)
{
	char		*p;
	t_buffer	*tmp;
	size_t		i;
	size_t		j;

	i = 0;
	p = malloc(sizeof(char) * (lst_buffer->total_len + 1));
	if (p == NULL)
		return ((free_chunk_buffer(lst_buffer)), NULL);
	tmp = lst_buffer->head;
	while (tmp != NULL)
	{
		j = 0;
		while (tmp->buffer[j] != '\0')
		{
			p[i] = tmp->buffer[j];
			i++;
			j++;
		}
		tmp = tmp->next;
	}
	p[i] = '\0';
	free_chunk_buffer(lst_buffer);
	return (p);
}
