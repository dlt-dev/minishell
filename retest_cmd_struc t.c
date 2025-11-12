/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retest_cmd_struc t.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:11:40 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/12 20:58:34 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*redir_name(int type) // TEST PRINT
{
	if (type == 11)
		return ("INFILE  (<)");
	if (type == 12)
		return ("OUTFILE (>)");
	if (type == 10)
		return ("HEREDOC  (<<)");
	if (type == 13)
		return ("OUTFILE_APPEND (>>)");
	return ("UNKNOWN");
}

void	print_cmd_list(t_exec *head) // TEST PRINT
{
	int i;
	int idx;
	t_redir *redir;
	t_exec *current;

	if (!head)
	{
		printf("print_cmd_list: no commands\n");
		return ;
	}
	idx = 0;
	current = head;

	while (current)
	{
		printf("Command [%d]:\n", idx++);
		if (current->cmds && current->cmds[0])
		{
			i = 0;
			while (current->cmds[i])
			{
				printf("  argv[%d]: %s\n", i, current->cmds[i]);
				i++;
			}
		}
		else
			printf("  (no args)\n");
		redir = current->redir;
		while (redir)
		{
			if (redir->filename)
				printf("  redir: %s  ->  %s\n",
					redir_name(redir->redir_type), redir->filename);
			else
				printf("  redir: %s  ->  (null)\n",
					redir_name(redir->redir_type));
			redir = redir->next;
		}
		current = current->next;
	}
}


t_exec	*create_new_command(void)
{
	t_exec	*command;

	command = malloc(sizeof(t_exec));
	if (!command)
		return (NULL);
	command->cmds = NULL;
	command->redir = NULL;
	command->fd_in = STDIN_FILENO;
	command->fd_out = STDOUT_FILENO;
	command->next = NULL;
	return (command);
}

int add_last_command(t_exec *current, char** new_args, char *cmd, int i)
{ 
	new_args[i] = ft_strdup(cmd);
	if(new_args[i] == ERROR)
		return(ERROR);
	new_args[i + 1] = NULL;
	free(current->cmds);
	current->cmds = new_args;
	return(0);
}

int	add_arg_command(t_exec *current, char *cmd)
{
	int		i;
	int		j;
	char	**new_args;

	i = 0;
	j = 0; 
	if (current->cmds != NULL)
	{ 
		while (current->cmds[i] != NULL)
			i++;
	}
	new_args = malloc(sizeof(char *) * (i + 2));
	if (new_args == NULL)
		return (ERROR);
	while (j < i)
	{
		new_args[j] = current->cmds[j];
		j++;
	}
	if(add_last_command(current, new_args, cmd, i) == ERROR)
		return(ft_free_split(new_args), ERROR);
	return (0);
}

/**
 * @brief @param on parcourt la chaine pour connaitre sa taille
 * on fait un char ** pour recuperer les args. while (j < a mon nombre d'args)
 * je fais new_args [j] = current->cmds[j]; 
 * 
 * 
 */

/**       
 * @brief realloc les add_arg_command avec i +2 , 
 * i correspond a la taille actuelle du tableau de cmd. 
 * on fait i + 2 pour la nouvelle cmd et pour un NULL de fin.
 * @return int 
 */

int	is_valid_redir(t_list *token_next)
{
	if (token_next == NULL) // fin de liste
		return (ERROR);
	if (token_next->flag.type != WORD)
		return (ERROR);
	return (0);
}

int	is_valid_pipe(t_list *token_next)
{
	if (!token_next) // fin de liste
		return (ERROR);
	if (token_next->flag.pipe == PIPE)
		return (ERROR);
	return (0);
}



int check_and_fill_redir(t_exec *current, t_list *token, t_flag flag)
{ 
	if(token->next != NULL && is_valid_redir(token->next) == 0)
	{ 
		if(redir_management(current, token, flag.redir_type) == ERROR)
			return(ERROR);
	}
	else
		return(SYNTAXE_ERR);
	return(0);
}

int check_create_new_command(t_exec **current)
{ 
	

	
}

// faire une fonction manage redir et manage pipe pour etre a la norme :)
int	logical_struct(t_shell *shell, t_exec *current, t_list *token)
{
	int check;
	if(token == NULL)
		return(0);
	shell->cmd_lst = create_new_command();
	current = shell->cmd_lst;
	if(shell->cmd_lst == NULL)
		return(ERROR); 
	if (token->flag.pipe == PIPE)
		return (print_syntax_error(NULL, shell, "|"), 0); // gestion d'erreur
	while (token != NULL)
	{
		if (token->flag.redir == REDIR)
		{
			check = check_and_fill_redir(current, token, token->flag);
			if(check == ERROR)
				return(ERROR);
			if(check == SYNTAXE_ERR)
				return(print_syntax_error(shell, token->content), SYNTAXE_ERR);
			if(check == 0)
				token = token->next;
		}
		else if (token->flag.type == WORD)
		{ 
			if(add_arg_command(current, token->content) == ERROR)
				return(ERROR);
		}
		else if (token->flag.pipe == PIPE && token->next && is_valid_pipe(token->next))
		{
			if(token->next != NULL && is_valid_pipe(token->next) == 0)
			{ 

				
			}
			current->next = create_new_command(); //malloc failed 
			current = current->next;
		}
		else
			return (print_syntax_error(shell, token->content), SYNTAXE_ERR);
		token = token->next;
	}
	return (0);
}

/**
 * @brief @param token= lst 
 * Si token est NULL on return pour proteger
 * Si le premier token est un pipe syntax error 
 * @param head = create new_command : creer un premier node de commande vide et intialiser a NULL
 * 
 * boucle
 * 1) Si l'element est une redir && il est suivi par un autre token && et que ce token est un word
 *  - on manage la redir
 * 2) Si l'element est un WORD 
 * - on l'ajoute
 * 
 * 
 */