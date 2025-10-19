/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_chunk_buffer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 00:57:54 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/20 01:06:20 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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


// int main()
// {
// 		char *str1 = "bonjour je mappelle michel aehaejwajkewaehaehekja"
// 	"dawwakdakjd ddawdawjkldadlkadhj "
// 	"dawdawdjadlklj daw dlkawjdalk dajkl dawdawjkldalwdalkjddlk dlda"
// 	" jldadj lkjdwladjawlkdj daw dakldalk dj dlkawjdalk 	dawdkadlkadaldja"
// 	" dlawjdawldjalkd jdjaw dladjlkdjawlkjdlka";
// 	char *fi = "Traduction de texte : traduisez dans 108 langues en saisissant du texte"
// 	" Appuyez pour traduire : copiez du texte dans une application, puis appuyez sur" 
// 	 "l'icône Google Traduction pour le traduire (toutes les langues)"
// 	"Hors connexion : traduisez sans connexion Internet (59 langues)"
// 	"Traduction instantanée avec l'appareil photo : traduisez instantanément"
// 	"le texte figurant dans des images en dirigeant" 
// 	" l'objectif de votre appareil photo vers celui-ci (94 langues)"
// 	"Photos : prenez ou importez des photos pour obtenir des tra";
// 	char *str2;
	
// 	t_lst_buffer lst_buffer;
// 	init_chunk_buffer(&lst_buffer, 200, 2);
// 	cb_append_str(&lst_buffer, str1);
// 	cb_append_str(&lst_buffer, fi);
// 	// printf_buffer(lst_buffer);
// 	str2 = fusion_all_chunk(&lst_buffer);
// 	printf("%s\n", str2);
// 	free(str2);
// }