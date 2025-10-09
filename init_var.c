/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:04:25 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/08 16:41:21 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_var(t_list **lst, t_syntax *syntax)
{ 
	*lst = NULL;
	syntax->blank= " \t";
	syntax->ifs = " \t\n";
	syntax->white_space= " \t\n\v\f\r";
	syntax->metachar=" \t\n|<>";
}
