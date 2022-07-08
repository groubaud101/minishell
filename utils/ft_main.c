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

static volatile int sig_catch;

void	signal_handler(int signum)
{
	sig_catch = signum;
	if (signum == SIGINT)
		ft_printf_fd(STDOUT, "\n");
		// ft_printf_fd(STDIN, "\b\b  \n");// à voir si on garde ^C
}

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

	input = readline("\033[1;32mMiniShell >> \033[0m");
	// If EOF is encountered while reading a line,
	//   and the line is empty, NULL is returned.
	if (!input)
		ft_exit(shell, 1);

	// A voir si il faut free 'input'
	ft_printf_fd(1, "input : |%s|\n", input);
	if (input[0] == '\0')
	{
		ft_printf_fd(1, "read 0\n");
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

	(void)ac;
	while (1)
	{
		ft_launch_minishell(&shell);
	}
	return (0);
}
