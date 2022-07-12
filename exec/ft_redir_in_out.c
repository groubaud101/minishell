/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_in_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 10:59:12 by groubaud          #+#    #+#             */
/*   Updated: 2022/07/12 20:02:23 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_redir_in(t_shell *shell, t_cmd cmd)
{
	shell->fd_in = open(cmd.left.target, cmd.left.oflag);
	if (shell->fd_in == -1)
	{
		ft_printf_fd(STDERR_FILENO, "bash: %s: Permission denied\n",
			cmd.left.target);
		return (1);
	}
	if (dup2(shell->fd_in, STDIN_FILENO) == -1)
	{
		perror("bash: dup2: ");
		if (close(shell->fd_in) == -1)
			perror("bash: close: ");
		return (1);
	}
	return (0);
}

static int	ft_redir_out(t_shell *shell, t_cmd cmd)
{
	shell->fd_out = open(cmd.right.target, cmd.right.oflag);
	if (shell->fd_out == -1)
	{
		ft_printf_fd(STDERR_FILENO, "bash: %s: Permission denied\n",
			cmd.right.target);
		return (1);
	}
	if (dup2(shell->fd_out, STDOUT_FILENO) == -1)
	{
		perror("bash: dup2: ");
		if (close(shell->fd_out) == -1)
			perror("bash: close: ");
		return (1);
	}
	return (0);
}

int	ft_redir(t_shell *shell, t_cmd cmd)
{
	int	ret;

	ret = 0;
	if (cmd.left.oflag != -1)
	{
		if (ft_redir_in(shell, cmd) == 1)
			ret = 1;
	}
	if (cmd.right.oflag != -1)
	{
		if (ft_redir_out(shell, cmd) == -1)
			ret = 1;
	}
	return (ret);
}
