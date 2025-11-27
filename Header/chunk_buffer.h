/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_buffer.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:50:33 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/27 12:32:08 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHUNK_BUFFER_H
# define CHUNK_BUFFER_H

# include "struct.h"
# include <stddef.h>

// create_buffer
int			init_chunk_buffer(t_cb *lst_buffer, size_t capacity, size_t factor);
t_buffer	*new_buffer(size_t capacity);
int			add_back_buffer(t_cb *lst_buffer);
void		free_chunk_buffer(t_cb *lst_buffer);

// management_buffer
void		printf_buffer(t_cb lst_buffer);
char		*fusion_all_chunk(t_cb *lst_buffer);
int			cb_append_char(t_cb *lst_buffer, char c);
int			cb_append_str(t_cb *lst_buffer, char *str);

#endif
