/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 13:47:28 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/27 15:45:38 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_char_in_str(char c, char *sep)
{ 
	int i;
	
	i = 0;
	while(sep[i] != '\0') 
	{ 
		if(c == sep[i])
			return(IS);
		i++; 
	}
	return(IS_NOT);
}

void write_str(char *str)
{
	write(1, str, ft_strlen(str));
}

void *ft_memset(void* str, int c, size_t n)
{
	size_t i;
	
	i = 0;
	while(i < n)
	{
		((unsigned char*)str)[i] = (unsigned char) c;
		i++;
	}
	return(str);
}

void    *ft_memcpy(void *dest, const void *src, size_t n)
{
        size_t                  i;
        unsigned char   *src_cast;
        unsigned char   *dest_cast;

        i = 0;
        if (dest == NULL && src == NULL)
                return (NULL);
        src_cast = (unsigned char *)src;
        dest_cast = (unsigned char *)dest;
        while (i < n)
        {
                dest_cast[i] = src_cast[i];
                i++;
        }
        return (dest_cast);
}
