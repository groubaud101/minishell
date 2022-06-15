/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 21:59:39 by groubaud          #+#    #+#             */
/*   Updated: 2022/06/15 21:59:39 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	char	*input;
	t_mini	mini;

	ft_init_mini(&mini, av, envp);
	(void)ac;
	shell = (t_shell){0};
	if (!copy_envp(&shell, envp))
		return (fail("Error - Malloc Envp"));
	while (1)
	{
		input = readline("\033[1;32mMiniShell >> \033[0m");
		add_history(input);
		if (!ft_strncmp(input, "exit", 4))
			break ;
		if (parse(&shell, input))
			ft_choose_the_exec(&shell, &mini);
	}
	free_mallocs(&shell, shell.cmds_count);
	return (0);
}