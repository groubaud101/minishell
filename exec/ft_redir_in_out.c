/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_in_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 10:59:12 by groubaud          #+#    #+#             */
/*   Updated: 2022/07/11 19:48:48 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir(t_shell *shell, t_cmd cmd)
{
	int	fd;

	(void)shell;
	if (cmd.left.oflag != -1)
	{
		dprintf(STDERR_FILENO, COUCOU);
		fd = open(cmd.left.target, cmd.left.oflag);
		if (fd == -1)
		{
			ft_printf_fd(STDERR_FILENO, "bash: %s: Permission denied\n", cmd.left.target);
			return (-1);
		}
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			close(fd); // message d erreur
			return (-1);
		}
	}
	if (cmd.right.oflag != -1)
	{
		dprintf(STDERR_FILENO, COUCOU);
		fd = open(cmd.right.target, cmd.right.oflag);
		if (fd == -1)
		{
			ft_printf_fd(STDERR_FILENO, "bash: %s: Permission denied\n", cmd.right.target);
			return (-1);
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			close(fd); // message d erreur
			return (-1);
		}
	}
	return (fd);	
}

/*
** TODO
** It must be that in theory but I don't know how to test it
*/

int	ft_redir_in(t_shell *shell, char *infile)
{
	if (infile == NULL)
		shell->fd_in = STDIN;
	else
		shell->fd_in = open(infile, O_RDONLY);
	if (shell->fd_in == -1)
	{
		ft_printf_fd(STDERR_FILENO, "bash: %s: Permission denied\n", infile);
		return (1);
	}
	return (0);	
}

/*
** TODO
** it's the <<END thing
*/

int	ft_double_redir_in(t_shell *shell, char *infile)
{
	// a faire
	// <<EXPRESSION indique à une lecture sur l'entrée standard (?)
	//  de continuer jusqu'à EXPRESSION non incluse
	shell->fd_in = open(infile, O_RDONLY);
	if (shell->fd_in == -1)
	{
		ft_printf_fd(STDERR_FILENO, "bash: %s: Permission denied\n", infile);
		return (1);
	}
	return (0);	
}

/*
** TO TEST
** shell : the master structure
** outfile : the path of the output file
**
** Attribute the 'fd_out' to the outfile called by '>'
**  create a new if not exist
**  give  write privileges
**  will replace content
*/

int	ft_redir_out(t_shell *shell, char *outfile)
{
	shell->fd_out = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (shell->fd_out == -1)
	{
		ft_printf_fd(STDERR_FILENO, "bash: %s: Permission denied\n", outfile);
		return (1);
	}
	return (0);	
}

/*
** TO TEST
** shell : the master structure
** outfile : the path of the output file
**
** Attribute the 'fd_out' to the outfile called by '>>'
**  create a new if not exist
**  give write privilege
**  will append new content
*/

int	ft_double_redir_out(t_shell *shell, char *outfile)
{
	shell->fd_out = open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (shell->fd_out == -1)
	{
		printf("could not open the outfile blah blah blah\n");
		ft_printf_fd(STDERR_FILENO, "bash: %s: Permission denied\n", outfile);
		return (1);
	}
	return (0);	
}
