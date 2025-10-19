/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:40:27 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/20 00:53:17 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Header/minishell.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"

typedef struct s_buffer
{ 
	char *buffer;
	size_t length;
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

t_buffer *new_buffer(size_t capacity)
{ 
	t_buffer *node;
	
	if(capacity == 0)
		return(NULL);
	node = malloc(sizeof(t_buffer));
	if(node == NULL)
		return(NULL);
	node->buffer = malloc(sizeof(char) * capacity);
	if(node->buffer == NULL)
		return(free(node), NULL);
	node->length = 0;
	node->capacity = capacity;
	node->next = NULL;
	return(node);
} 

int add_back_buffer(t_lst_buffer *lst_buffer)
{
	t_buffer *node;
	
	if(lst_buffer->head == NULL || lst_buffer->tail == NULL)
		return(ERROR);
	lst_buffer->capacity *= lst_buffer->factor;
	node = new_buffer(lst_buffer->capacity);
	if(node == NULL)
		return(ERROR);
	lst_buffer->tail->next = node;
	lst_buffer->tail = node;
	return(0);
}

int cb_append_char(t_lst_buffer* lst_buffer, char c)
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

static int cb_loop_append_str(t_lst_buffer* lst_buffer, char *str)
{
	size_t *i;
	size_t j;
	t_buffer *curr;
	
	j = 0;
	while(str[j] != '\0')
	{
		curr = lst_buffer->tail;
		i = &curr->length;
		while(curr->length < (curr->capacity - 1) && str[j] != '\0')
		{
			curr->buffer[*i] = str[j];
			(*i)++;
			j++;
			lst_buffer->total_len++;
		}
		if(curr->length == (curr->capacity - 1))
			curr->buffer[*i] = '\0';
		if(str[j] != '\0')
			if(add_back_buffer(lst_buffer) == ERROR)
				return(ERROR);
	}
	curr->buffer[*i] = '\0';
	return(0);
}


int cb_append_str(t_lst_buffer *lst_buffer, char *str)
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


int init_chunk_buffer(t_lst_buffer *lst_buffer, size_t capacity, int factor)
{
	t_buffer *node;
	
	if(capacity == 0 || factor == 0)
		return(ERROR);
	*lst_buffer = (t_lst_buffer){0};
	lst_buffer->capacity = capacity * factor;
	lst_buffer->factor = factor;
	node = new_buffer(capacity);
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
		while(j < tmp->length)
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
		printf("length: %lu\n",lst_buffer.head->length);
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
	char *fi = "Traduction de texte : traduisez dans 108 langues en saisissant du texte"
	" Appuyez pour traduire : copiez du texte dans une application, puis appuyez sur" 
	 "l'icône Google Traduction pour le traduire (toutes les langues)"
	"Hors connexion : traduisez sans connexion Internet (59 langues)"
	"Traduction instantanée avec l'appareil photo : traduisez instantanément"
	"le texte figurant dans des images en dirigeant" 
	" l'objectif de votre appareil photo vers celui-ci (94 langues)"
	"Photos : prenez ou importez des photos pour obtenir des tra";
	char *str2;
	
	t_lst_buffer lst_buffer;
	init_chunk_buffer(&lst_buffer, 200, 2);
	cb_append_str(&lst_buffer, str1);
	cb_append_str(&lst_buffer, fi);
	// printf_buffer(lst_buffer);
	str2 = fusion_all_chunk(&lst_buffer);
	printf("%s\n", str2);
	free(str2);
}