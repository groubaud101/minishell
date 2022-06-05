/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:38:48 by jrobert           #+#    #+#             */
/*   Updated: 2022/04/11 15:18:40 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
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

typedef struct s_shell
{
	char		**envp;
	int			exit_status;
	int			cmds_count;
	t_cmd		*cmds;
}				t_shell;

int		fail(char *err);
int		free_all(t_token **head);
void	clear_tknlst(t_token **head, void (*del)(void *));
int		bi_export(t_shell *shell, int i);
int		bi_echo(t_shell *shell, int i);
int		bi_env(t_shell *shell);

#endif
