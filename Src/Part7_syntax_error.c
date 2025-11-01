/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part7_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:11:09 by jdelattr          #+#    #+#             */
/*   Updated: 2025/11/01 14:50:47 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_syntax_error(t_shell *shell, char *tok_content)
{
	printf("syntax error near unexpected token '%s'", tok_content);
	shell->exit_status = 127;
}