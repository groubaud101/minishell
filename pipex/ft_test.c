/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 03:24:49 by groubaud          #+#    #+#             */
/*   Updated: 2022/02/11 03:24:49 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_set_cmd1_cmd2(char ***cmd1, char ***cmd2, char **av)
{
	*cmd1 = ft_split(av[2], ' ');
	if (!(*cmd1))
		return (-1);
	*cmd2 = ft_split(av[3], ' ');
	if (!(*cmd2))
		return (-1);
	return (CHECK_OK);	
}

int main(int ac, char **av, char *envp[])
{
	t_minishell	mini;

	if (ac != 5)
		return (printf("Error: %s infile cm1 cm2 outfile\n %i\n", av[0], ac));

	if (ft_redir_in(&mini.fd_in, av[1]) == CHECK_ERR) //&fd_in sera remplacé par la variable de la structure
		return (1);
	if (ft_redir_out(&mini.fd_out, av[4]) == CHECK_ERR)
		return (1);

	char	**cmd_args1;
	char	**cmd_args2;

	ft_set_cmd1_cmd2(&cmd_args1, &cmd_args2, av); // provisoire

	mini.paths = what_are_the_paths(envp);
	if (mini.paths == NULL)
		return (1); // a voir

	ft_pipe(mini, cmd_args1, cmd_args2, envp);
	free(cmd_args1);
	free(cmd_args2);
}