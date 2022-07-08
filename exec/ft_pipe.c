/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 16:17:03 by groubaud          #+#    #+#             */
/*   Updated: 2022/07/08 16:17:03 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_kind_of_pipe(void)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid == 0) // fils
	{
		close(pipefd[1]); // close la sortie
		dup2(pipefd[0], STDIN_FILENO); // redirige l'entrée std sur l'entrée du tuyau
		return (pid);
	}
	else // père
	{
		close(pipefd[0]); // close l'entrée
		dup2(pipefd[1], STDOUT_FILENO); // redirige la sortie std sur la sortie du tuyau
		return (pid);
	}
}

int	ft_pipe(t_shell *shell, t_cmd *cmds, int i)
{
	int		pid;

	// dprintf(2, "coucou\n");
	pid = ft_kind_of_pipe();
	if (pid != 0) // process père
	{
		ft_exec(shell, cmds[i]);
	}
	else if (i + 1 < shell->cmds_count)
	{
		if (i + 2 < shell->cmds_count)
			ft_pipe(shell, cmds, i + 1);
		ft_exec(shell, cmds[i + 1]);
	}
	else
		waitpid(pid, NULL, 0);
	exit (1);
	return (1);
}