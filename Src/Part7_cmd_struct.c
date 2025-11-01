/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part6_logical_structuring.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 17:05:43 by jdelattr          #+#    #+#             */
/*   Updated: 2025/10/31 18:04:23 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* t_exec	**logical_struct(t_list *lst_tokens);
t_exec	*create_new_command();

void	redir_management(t_exec *current_command, t_list *token);
void	print_syntaxe_error(char *content);
int		is_valid_redir(t_list *token);
int		is_valide_pipe(t_list *token);
void	add_arg_command();


char *ft_strdup(char *str); */

//printf qui retourn un int

// free aussi ? // dans le cas d'une erreur de syntaxe - exit ?
void	print_syntax_error(t_shell *shell, char *tok_content)
{
	printf("syntax error near unexpected token '%s'", tok_content);
	shell->exit_status = 127;

}

t_exec	*create_new_command()
{
	t_exec *command;

	command = malloc(sizeof(t_exec));
	if (!command)
		return (NULL);
	command->cmds = NULL;
	command->redir = NULL;
	command->next = NULL;
	return (command);

}

int	add_arg_command(t_exec *current, char *tok_content)
{
	int i;
	int	j;
	char **new_args;

	i = 0;
	j = 0;
	if (!current || !tok_content)
		return (1);

	if (current->cmds)
	{
		while (current->cmds[i])
			i++;
	}

	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return (1);

	while (j < i)
	{
		new_args[j] = current->cmds[j];
		j++;
	}
	
	new_args[i] = ft_strdup(tok_content);
	new_args[i + 1] = NULL;

	free(current->cmds);
	current->cmds = new_args;
	return (0);

}


int	is_valid_redir(t_list *token)
{
	if (!token)//fin de liste
		return (0);
	if (token->flag.type != WORD)
		return (0);
	return (1);
}

int	is_valid_pipe(t_list *token)
{
	if (!token)// fin deliste
		return (0);
	if (token->flag.type == PIPE)
		return (0);
	return (1);
}



t_redir	*create_new_redir(int type, char *filename) // si plusieurs redir a la suite
{
	t_redir *new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->redir_type = type;
	new->filename = ft_strdup(filename);
	new->next = NULL;
	return (new);

}

void	add_redir_command(t_exec *current, t_redir *redir)
{

	t_redir *tmp;

	tmp = 	NULL;
	if (!current || !redir)
		return ;

	if (!current->redir)
	{
		current->redir = redir;
		return ;
	}




	tmp = current->redir;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = redir;
}

// assigne le type de redir et file le filename dans la nod commande correspondante
void	redir_management(t_exec *current, t_list *token)
{
	int type;
	t_list *next_token;
	t_redir *new_redir;

	if (!current || !token)
		return ;

	next_token  = token->next;


	// if pas de suivant ou pas de mot ?


/* 	if (strcmp(token->content, "<") == 0)
		type = SIMPLE_IN;
	else if (strcmp(token->content, ">") == 0)
		type = SIMPLE_OUT;
	else if (strcmp(token->content, "<<") == 0)
		type = DOUBLE_IN;
	else if (strcmp(token->content, ">>") == 0)
		type = DOUBLE_OUT;
	else
		return ; */

	new_redir = create_new_redir(type, next_token->content)// a changer type == next_token->flag.redir_type ;
	add_redir_command(current, new_redir);

}

// si je met enb int alors mes variables doivent etre initiees en amont et 
// passent dans le prototype
t_exec	*logical_struct(t_shell *shell, t_list *lst_tokens)//renvoie code erreur si probleme
{
	t_exec	*head = NULL;
	t_exec	*current = NULL;
	t_list	*token = lst_tokens;

	if (token && token->flag.type == PIPE)
	{
		//free(all)? - rien n'est cree pour le moment
		return(print_syntax_error(shell, "|"), NULL);//(current));
	}
	current = create_new_command();
	head = current;

	while (token)
	{
		if (token->flag.type == REDIR)
		{

			if (!token->next || !is_valid_redir(token->next))// soit piep ou autre redir 
				return (print_syntax_error(shell, token->content), NULL);
			redir_management(current, token);//cree node redir et l'attache a current
			token = token->next;// passer le namefile

		}
		else if (token->flag.type == WORD)
		{

			add_arg_command(current, token->content); // !! si retourn != 0

		}
		else if (token->flag.type == PIPE)
		{
			if (!token->next || !is_valid_pipe(token->next))
				return (print_syntax_error(shell, token->content), NULL);
			current->next = create_new_command();
			current = current->next;
		}

		else // est ce que j'ai d'aute cas ?
			return (print_syntax_error(shell, token->content), NULL);
			
		token = token->next;
	}
	return (head);
}



/*PSEUDO CODE 
 void	logical_struct(lst tokens, )
{
	*parcours list de tokens pour creer les nodes commands - manage les redirs 
	a linterieur des nodes commandes.*

	t_cmd_list *commands_list; // je cree la liste 
	t_command *head = NULL;
	t_command *current = NULL;
	est ce que je calcule deja la taille de la liste avant de la remplir ?

	if (1er tok = pipes )
		print_syntax_error()
	si le premier est un mot je cree 1er commande node
	while (tokens)
	{
		if (redir)
		{
			if (redir + 1 = pipe || redir)
				print_syntaxe_error()
			redir_management(list_tok, *command_list)
		}

		if (word)
		{
			lst_new_cmd_node(*commands list) // je l'ai peut etre cree avant
			while (tok = word) // si des mots suivent 1er mot
				je rentre dans le **tab commande + ses args
				if (tok + 1 != word)
					break;
		}
		
		if (pipe)
		{
			if (pipe est le dernier token (pipe + 1 = NULL)|| pipe + 1 = pipe)
				print_syntaxe_error()
			current = add_new_command_node(&head);
			le new devient le current
		}
		token = token->next
	}
} */
