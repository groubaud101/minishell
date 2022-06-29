/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 04:46:05 by groubaud          #+#    #+#             */
/*   Updated: 2022/06/27 11:39:24 by jrobert          ###   ########.fr       */
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
# include <stdint.h>
# include <errno.h>
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"

# define CHECK_OK 0
# define CHECK_ERR -1
# define TO_EXIT 1
# define NO_EXIT 0

# define ECHO 1
# define CD 2
# define PWD 3
# define EXPORT 4
# define UNSET 5
# define ENV 6
# define EXIT 7

# define STDIN STDIN_FILENO
# define STDOUT STDOUT_FILENO
# define STDERR STDERR_FILENO

# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>

typedef struct s_spec
{
	char	*spec;
	int		size;
	char	*type;
}				t_spec;

typedef struct s_token
{
	char			*content;
	int				size;
	char			*type;
	struct s_token	*next;
}				t_token;

typedef struct s_chevron
{
	char	*target;
	int		oflag;
	char	*heredoc;
}				t_chevron;

typedef struct s_cmd
{
	char		*cmd;
	char		**args;
	int			argc;
	t_chevron	left;
	t_chevron	right;
}				t_cmd;

typedef struct s_env
{
	char			*name;
	int				len_name;
	char			*value;
	struct s_env	*next;
}t_env;

typedef struct s_bash
{
	char			*name;
	int				len_name;
	char			*value;
	struct s_bash	*next;
}t_bash;

typedef struct s_shell
{
	int		exit_status;
	int		cmds_count;
	t_cmd	*cmds;
	char	*binary_name;
	int		fd_in;
	int		fd_out;
	char	**paths;
	t_env	*env;
	bool	env_has_changed;
	t_bash	*var_bash;
	char	**envp_tab;
}t_shell;

/* exec */
int		ft_redir_in(t_shell *shell, char *infile);
int		ft_redir_out(t_shell *shell, char *outfile);
int		ft_double_redir_in(t_shell *shell, char *infile);
int		ft_double_redir_out(t_shell *shell, char *outfile);
int		ft_exec_process(t_shell *shell, t_cmd cmd, bool to_exit);
int		ft_pipe(t_cmd *cmds, t_shell *shell);

/* utils */
void	ft_init_mini(t_shell *shell, char **av, char **envp);
char	**ft_split_once(char *str, char c);
char	**ft_convert_env_list_to_tab(t_shell *shell);

/* builtins */
int		ft_exec_builtin(t_shell *shell, t_cmd cmd);
void	ft_env(t_env *env);
t_env	*ft_getenv(char *name, t_env *env);
int		ft_cd(t_shell *shell, char *path);
char	*ft_getcwd(void);
int		ft_pwd(void);
int		ft_export_to_env(t_shell *shell, char *name, char *value);
void	ft_display_export(t_env *env);
int		ft_export(t_shell *shell, char *name, char *value);
int		ft_unset(t_shell *shell, t_cmd cmd);

/* parsing */
int		fail(char *err);
int		free_all(t_token **head);
void	clear_tknlst(t_token **head, void (*del)(void *));
int		copy_envp(t_shell *shell, char **envp);
int		parse(t_shell *shell, char *input);
int		free_mallocs(t_shell *shell, int i);
int		is_builtin(char *cmd);
char	*get_path(char *cmd);

/* transition */
int	ft_choose_the_exec(t_shell *shell);

#endif