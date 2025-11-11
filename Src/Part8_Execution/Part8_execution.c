// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   part8_execution.c                                  :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: arthurito <arthurito@student.42.fr>        +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/11/03 16:27:16 by jdelattr          #+#    #+#             */
// /*   Updated: 2025/11/08 22:53:51 by arthurito        ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"


// /////////////////////////////////////
// /// @fonctions built_in.c /// 
// ////////////////////////////////////

// void ft_exit(void)
// {
// 	printf("execute exit !\n");
// 	//exit(1);
// }

// // void ft_env(void)// printf de l'env - PAS D'ARGS
// // {
// // 	printf("execute env !\n");
// // }

// void ft_unset(void)
// {
// 	printf("execute unset !\n");
// }

// void ft_export(void)
// {
// 	printf("execute export !\n");
// }

// void ft_pwd(void)
// {
// 	printf("execute pwd !\n");
// }

// void ft_cd(void)
// {
// 	printf("execute cd !\n");
// }

// void ft_echo(void)// + args
// {
// 	printf("execute echo !\n");
// }

// /////////////////////////////////////
// /// @fonctions manage_built_in.c /// 
// ////////////////////////////////////

// enum	e_builtin_type
// {
// 	NO_BUILT_IN,
// 	ECHO,
// 	CD,
// 	PWD,
// 	EXPORT,
// 	UNSET,
// 	ENV,
// 	EXIT,
// };

// int	is_built_in(char *cmd) // return l'enum du builtin
// {
// 	if (ft_strcmp(cmd, "echo") == 0)
// 		return (ECHO);
// 	if (ft_strcmp(cmd, "cd") == 0)
// 		return (CD);
// 	if (ft_strcmp(cmd, "pwd") == 0)
// 		return (PWD);
// 	if (ft_strcmp(cmd, "export") == 0)
// 		return (EXPORT);
// 	if (ft_strcmp(cmd, "unset") == 0)
// 		return (UNSET);
// 	if (ft_strcmp(cmd, "env") == 0)
// 		return (ENV);
// 	if (ft_strcmp(cmd, "exit") == 0)
// 		return (EXIT);
// 	else
// 		return (NO_BUILT_IN);
// }

// int	execute_built_in(int type)//, char **args)
// {
// 	if (type == ECHO) // echo with option -n
// 		ft_echo();
// 	if (type == CD) // with only a relative or absolute path
// 		ft_cd();
// 	if (type == PWD) // no opt
// 		ft_pwd();
// 	if (type == EXPORT) // no opt mais plusieurs args
// 		ft_export();
// 	if (type == UNSET) // no opt
// 		ft_unset();
// 	// if (type == ENV) // no opt
// 	// 	ft_env();
// 	if (type == EXIT) // no opt
// 		ft_exit(); //(args) si args est ce que j'execute qm ???
// 	//else
// 	return (1);
	
// }


// int	manage_execution(t_shell *shell, t_valist *env)// , char **cmds
// {
// 	//ac = nb de cmds
// 	(void) env;
// 	t_exec *cmd_list = shell->cmd_lst;
// 	//t_exec *current = cmd_list;

// 	//t_pipex pipex;

// 	if (cmd_list == NULL)
// 	{
	
// 		return (0); // pas de commande - liste vide
// 		printf("pas de commande");
// 	}

// 	else if (cmd_list->next == NULL && is_built_in(cmd_list->cmds[0]) != 0) // une seul commande et builtin
// 	{
// 		printf("built_in type = %d\n", is_built_in(cmd_list->cmds[0]));
// 		execute_built_in(is_built_in(cmd_list->cmds[0]));//, cmd_list->cmds); + PASSER ENV ? OU SHELL DIRECT
		
// 	}

// /* 	else // j'ai plrs commandes et des pipes (fork() les process)
// 	{
// 		while (current->next != NULL)
// 		{
// 			//ICI JE TROUVE LES BONNES REDIR POUR APPELER PIPEX

// 			pipex.cmd_left = current->cmds;
// 			pipex.cmd_right = current->next->cmds;

// 			pipex(&shell, env);
			
// 			//get_left_cmd();
// 			//get_right_cmd();
			
// 			//execute_cmd(cmd_list, env);

			
// 		}

// 	}*/
// 	return (0);
// }
