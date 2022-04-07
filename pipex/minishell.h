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

# include "libft.h"
# include "ft_printf.h"

# define CHECK_OK 0
# define CHECK_ERR -1

# define STDIN STDIN_FILENO
# define STDOUT STDOUT_FILENO
# define STDERR STDERR_FILENO

typedef struct s_minishell
{
	int		in;
	int		out;
	int		fd_in;
	int		fd_out;
	int		end0;
	int		end1;
	int		nb_pipe;
	char	**paths;
}t_minishell;


char	*where_is_da_way(char *envp[]);
char	**what_are_the_paths(char *envp[]);

int		ft_set_cmd1_cmd2(char ***cmd1, char ***cmd2, char **av);

char	**ft_split_add_c(char const *s, char sep, char c);

int		ft_redir_in(int *fd_in, char *infile);
int		ft_redir_out(int *fd_out, char *outfile);
int		ft_double_redir_in(int *fd_in, char *infile);
int		ft_double_redir_out(int *fd_out, char *outfile);

void	child_process(char **paths, char **cmd_args, char *envp[]);
pid_t	ft_child(t_minishell mini, int end[2], char **cmd, char *envp[]);

pid_t	ft_pipe(t_minishell *mini);

int	ft_exec(t_minishell *mini, char **cmd, char *envp[]);

#endif