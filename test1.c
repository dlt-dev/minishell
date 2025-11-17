/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:55:59 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/15 19:00:41 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_error_message(char * fonction)
{
    char *error;
    char *minishell;

    minishell = "minishell: ";
    error = strerror(errno);
    write(2, minishell, ft_strlen(minishell));
    write(2, fonction, ft_strlen(fonction));
    write(2 , ": ", 2);
    write(2 , error, ft_strlen(error)); 
}

int main()
{
    print_error_message("cd"); 

}