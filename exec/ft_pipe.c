/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:08:40 by groubaud          #+#    #+#             */
/*   Updated: 2022/07/11 19:24:43 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_wif_ret(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	else if (WIFSTOPPED(status))
		return (WSTOPSIG(status));
	else
		return (1);
}

int	ft_pipe(t_shell *shell, t_cmd *cmds, int i)
{
	int fd[2];
	int fd_save;
	int status;
	int	pid;

	i = 0;
	while (i < shell->cmds_count)
	{
		if (i < shell->cmds_count - 1)
		{
			pipe(fd);
		}
		pid = fork();
		if (pid == 0)
		{
			if (i > 0)
				dup2(fd_save, STDIN_FILENO);
			if (i < shell->cmds_count - 1)
			{
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
			}
			ft_exec(shell, cmds[i]);
		}
		if (i > 0)
			close(fd_save);
		if (i < shell->cmds_count - 1)
		{
			close(fd[1]);
			fd_save = fd[0];
		}
		i++;
	}
	ft_sleep(50000);
	waitpid(pid, &status, 0);
	return (ft_wif_ret(status));
}