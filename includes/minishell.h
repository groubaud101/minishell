/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 04:46:05 by groubaud          #+#    #+#             */
/*   Updated: 2022/07/14 11:52:49 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <sys/wait.h>
# include <stdint.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"

# define CHECK_OK 0
# define CHECK_ERR -1

# define STDIN STDIN_FILENO
# define STDOUT STDOUT_FILENO
# define STDERR STDERR_FILENO

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
}				t_env;

typedef struct s_shell
{
	int		cmds_count;
	t_cmd	*cmds;
	char	**paths;
	t_env	*env;
	int		env_has_changed;
	char	**envp_tab;
	int		fd_in;
	int		fd_out;
	int		save_stdin;
	int		save_stdout;
	int		ret_value;
}				t_shell;

/* exec */
int		ft_pipe(t_shell *shell, int i);
int		ft_exec(t_shell *shell, t_cmd cmd);
int		ft_execve(char **cmd, char **paths, char *envp[]);
int		ft_choose_the_exec(t_shell *shell);
int		ft_back_to_std(t_shell *shell, t_cmd cmd);
int		ft_redir(t_shell *shell, t_cmd cmd);

/* utils */
void	ft_init_mini(t_shell *shell, char **envp);
char	**ft_split_once(char *str, char c);
char	**ft_convert_env_list_to_tab(t_shell *shell);
int		ft_check_syntax(t_shell *shell);
void	ft_exit_error(t_shell *shell, int ret_value);

void	handle_ctrl_c(int sig);
void	ft_attribute_signal(void (*sig_int)(int), void (*sig_quit)(int));

/* builtins */
int		ft_exec_builtin(t_shell *shell, t_cmd cmd);

int		ft_cd(t_shell *shell, char *path);

char	*ft_getcwd(t_shell *shell);
int		ft_pwd(t_shell *shell);

void	ft_env(t_env *env);
t_env	*ft_getenv(char *name, t_env *env);

int		ft_export_to_env(t_shell *shell, char *name, char *value);
void	ft_display_export(t_env *env);
int		ft_export(t_shell *shell, char *name, char *value);

int		ft_unset(t_shell *shell, t_cmd cmd);

void	ft_free_t_cmd(t_cmd *cmds, int nb_cmds);
void	ft_free_t_env(t_env *env);
void	ft_exit(t_shell *shell);
int		ft_echo(t_shell *shell, char **next_args);

/* parsing */
char	*get_var(t_shell *shell, char **str, char **bef, int *j);
char	**init_vars(char *str, char **bef, int *i);
int		replace_var(t_shell *shell, char *str, char **bef);
int		replace(t_shell *shell, char **vars, int i, char **bef);
int		replace_env_var(t_shell *shell, t_token **head);

int		count_cmds(t_token *tkn);
int		count_args(t_token *tkn);
void	init_cmd(t_shell *shell, int i, int n);
int		init_parser(t_shell *shell, t_token *tkn);

int		parse(t_shell *shell, char *input);
int		odd_quote_bef(char **strs, int i, char c);
int		odd_quote_aft(char **strs, int i, char c);

void	cpy_in_quotes(char *content, int *i, int *j, char *new);
int		len_wo_quotes(char *str);
int		remove_quotes(t_token **head);
int		valid_quotes(char *input);
void	handle_quotes(char **input, int *i);

int		trim_tkn(t_token **tkn);
int		save_chev_l(t_shell *shell, t_token **tkn, int i);
int		save_chev_r(t_shell *shell, t_token **tkn, int i);
int		save_chev_rr(t_shell *shell, t_token **tkn, int i);

int		save_arg(t_shell *shell, t_token **tkn, int i, int *j);
int		end_save(t_shell *shell, t_token **tkn, int i, int j);
int		save_cmds(t_shell *shell, t_token *tkn);

t_spec	find_spec(char *s);
void	tkn_add_back(t_token **alst, t_token *new);
t_token	*new_tkn(char *content, int size, char *type);
void	handle_input(t_token **head, char **input, int *i);
int		tokenize(t_shell *shell, char *input, t_token **head);

void	clear_tknlst(t_token **head, void (*del)(void *));
int		free_all(t_token **head);
int		fail(char *err);
char	*ft_strjoin_free(char *s1, char *s2);

#endif