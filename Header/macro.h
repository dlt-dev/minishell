/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:52:31 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/04 12:51:49 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACRO_H
#	define MACRO_H

// Couleur macro makefile
#define RED "\033[31;1;3m"
#define GREEN "\033[32;1;3m"
#define YELL "\033[33;1;3m"
#define CYAN "\033[36;1;3m"
#define RESET "\033[m"

//Couleur macro prompt
#define YELL_PS "\033[33;1m"
#define BLUE_PS "\033[34;1m"

// Erreur macro
#define GEN_ERRNO 1
#define ERROR -1
#define IS_NOT 0
#define IS 1
#define CONTINUE -2
#define SYNTAXE_ERR -2 

#endif