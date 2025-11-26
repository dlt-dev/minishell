/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part2_refonte_heredoc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 19:18:46 by jdelattr          #+#    #+#             */
/*   Updated: 2025/11/26 20:37:06 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *delimit_without_quotes(char *delimit)
{ 
    char *new_delimit;
    t_list *node;
    char *dup;

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

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;
	char	result;

	nb = (long)n;
	if (nb < 0)
	{
		nb = -nb;
		write (fd, "-", 1);
	}
	if (nb >= 10)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putnbr_fd(nb % 10, fd);
	}
	if (nb < 10)
	{
		result = nb + '0';
		write (fd, &result, 1);
	}
}

void here_doc_message(int i, char *delimit)
{ 
	char *m_one;
	char *m_two;

	m_one = "minishell : warning: here-document at line ";
	m_two = " delimited by end-of-file (wanted \'";
	write(2, m_one, ft_strlen(m_one));
	ft_putnbr_fd(i , 2);
	write(2, m_two, ft_strlen(m_two));
	write(2, delimit, ft_strlen(delimit));
	write(2, "\')\n", 3);
	
}

int here_doc_expand(t_shell *shell, char *delimit, int pipefd[2])
{
	char *str;
	char *new_str;
	int i;
	
	i = 1;
	while(1)
	{ 
		str = readline(">");
		if(str == NULL)
			return(here_doc_message(i, delimit), 0);
		if(ft_strcmp(str, delimit) == 0)
		{ 
			free(str);
			break;
		}
		new_str = create_expand_str(shell, str);
		if(new_str == NULL)
			return(free(str), ERROR);
		write(pipefd[1], new_str, ft_strlen(new_str));
		write(pipefd[1], "\n", 1);
		free(str);
		free(new_str);
		i++;
	}
	return(0);
}

int here_doc_no_expand( char *delimit, int pipefd[2])
{
	char *str;
	char *new_delimit;
	int i;

	i = 1;
	new_delimit = delimit_without_quotes(delimit);
	if(new_delimit == NULL)
		return(GEN_ERRNO);
	while(1)
	{
		str = readline(">");
		if(str == NULL)
			return(here_doc_message(i, new_delimit), 
			free(new_delimit), close(pipefd[1]), 0);
		if(ft_strcmp(str, new_delimit) == 0)
		{
			free(new_delimit);
			free(str);
			break;	
		}
		write(pipefd[1], str, ft_strlen(str));
		write(pipefd[1], "\n", 1);
		free(str);
		i++; 
	}
	return(0); // free-exit avec le vrai shell 
}

void routine_heredoc(t_shell *shell, char *delimit, int pipefd[2])
{ 	
	int check;
	close(pipefd[0]);
	if(delimit[0] == '"' || delimit[0] == '\'')
		check = here_doc_no_expand(delimit, pipefd);
	else
		check = here_doc_expand(shell, delimit, pipefd);
	close(pipefd[1]);
	free_exit(shell, check, NULL);
}


int handle_heredoc(t_shell *shell, char *delimit)
{	
	int pipefd[2];

	if (pipe(pipefd) == -1)
		return (ERROR);
	pid_t pid_heredoc;
	pid_heredoc = fork();
	
	if(pid_heredoc == ERROR)
		return(close(pipefd[1]), close(pipefd[0]), GEN_ERRNO);
	if(pid_heredoc == 0)
	{ 
		routine_heredoc(shell, delimit, pipefd);
	}
	if(pid_heredoc > 0 )
	{
		close(pipefd[1]);
		wait_and_status(shell, pid_heredoc);
	}
	return(pipefd[0]);
}


// clean maintenant 
