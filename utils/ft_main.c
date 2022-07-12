/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 05:20:19 by groubaud          #+#    #+#             */
/*   Updated: 2022/07/12 11:42:35 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** shell : the master structure
**
** Display the prompt and read the input
** Parse and fill the shell structure with token
** If there is cmd, add it to the history
**  and launch the execution of the command
** Free t_cmd
*/

int	ft_launch_minishell(t_shell *shell)
{
	char	*input;

	input = readline("\001\033[1;32m\002MiniShell >> \001\033[0m\002");
	// input = readline("G ");
	// If EOF is encountered while reading a line,
	//   and the line is empty, NULL is returned.
	if (!input)
	{
		printf("exit\n");
		ft_exit(shell);
	}
	if (input[0] == '\0')
	{
		free(input);
		return (0);
	}
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
** Launch minishell in a infinite loop
*/

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	ft_init_mini(&shell, av, envp);
	// sig_catch = -1;
	ft_init_signal();
	(void)ac;
	while (1)
	{
		ft_launch_minishell(&shell);
	}
	return (0);
}
