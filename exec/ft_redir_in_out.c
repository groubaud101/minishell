/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_in_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 10:59:12 by groubaud          #+#    #+#             */
/*   Updated: 2022/07/14 11:52:16 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_redir_in(t_shell *shell, t_cmd cmd)
{
	shell->fd_in = open(cmd.left.target, cmd.left.oflag, 644);
	shell->save_stdin = dup(STDIN_FILENO);
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
	shell->fd_out = open(cmd.right.target, cmd.right.oflag, 0644);
	shell->save_stdout = dup(STDOUT_FILENO);
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
		ret = ft_redir_in(shell, cmd);
	if (cmd.right.oflag != -1)
		ret = ft_redir_out(shell, cmd);
	return (ret);
}

int	ft_back_to_std(t_shell *shell, t_cmd cmd)
{
	if (cmd.left.oflag != -1
		&& dup2(shell->save_stdin, STDIN_FILENO) == -1)
		return (1);
	if (cmd.right.oflag != -1
		&& dup2(shell->save_stdout, STDOUT_FILENO) == -1)
		return (1);
	return (0);
}
