/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 03:24:49 by groubaud          #+#    #+#             */
/*   Updated: 2022/02/11 03:24:49 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"

void	child_process(int f1, char **paths, char **cmd_args, char *envp[])
{
	int		i;
	char	*tmp;
	char	*filename;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		filename = ft_strjoin(tmp, cmd_args[0]);
		free(tmp);
		if (!filename)
			exit(0) ; // on verra plus tard
		execve(filename, cmd_args, envp);
		free (filename);
		i++;
	}
	printf("command not found\n"); // a voir plus tard
}

// void    pipex(int f1, int f2, char **paths, char *cmd1, char *cmd2)
// {
// 	int   end[2];
// 	pid_t parent;
// 	char	*cmd_args1;

// 	cmd_args1 = ft_split(cmd, ' '); // faudra le changer pour tout ce qui est espace je pense
// 	if (!cmd_args1)
// 		exit ; // on verra plus tard

// 	pipe(end);
// 	parent = fork();
// 	if (parent < 0)
// 		return (perror("Fork: "));

// 	if (!parent) // if fork() returns 0, we are in the child process
// 		child_process(f1, paths, cmd1, cmd_args1);
// 	else
// 		parent_process(f2, cmd2);
// }

// je me demande si on peut faire une recherche de which au début
// comme ça si il y est, le path des commandes est rapide à trouver

char	*where_is_da_way(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0) //fonction systeme
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	**what_are_the_paths(char *envp[])
{
	char	*da_way;

	da_way = where_is_da_way(envp);
	if (da_way == NULL)
	{
		printf("Environnement variable PATH not found.\n");
		return (NULL);
	}
	return(ft_split(da_way, ':'));
}

int main(int ac, char **av, char *envp[])
{
	int	fd1;
	int	fd2;
	char	**paths;

	if (ac != 5)
		return (printf("Error: %s infile cm1 cm2 outfile\n %i\n", av[0], ac));
	fd1 = open(av[1], O_RDONLY);
	fd2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644); //trunc pour >; append pour >>

	paths = what_are_the_paths(envp);

	char	**cmd_args1;

	cmd_args1 = ft_split(av[2], ' '); // faudra le changer pour tout ce qui est espace je pense
	if (!cmd_args1)
		exit(1) ; // on verra plus tard (erreur toussa)

	child_process(fd1, paths, cmd_args1, envp);
	free(cmd_args1);

	//pipex(fd1, fd2, paths);
	
}