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

int	ft_launch_minishell(t_shell *shell)
{
	char	*input;

	// faudra un fork, le to_exit de execve sera toujours true
	// les builtin auront un exit à la fin avec ret_value
	input = readline("\033[1;32mMiniShell >> \033[0m");
	// If EOF is encountered while reading a line,
	//   and the line is empty, NULL is returned.
	if (!input)
		ft_exit(shell, 0);

	// A voir si il faut free 'input'
	if (input[0] == '\0')
		return (0);
	parse(shell, input);
	if (shell->cmds->cmd)
	{
		add_history(input);
		ft_choose_the_exec(shell);
	}
	ft_free_t_cmd(shell->cmds, shell->cmds_count);
	return (0);
}

/*
** ac/av/envp : number of arg / tab of arg / tab of the environnement
**
** Initialize the master structure shell
** Launch minishell in a infinite loupe
*/

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	ft_init_mini(&shell, av, envp);
	(void)ac;
	while (1)
	{
		ft_launch_minishell(&shell);
	}
	return (0);
}

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