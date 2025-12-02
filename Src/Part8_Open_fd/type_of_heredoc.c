/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_of_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 12:59:57 by aoesterl          #+#    #+#             */
/*   Updated: 2025/12/02 02:57:38 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*delimit_without_quotes(char *delimit)
{
	char	*new_delimit;
	t_list	*node;
	char	*dup;

	dup = ft_strdup(delimit);
	if (dup == NULL)
		return (NULL);
	node = ft_lstnew(dup);
	if (node == NULL)
	{
		free(dup);
		return (NULL);
	}
	new_delimit = delete_quotes_str(node);
	lst_del_one(node);
	return (new_delimit);
}

void	here_doc_message(int i, char *delimit)
{
	char	*m_one;
	char	*m_two;

	m_one = "minishell : warning: here-document at line ";
	m_two = " delimited by end-of-file (wanted \'";
	write(2, m_one, ft_strlen(m_one));
	ft_putnbr_fd(i, 2);
	write(2, m_two, ft_strlen(m_two));
	write(2, delimit, ft_strlen(delimit));
	write(2, "\')\n", 3);
}

int	here_doc_expand(t_shell *shell, char *delimit, int pipefd[2])
{
	char	*str;
	char	*new_str;
	int		i;

	i = 1;
	while (1)
	{
		flag_signal = 0;
		str = readline(">");
		if (str == NULL && flag_signal == SIGINT + 128)
		{
			if (str != NULL)
				free(str);
			return (SIGINT + 128);
		}
		if (str == NULL)
			return (here_doc_message(i, delimit), 0);
		if (ft_strcmp(str, delimit) == 0)
			return (free(str), 0);
		new_str = create_expand_str(shell, str);
		if (new_str == NULL)
			return (free(str), ERROR);
		write(pipefd[1], new_str, ft_strlen(new_str));
		write(pipefd[1], "\n", 1);
		free(str);
		free(new_str);
		i++;
	}
	return (0);
}

int	here_doc_no_expand(char *delimit, int pipefd[2])
{
	char	*str;
	char	*new_delimit;
	int		i;

	i = 1;
	new_delimit = delimit_without_quotes(delimit);
	if (new_delimit == NULL)
		return (GEN_ERRNO);
	while (1)
	{
		flag_signal = 0;
		str = readline(">");
		if (str == NULL && flag_signal == SIGINT + 128)
		{
			if (str != NULL)
				free(str);
			free(new_delimit);
			return (SIGINT + 128);
		}
		if (str == NULL)
			return (here_doc_message(i, new_delimit), free(new_delimit),
				close(pipefd[1]), 0);
		if (ft_strcmp(str, new_delimit) == 0)
			return (free(str), free(new_delimit), 0);
		write(pipefd[1], str, ft_strlen(str));
		write(pipefd[1], "\n", 1);
		free(str);
		i++;
	}
	return (0);
}
