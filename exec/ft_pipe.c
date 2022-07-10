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
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		return (pid);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		return (pid);
	}
}

int	ft_pipe(t_shell *shell, t_cmd *cmds, int i)
{
	int		pid;

	pid = ft_kind_of_pipe();
	if (pid < 0)
		return (-1);
	if (pid != 0)
	{
		ft_exec(shell, cmds[i]);
	}
	else
	{
		if (i + 1 < shell->cmds_count - 1)
		{
			ft_pipe(shell, cmds, i + 1);
		}
		ft_exec(shell, cmds[i + 1]);
	}
	exit(1);
	return (1);
}