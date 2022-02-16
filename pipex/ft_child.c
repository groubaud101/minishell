/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:38:21 by groubaud          #+#    #+#             */
/*   Updated: 2022/02/16 11:38:21 by groubaud         ###   ########.fr       */
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

pid_t	ft_child1(t_minishell mini, int end[2], char **cmd, char *envp[])
{
	pid_t	child1;

	child1 = fork();
	if (child1 < 0)
		perror("fork: ");
	else if (child1 == 0)
	{
		dup2(end[1], 1);
		close(end[0]);
		dup2(mini.fd_in, 0);
		child_process(mini.paths, cmd, envp);
	}
	return (child1);
}

pid_t	ft_child2(t_minishell mini, int end[2], char **cmd, char *envp[])
{
	pid_t	child2;

	child2 = fork();
	if (child2 < 0)
		perror("fork: ");
	else if (child2 == 0)
	{
		dup2(end[0], 0);
		close(end[1]);
		dup2(mini.fd_out, 1);
		child_process(mini.paths, cmd, envp);
	}
	return (child2);
}
