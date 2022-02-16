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
#include "minishell.h"

void	child_process(char **paths, char **cmd_args, char *envp[])
{
	int		i;
	char	*tmp;
	char	*filename;

	i = 0;
	if (access(cmd_args[0], F_OK | X_OK) == 0) // si chemin absolu donné, checker les erreurs (si existe pas)
		execve(cmd_args[0], cmd_args, envp);
	// perror("execve : ");
	while (paths[i])
	{
		filename = ft_strjoin(paths[i], cmd_args[0]);
		if (!filename)
			exit(0) ; // on verra plus tard
		if (access(filename, F_OK | X_OK) == 0)
			execve(filename, cmd_args, envp);
		//perror("execve ");
		free(filename);
		i++;
	}
	printf("%s command not found\n", cmd_args[0]); // a voir plus tard
}

void	child_process2(char **paths, char **cmd_args, char *envp[])
{
	int		i;
	char	*tmp;
	char	*filename;

	i = 0;
	if (access(cmd_args[0], F_OK | X_OK) == 0) // si chemin absolu donné, checker les erreurs (si existe pas)
		execve(cmd_args[0], cmd_args, envp);
	// perror("execve : ");
	while (paths[i])
	{
		filename = ft_strjoin(paths[i], cmd_args[0]);
		if (!filename)
			exit(0) ; // on verra plus tard
		if (access(filename, F_OK | X_OK) == 0)
			execve(filename, cmd_args, envp);
		//perror("execve ");
		free(filename);
		i++;
	}
	printf("%s command not found\n", cmd_args[0]); // a voir plus tard
}

void    pipex(int fd_in, int fd_out, char **cmd1, char **cmd2, char *envp[])
{
	int   	end[2];
	pid_t	child1;
	pid_t	child2;
	int		status;
	char	**paths;

	paths = what_are_the_paths(envp);
	if (paths == NULL)
		return ; // a voir
		
	if (pipe(end) == -1)
		return (perror("pipe"));

	child1 = fork();
	if (child1 < 0)
		return (perror("Fork: "));
	if (child1 == 0) // if fork() returns 0, we are in the child process
	{
		dup2(end[1], 1);
		close(end[0]);
		dup2(fd_in, 0);
		child_process(paths, cmd1, envp);

	}
	child2 = fork();
	if (child2 < 0)
		return (perror("Fork: "));
	if (child2 == 0)
	{
		dup2(end[0], 0);
		close(end[1]);
		dup2(fd_out, 1);	
		child_process(paths, cmd2, envp);
	}

	close(end[0]);
	close(end[1]);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
}

int main(int ac, char **av, char *envp[])
{
	char	**paths;
	int	fd1;
	int	fd2;

	if (ac != 5)
		return (printf("Error: %s infile cm1 cm2 outfile\n %i\n", av[0], ac));
	fd1 = open(av[1], O_RDONLY);
	if (fd1)
	fd2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644); //trunc pour >; append pour >>
	// voir pour un fichier qui existe mais dont on a pas les droits

	char	**cmd_args1;
	char	**cmd_args2;

	ft_set_cmd1_cmd2(&cmd_args1, &cmd_args2, av); // provisoire

	pipex(fd1, fd2, cmd_args1, cmd_args2, envp);

	//child_process(fd1, paths, cmd_args1, envp);
	free(cmd_args1);
	free(cmd_args2);

}