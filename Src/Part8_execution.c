/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part8_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:27:16 by jdelattr          #+#    #+#             */
/*   Updated: 2025/11/07 14:25:19 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/////////////////////////////////////
/// @fonctions manage_built_in.c /// 
////////////////////////////////////

enum	e_builtin_type
{
	NO_BUILT_IN,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
};

int	is_built_in(char *cmd) // return l'enum du builtin
{
	if (ft_strncmp(cmd, "echo", ft_strlen("echo")) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", ft_strlen("cd")) == 0)
		return (2);
	if (ft_strncmp(cmd, "pwd", ft_strlen("pwd")) == 0)
		return (3);
	if (ft_strncmp(cmd, "export", ft_strlen("export")) == 0)
		return (4);
	if (ft_strncmp(cmd, "unset", ft_strlen("unset")) == 0)
		return (5);
	if (ft_strncmp(cmd, "env", ft_strlen("env")) == 0)
		return (6);
	if (ft_strncmp(cmd, "exit", ft_strlen("exit")) == 0)
		return (7);

	else
		return (NO_BUILT_IN);
}

int	execute_built_in(int type)//, char **args)
{
	if (type == ECHO) // echo with option -n
		ft_echo();
	if (type == CD) // with only a relative or absolute path
		ft_cd();
	if (type == PWD) // no opt
		ft_pwd();
	if (type == EXPORT) // no opt mais plusieurs args
		ft_export();
	if (type == UNSET) // no opt
		ft_unset();
	if (type == ENV) // no opt
		ft_env();
	if (type == EXIT) // no opt
		ft_exit(); //(args) si args est ce que j'execute qm ???
	//else
	return (1);
	
}

/////////////////////////////////////
/// @fonctions built_in.c /// 
////////////////////////////////////

void ft_exit()
{
	printf("execute exit !\n");
	//exit(1);
}

void ft_env()// printf de l'env - PAS D'ARGS
{
	printf("execute env !\n");
}

void ft_unset()
{
	printf("execute unset !\n");
}

void ft_export()
{
	printf("execute export !\n");
}

void ft_pwd()
{
	printf("execute pwd !\n");
}

void ft_cd()
{
	printf("execute cd !\n");
}

void ft_echo()// + args
{
	printf("execute echo !\n");
}


/////////////////////////////////////
/// @fonctions fork_process.c /// 
////////////////////////////////////

typedef struct s_pipex
{
	char	**cmd_left;
	char	**cmd_right;
}	t_pipex;


void execute_cmd()
{

}


/* char	**get_left_cmd(char **av)
{
	char	**cmd;

	if (av[2] == NULL || av[2][0] == '\0')
		cmd_not_found();
	cmd = ft_split(av[2], ' ');
	if (!cmd || !cmd[0] || cmd[0][0] == '\0')
	{
		ft_free_tab(cmd);
		cmd_not_found();
	}
	return (cmd);
}

char	**get_right_cmd(char **av, char **tofree)
{
	char	**cmd;

	if (av[3] == NULL || av[3][0] == '\0')
	{
		ft_free_tab(tofree);
		cmd_not_found();
	}
	cmd = ft_split(av[3], ' ');
	if (!cmd || !cmd[0] || cmd[0][0] == '\0')
	{
		ft_free_tab(cmd);
		ft_free_tab(tofree);
		cmd_not_found();
	}
	return (cmd);
} */

char	*find_my_cmd_path(char *my_cmd, t_valist*env) // a modifier pour parcourir la liste env
{
	int		i;
	char	*my_path;
	char	**paths;

	my_path = NULL;
	paths = split_tab_paths(envp);
	i = 0;
	while (paths[i])
	{
		my_path = malloc(ft_strlen(paths[i]) + 1 + ft_strlen(my_cmd) + 1);
		if (!my_path)
			return (NULL);
		ft_strcpy(my_path, paths[i]);
		ft_strcat(my_path, "/");
		ft_strcat(my_path, my_cmd);
		if (access(my_path, X_OK) == 0)
		{
			ft_free_tab(paths);
			return (my_path);
		}
		free(my_path);
		i++;
	}
	ft_free_tab(paths);
	return (NULL);
}

pid_t	fork_child_one(char **av, int fd_pipe[2], char **envp, t_pipex *pipex)
{
	pid_t	child1;

	child1 = fork();
	if (child1 < 0)
		perror("fork: ");
	if (child1 == 0)
	{
		ft_free_tab(pipex->cmd_right);
		routine_child_one(av, fd_pipe, pipex->cmd1, envp);
	}
	return (child1);
}

pid_t	fork_child_two(char **av, int fd_pipe[2], char **envp, t_pipex *pipex)
{
	pid_t	child2;

	child2 = fork();
	if (child2 < 0)
		perror("fork: ");
	if (child2 == 0)
	{
		ft_free_tab(pipex->cmd1);
		routine_child_two(av, fd_pipe, pipex->cmd2, envp);
	}
	return (child2);
}

void	routine_child_one(char **av, int fd_pipe[2], char **cmd1, char **envp)
{
	int		fd1;
	char	*my_cmd_path;

	fd1 = open(av[1], O_RDONLY);
	check_error_one(fd1, cmd1, av, fd_pipe);
	my_cmd_path = find_my_cmd_path(cmd1[0], envp);
	if (!my_cmd_path || my_cmd_path[0] == '\0')
	{
		ft_free_tab(cmd1);
		close(fd_pipe[1]);
		close(fd1);
		path_not_found();
	}
	dup2(fd1, STDIN_FILENO);
	dup2(fd_pipe[1], STDOUT_FILENO);
	close(fd_pipe[1]);
	close(fd1);
	execve(my_cmd_path, cmd1, envp);
	perror("execve");
	exit(1);
}

void	routine_child_two(char **av, int fd_pipe[2], char **cmd2, char **envp)
{
	int		fd2;
	char	*my_cmd_path;

	fd2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	check_error_two(fd2, cmd2, av, fd_pipe);
	my_cmd_path = find_my_cmd_path(cmd2[0], envp);
	if (!my_cmd_path || my_cmd_path[0] == '\0')
	{
		ft_free_tab(cmd2);
		close(fd_pipe[1]);
		close(fd2);
		path_not_found();
	}
	dup2(fd_pipe[0], STDIN_FILENO);
	dup2(fd2, STDOUT_FILENO);
	close(fd_pipe[0]);
	close(fd2);
	execve(my_cmd_path, cmd2, envp);
	perror("execve");
	exit(1);
}

void	pipex(t_shell *shell, t_valist *env, t_pipex pipex)//(char **av, char **envp)
{
	t_pipex	pipex;
	int		fd_pipe[2];
	int		status;
	pid_t	child1;
	pid_t	child2;

	if (pipe(fd_pipe) == -1)
		return (perror("pipe"));
	child1 = fork_child_one(av, fd_pipe, env, &pipex);
	child2 = fork_child_two(av, fd_pipe, env, &pipex);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
	ft_free_tab(pipex.cmd_left);
	ft_free_tab(pipex.cmd_right);
	if (WEXITSTATUS(status))
		exit(WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		exit(128 + WTERMSIG(status));
}


int	manage_execution(t_shell *shell, t_valist *env)// , char **cmds
{
	//ac = nb de cmds
	//(void) env;
	int i;
	i = 0;
	t_exec *cmd_list = shell->cmd_lst;
	t_exec *current = cmd_list;

	t_pipex pipex;

	if (cmd_list == NULL)
	{
	
		return (0); // pas de commande - liste vide
		printf("pas de commande");
	}

	else if (cmd_list->next == NULL && is_built_in(cmd_list->cmds[0]) != 0) // une seul commande et builtin
	{
		printf("built_in type = %d\n", is_built_in(cmd_list->cmds[0]));
		execute_built_in(is_built_in(cmd_list->cmds[0]));//, cmd_list->cmds); + PASSER ENV ? OU SHELL DIRECT
		
	}

	else // j'ai plrs commandes et des pipes (fork() les process)
	{
		while (current->next != NULL)
		{
			//ICI JE TROUVE LES BONNES REDIR POUR APPELER PIPEX

			pipex.cmd_left = current->cmds;
			pipex.cmd_right = current->next->cmds;

			pipex(&shell, env);
			
			//get_left_cmd();
			//get_right_cmd();
			
			//execute_cmd(cmd_list, env);

			
		}

	}
	return (0);
}







/* 		pipex cmd 0 / cmd 1
		pipex cmd 1 / cmd 2
		pipex cmd 2 / cmd 3 ............ + checker les redir !!!!! */

/* execve()
open()
read()
access()
close()
waitpid()
dup2()
pipe()
perror()
dup, opendir, readdir, closedir,
strerror */


/* void routine_child(redir, in, out)
{

}

void open_redir(t_exec cmd)
{

}

void execute_cmd(t_shell **shell)
{
	-je check les redir de la premiere commande, j,obtiens l,outfile / regarde in 
			-> une fois que j'ai in et out de la commande, je l,execute / lance le processus.
	-si pipe, je dirige cet output sur l,entree du pipe. / si pas de pipe, STDOUT
	-la sortie de ce pipe donne sur la commande suivante
	-je check les redirs de la commande suivante et ainsi de suite ...... 
			-> cas des heredocs ???
	
} */

/* pid_t	fork_child_one(char **av, int fd_pipe[2], char **envp, t_pipex *pipex)
{
	pid_t	child1;

	child1 = fork();
	if (child1 < 0)
		perror("fork: ");
	if (child1 == 0)
	{
		ft_free_tab(pipex->cmd2);
		routine_child_one(av, fd_pipe, pipex->cmd1, envp);
	}
	return (child1);
}

pid_t	fork_child_two(char **av, int fd_pipe[2], char **envp, t_pipex *pipex)
{
	pid_t	child2;

	child2 = fork();
	if (child2 < 0)
		perror("fork: ");
	if (child2 == 0)
	{
		ft_free_tab(pipex->cmd1);
		routine_child_two(av, fd_pipe, pipex->cmd2, envp);
	}
	return (child2);
}

void	routine_child_one(char **av, int fd_pipe[2], char **cmd1, char **envp)
{
	int		fd1;
	char	*my_cmd_path;

	fd1 = open(av[1], O_RDONLY);
	check_error_one(fd1, cmd1, av, fd_pipe);
	my_cmd_path = find_my_cmd_path(cmd1[0], envp);
	if (!my_cmd_path || my_cmd_path[0] == '\0')
	{
		ft_free_tab(cmd1);
		close(fd_pipe[1]);
		close(fd1);
		path_not_found();
	}
	dup2(fd1, STDIN_FILENO);
	dup2(fd_pipe[1], STDOUT_FILENO);
	close(fd_pipe[1]);
	close(fd1);
	execve(my_cmd_path, cmd1, envp);
	perror("execve");
	exit(1);
}

void	routine_child_two(char **av, int fd_pipe[2], char **cmd2, char **envp)
{
	int		fd2;
	char	*my_cmd_path;

	fd2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	check_error_two(fd2, cmd2, av, fd_pipe);
	my_cmd_path = find_my_cmd_path(cmd2[0], envp);
	if (!my_cmd_path || my_cmd_path[0] == '\0')
	{
		ft_free_tab(cmd2);
		close(fd_pipe[1]);
		close(fd2);
		path_not_found();
	}
	dup2(fd_pipe[0], STDIN_FILENO);
	dup2(fd2, STDOUT_FILENO);
	close(fd_pipe[0]);
	close(fd2);
	execve(my_cmd_path, cmd2, envp);
	perror("execve");
	exit(1);
}

void	pipex(char **av, t_valist *envp)
{
	t_pipex	pipex;

	int		fd_pipe[2];
	int		status;
	pid_t	child1;
	pid_t	child2;

	pipex.cmd1 = get_cmd_one(av);
	pipex.cmd2 = get_cmd_two(av, pipex.cmd1);
	if (pipe(fd_pipe) == -1)
		return (perror("pipe"));
	child1 = fork_child_one(av, fd_pipe, envp, &pipex);
	child2 = fork_child_two(av, fd_pipe, envp, &pipex);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
	ft_free_tab(pipex.cmd1);
	ft_free_tab(pipex.cmd2);
	if (WEXITSTATUS(status))
		exit(WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		exit(128 + WTERMSIG(status));
}

int	execution_cmd(t_shell *shell, t_valist *env, char **cmds)
{
	//ac = nd de cmds
	if (je n'ai qu'une seule cmd)
	{
		execute la cmd (built in / externe execve())
	}
	while (j'ai des commandes)
	{
		pipex cmd 0 / cmd 1
		pipex cmd 1 / cmd 2
		pipex cmd 2 / cmd 3 ............ + checker les redir !!!!!
	}

	pipex(cmds, env); // je transmet le tab de tab de commandes et liste env


	ft_putstr("\033[31minvalid arguments for pipex\n\033[0m");
	return (0);
} */