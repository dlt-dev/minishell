/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part5_word_splitting_main.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:24:23 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/26 17:26:28 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*split_in_lst(char **tab, t_list *curr_node)
{
	t_list	*lst;
	t_list	*tmp;
	int		i;

	i = 0;
	lst = NULL;
	while (tab[i] != NULL)
	{
		tmp = ft_lstnew(tab[i]);
		if (tmp == NULL)
			return (ft_free_lst(&lst), NULL);
		ft_memcpy(&tmp->flag, &curr_node->flag, sizeof(t_flag));
		ft_lstadd_back(&lst, tmp);
		i++;
	}
	return (lst);
}

int	lst_splitted(t_list *curr_node, t_list **ins_lst)
{
	int		count_word;
	char	**tab;

	count_word = count_word_hdle_quotes(curr_node->content);
	if (count_word > 1)
	{
		tab = word_splitting(curr_node->content, count_word);
		if (tab == NULL)
			return (ERROR);
		*ins_lst = split_in_lst(tab, curr_node);
		if (ins_lst == NULL)
			return (ft_free_split(&tab), ERROR);
		free(tab);
		return (CONTINUE);
	}
	return (0);
}

/**

	* @brief on commence par compter le nombre 
	de word dans notre curr_node->content
 * s'il y a 2 mots ou plus,
	il faut faire un @param word_splitting. tab va recup les
 * differents mots dans un char **. une fois que tab est full,
	on va mettre les char*

	* dans une liste chainees @param ins_lst a tra
	vers la fonction @param split_in_lst.
 */

void	jump_insert_lst(t_shell *shell, t_list **curr_node, t_list **prev_node,
		t_list *ins_lst)
{
	int	i;

	i = insert_multi_node(*curr_node, ins_lst);
	del_one_relink(&shell->lst, *curr_node, *prev_node);
	*curr_node = ins_lst;
	while (i > 0)
	{
		*prev_node = *curr_node;
		*curr_node = (*curr_node)->next;
		i--;
	}
}

//Factoriser, faire valider par le Grand Arthur
int	split_param(t_shell *shell, t_list *curr_node, t_list *prev_node)
{
	t_list	*ins_lst;
	int		step;

	ins_lst = NULL;
	if (curr_node == NULL)
		return (0);
	while (curr_node != NULL)
	{
		if (curr_node->flag.word_type == CMD)
		{
			step = lst_splitted(curr_node, &ins_lst);
			if (step == ERROR)
				return (ERROR);
			else if (step == CONTINUE)
			{
				jump_insert_lst(shell, &curr_node, &prev_node, ins_lst);
				continue ;
			}
		}
		prev_node = curr_node;
		curr_node = curr_node->next;
	}
	return (0);
}

//Au cas ou
// int	split_param(t_shell *shell, t_list *curr_node, t_list *prev_node)
// {
// 	t_list	*ins_lst;
// 	int		step;

// 	ins_lst = NULL;
// 	if (curr_node == NULL)
// 		return (0);
// 	while (curr_node != NULL)
// 	{
// 		if (curr_node->flag.word_type == CMD)
// 		{
// 			step = lst_splitted(curr_node, &ins_lst);
// 			if (step == ERROR)
// 				return (ERROR);
// 			else if (step == CONTINUE)
// 				jump_insert_lst(shell, &curr_node, &prev_node, ins_lst);
// 			else
// 			{
// 				prev_node = curr_node;
// 				curr_node = curr_node->next;
// 			}
// 		}
// 		else
// 		{
// 			prev_node = curr_node;
// 			curr_node = curr_node->next;
// 		}
// 	}
// 	return (0);
// }

/**
 * @brief @param split_param: on parcours la liste chaine.
 * si on rencontre un node qui a le flag CMD, on est cense faire
 * un wordsplitting car les objets FILE ne sont pas touche par le
 * splitting. @param step va nous permettre de savoir ce qu'il s'est
 * passer dans @param lst_splitted. Si cette fonction:
 * - @return ERROR, une erreur s'est produite
 * - @return 0, ca veut dire que la fonction a bien marche mais qu'il n'y a pas
 * besoin de split car count_word
 * - @return CONTINUE, ca veut dire qu'un mot a ete split, a ete mis danns
 * @param  ins_lst.
 * on voit apres que @param ins_lst n'est inserer dans notre liste que si
 * step == CONTINUE, donc qu'un word splitting a eu lieu. Ainsi,
	pour parcourir notre
 * chaine 3 choses vont se faire:
 *
	- Si @param curr_node a un flag file : le previous_node devient le curr_node et
 * et on passe au node suivant.
 *
	- SI @param curr_node a un flag CMD et qu'il n'y a qu'un mot: step n'a pas la valeur
 * CONTINUE et prev_node devient curr_node et on passe au noeud suivant
 *
	- Si @param curr_node a un flag CMD et qu'il y a plusieurs mot: step a la valeur

	* CONTINUE et la liste est inserer via @param jump_insert_lst. cette derniere fonction

	* insert la nouvelle liste dans l'ancienne au niveau de @param curr_node et deplace

	* les pointeurs curr_node et prev_node a la fin de la nouvelle liste inserer afin de
 * pouvoir controler les noeuds suivant de notre listes.
 */
