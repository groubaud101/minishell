/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 06:06:54 by groubaud          #+#    #+#             */
/*   Updated: 2022/03/24 06:06:54 by groubaud         ###   ########.fr       */
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

	//perror("execve : ");
	while (paths[i])
	{
		filename = ft_strjoin(paths[i], cmd_args[0]);
		if (!filename)
			exit(0) ; // on verra plus tard
		if (access(filename, F_OK | X_OK) == 0)
			execve(filename, cmd_args, envp);
		// perror("execve ");
		free(filename);
		i++;
	}
}

int	ft_exec(t_minishell* mini, char **cmd, char *envp[])
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		printf("pid = 0\n");
		child_process(mini->paths, cmd, envp);
	}
	else
	{
		printf("pid = %i\n", pid);
		waitpid(pid, &status, 0);
	}
	close(mini->end0);
	close(mini->end1);
	return (1);
}
