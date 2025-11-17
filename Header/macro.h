/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:52:31 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/15 18:11:28 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACRO_H
#	define MACRO_H

// Couleur macro makefile
#define YELL "\033[33;1;3m"
#define CYAN "\033[36;1;3m"
#define RESET "\001\033[0m\002"

//Couleur macro prompt
#define YELL_PS "\001\033[33;1m\002"
#define BLUE_PS "\001\033[34;1m\002"
#define GREEN "\001\033[32;1m\002"
#define RED "\001\033[31;1m\002"

// Erreur macro
#define GEN_ERRNO 1
#define ERROR -1
#define IS_NOT 0
#define IS 1
#define CONTINUE -2
#define SYNTAXE_ERR -2 
#define MALLOC_FAILED -1

#endif