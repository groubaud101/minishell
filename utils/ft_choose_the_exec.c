/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_choose_the_exec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:15:50 by groubaud          #+#    #+#             */
/*   Updated: 2022/07/12 15:47:46 by groubaud         ###   ########.fr       */
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

// int	exec(t_shell *shell)
// sera remplacé par l'appel à ft_pipe, c'est dans ft_pipe qu'on fera le tri

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
	// signal(SIGQUIT, SIG_IGN);
	// signal(SIGINT, SIG_IGN);
	ft_attribute_signal(SIG_IGN, SIG_IGN);
	ft_convert_env_list_to_tab(shell);
	if (shell->cmds_count == 1)
	{
		// if (!ft_redir(shell, shell->cmds[0]))
			shell->ret_value = ft_exec_builtin(shell, shell->cmds[0]);
		// ft_close(shell);
	}
	if (shell->ret_value == -19 || shell->cmds_count > 1)
		shell->ret_value = ft_pipe(shell, shell->cmds, 0);
	ft_close(shell);
	// dprintf(2, COUCOU);
	return (1);
}