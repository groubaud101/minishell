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

typedef struct s_env
{
	char			*name;
	int				len_name;
	char			*value;
	struct s_env	*next;
}t_env;

typedef struct s_mini
{
	int		fd_in;
	int		fd_out;
	char	**paths;
	t_env	*env;
	bool	env_has_changed;
	char	**envp_tab;
}t_mini;


/* exec */
int		ft_redir_in(int *fd_in, char *infile);
int		ft_redir_out(int *fd_out, char *outfile);
int		ft_double_redir_in(int *fd_in, char *infile);
int		ft_double_redir_out(int *fd_out, char *outfile);
int		ft_pipe(char **cmds, t_mini *mini);

/* utils */
void	ft_init_mini(t_mini *mini, char **envp);
char	**ft_convert_env_list_to_tab(t_mini *mini);
void	ft_free_envp_tab(char **envp_tab);

/* builtins */
void	ft_aff_env(t_env *env);
char	*ft_getenv(char *name, t_env *env);

#endif