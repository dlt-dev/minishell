/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:57:10 by aoesterl          #+#    #+#             */
/*   Updated: 2025/12/02 02:32:15 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	is_bool_in_heap(char *heap)
{
	size_t	i;

	i = 0;
	if (heap == NULL)
		return (0);
	while (heap[i] != '\0')
	{
		if (heap[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_read_until_n(int fd, char *heap)
{
	char	*buffer;
	char	*trash_heap;
	ssize_t	count;

	count = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	while (is_bool_in_heap(heap) == 0)
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if (count == -1 || (count == 0 && heap == NULL))
			return (free(buffer), free(heap), NULL);
		buffer[count] = '\0';
		trash_heap = heap;
		heap = strjoin(heap, buffer);
		free(trash_heap);
		if (count == 0)
			break ;
	}
	return (free(buffer), heap);
}

char	*cutnewline(char *heap)
{
	char	*p;
	size_t	i;

	i = 0;
	while (heap[i] != '\n' && heap[i] != '\0')
		i++;
	if (heap[i] == '\n')
		p = malloc(sizeof(char) * (i + 2));
	else
		p = malloc(sizeof(char) * (i + 1));
	if (p == NULL)
		return (NULL);
	i = 0;
	while (heap[i] != '\0')
	{
		p[i] = heap[i];
		if (heap[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_newheap(char *heap)
{
	char	*trash_heap;
	ssize_t	i;

	i = 0;
	while (heap[i] != '\n' && heap[i] != '\0')
		i++;
	trash_heap = heap;
	if (heap[i] == '\n')
		heap = gnl_strdup(&heap[i + 1]);
	else
		heap = gnl_strdup(&heap[i]);
	free(trash_heap);
	return (heap);
}

char	*get_next_line(int fd)
{
	static char	*heap;
	char		*newline;

	newline = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	heap = ft_read_until_n(fd, heap);
	if (heap == NULL)
		return (NULL);
	newline = cutnewline(heap);
	heap = ft_newheap(heap);
	return (newline);
}

// int main ()
// {
// 	char *a;
// 	int i;
// 	int fd;

// 	i = 0;
// 	fd = open("texte.txt", O_RDONLY);
// 	a =  get_next_line(fd);
// 	while (a != NULL)
// 	{
// 		printf("%s", a);
// 		free(a);
// 		a =  get_next_line(fd);

// 	}
// 	close(fd);
// }