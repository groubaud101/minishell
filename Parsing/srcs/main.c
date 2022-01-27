/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:48:31 by jrobert           #+#    #+#             */
/*   Updated: 2022/01/27 21:45:18 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_cmd(char *word)
{
	if (ft_strncmp(word, "echo", 0)
		|| ft_strncmp(word, "cd", 0)
		|| ft_strncmp(word, "pwd", 0)
		|| ft_strncmp(word, "export", 0)
		|| ft_strncmp(word, "unset", 0)
		|| ft_strncmp(word, "env", 0)
		|| ft_strncmp(word, "exit", 0))
		return (1);
	else
		return (0);
}

int	parse(t_shell *shell)
{
	int		n;

	shell->words = ft_split(shell->input, ' ');
	if (is_cmd(shell->words[0]))
	{
		n = 0;
		while (shell->words[n])
			n++;
		shell->cmds = (t_cmd *)malloc(sizeof(t_cmd) * n);
		if (!shell->cmds)
			return (0);
		shell->cmds[0].cmd = shell->words[0];
		n = 1;
		while (shell->words[n])
		{
			n++; 
		}
	}
		
	
	return (1);
}

int	main(void)
{
	t_shell	shell;

	shell = (t_shell){0};
	shell.input = "";
	while (ft_strncmp(shell.input, "exit", 4) != 0)
	{
		shell.input = readline("\033[1;32m>> \033[0m");
		add_history(shell.input);
		if (!parse(&shell))
			return (fail("Parsing error"));
	}
	free(shell.input);
	free(shell.words);
	system("leaks minishell");
	return (0);
}
