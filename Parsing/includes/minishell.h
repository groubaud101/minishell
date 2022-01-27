/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:38:48 by jrobert           #+#    #+#             */
/*   Updated: 2022/01/27 21:49:48 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_cmd
{
	char		*cmd;
	char		**argv;
	char		*redirection;
}				t_cmd;

typedef struct s_shell
{
	char		*input;
	char		**words;
	int			exit_status;
	int			cmds_count;
	t_cmd		*cmds;
}				t_shell;

int		fail(char *err);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		parse(t_shell *shell);

#endif
