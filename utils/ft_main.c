/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 05:20:19 by groubaud          #+#    #+#             */
/*   Updated: 2022/07/29 12:47:01 by groubaud         ###   ########.fr       */
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
	add_history(input);
	if (parse(shell, input) == 1)
	{
		free(input);
		return (1);
	}
	free(input);
	if (shell->cmds->cmd && ft_check_syntax(shell) == CHECK_OK)
		ft_choose_the_exec(shell);
	ft_free_t_cmd(shell->cmds, shell->cmds_count);
	shell->cmds = NULL;
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

	(void)av;
	ft_init_mini(&shell, envp);
	while (ac > -1)
	{
		ft_attribute_signal(handle_ctrl_c, SIG_IGN);
		ft_launch_minishell(&shell);
	}
	return (0);
}
