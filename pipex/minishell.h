/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 04:46:05 by groubaud          #+#    #+#             */
/*   Updated: 2022/02/16 04:46:05 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdbool.h>
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"

# define CHECK_OK 0
# define CHECK_ERR -1
# define TO_EXIT 1
# define NO_EXIT 0

# define STDIN STDIN_FILENO
# define STDOUT STDOUT_FILENO
# define STDERR STDERR_FILENO

typedef struct s_mini
{
	int		fd_in;
	int		fd_out;
	char	**paths;
	char	**envp;
	bool	envp_has_changed;

}t_mini;


int		ft_redir_in(int *fd_in, char *infile);
int		ft_redir_out(int *fd_out, char *outfile);
int		ft_double_redir_in(int *fd_in, char *infile);
int		ft_double_redir_out(int *fd_out, char *outfile);
int		ft_pipe(char **cmds, t_mini *mini);

#endif