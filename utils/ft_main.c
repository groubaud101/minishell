/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 05:20:19 by groubaud          #+#    #+#             */
/*   Updated: 2022/05/07 05:20:19 by groubaud         ###   ########.fr       */
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

// /*
// ** ac/av/envp : number of arg / tab of arg / tab of the environnement
// **
// ** Initialize the master structure mini
// */

// int main(int ac, char **av, char *envp[])
// {
// 	t_mini	mini;

// 	ft_init_mini(&mini, av, envp);
// 	ft_env(mini.env);
// 	ft_printf("\nnew env :\n");
// 	if (ac > 1)
// 	// 	ft_pipe(av + 1, &mini);
// 		// ft_cd(&mini, av[1]);
// 		if (ac > 2)
// 			ft_export_to_env(&mini, av[1], av[2]);
// 	ft_env(mini.env);
// 	ft_display_export(mini.env);
// 	// ft_printf("\n\nThis is the end, hold your breath and count to ten\n");
// }