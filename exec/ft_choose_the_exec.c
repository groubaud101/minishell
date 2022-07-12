/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_choose_the_exec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:15:50 by groubaud          #+#    #+#             */
/*   Updated: 2022/07/12 19:13:02 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	exec_other(t_shell *shell, int i, char *path)
// {
// 	int	fd;
// 	int pid;

// 	if (!path)
// 		return (0);
// 	pid = fork();
// 	if (pid == -1)
// 		return (0);
// 	if (pid == 0)
// 	{
// 		if (shell->cmds[i].left.target)
// 		{
// 			fd = open(shell->cmds[i].left.target, shell->cmds[i].left.oflag);
// 			if (fd == -1)
// 				return (0);
// 			if (dup2(fd, STDIN_FILENO) == -1)
// 			{
// 				close(fd);
// 				return (0);
// 			}
// 		}
// 		if (shell->cmds[i].right.target)
// 		{
// 			fd = open(shell->cmds[i].right.target, shell->cmds[i].right.oflag);
// 			if (fd == -1)
// 				return (0);
// 			if (dup2(fd, STDOUT_FILENO) == -1)
// 			{
// 				close(fd);
// 				return (0);
// 			}
// 		}
// 		close(fd);
// 		execve(path, shell->cmds[i].args, shell->envp_tab);
// 	}
// 	wait(NULL);
// 	free(path);
// 	return (1);
// }

void	ft_close(t_shell *shell)
{
	dup2(shell->fd_in, STDIN_FILENO);
	dup2(shell->fd_out, STDOUT_FILENO);
	if (shell->fd_in > 0)
		close(shell->fd_in);
	if (shell->fd_out > 1)
		close(shell->fd_out);
	shell->fd_in = STDIN_FILENO;
	shell->fd_out = STDOUT_FILENO;
}

int	ft_choose_the_exec(t_shell *shell)
{
	ft_attribute_signal(SIG_IGN, SIG_IGN);
	ft_convert_env_list_to_tab(shell);
	if (shell->cmds_count == 1)
		shell->ret_value = ft_exec_builtin(shell, shell->cmds[0]);
	if (shell->ret_value == -19 || shell->cmds_count > 1)
		shell->ret_value = ft_pipe(shell, 0);
	if (shell->ret_value == 11)
		ft_printf_fd(STDERR_FILENO, "Segmentation fault: 11\n");
	else if (shell->ret_value == 10)
		ft_printf_fd(STDERR_FILENO, "Bus error: 10\n");
	ft_close(shell);
	return (1);
}
