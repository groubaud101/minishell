/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 21:03:56 by groubaud          #+#    #+#             */
/*   Updated: 2022/06/27 21:03:56 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_transi_export(t_shell *shell, t_cmd cmd)
{
	char	**name_value;
	int		i;

	i = 1;
	if (cmd.args[1] == NULL)
		ft_export(shell, NULL, NULL);
	while (cmd.args[i])
	{
		// ft_puttab(cmd.args, "___");
		name_value = ft_split_once(cmd.args[i], '='); // check malloc
		if (name_value == NULL)
			ft_exit(shell, 1);
		// ft_puttab(name_value, "===");
		if (name_value[1])
			ft_export(shell, name_value[0], name_value[1]);
		else
			ft_export(shell, name_value[0], NULL);
		free(name_value);
		i++;
	}
	return (0);
}

int	ft_exec_builtin(t_shell *shell, t_cmd cmd)
{
	int	ret_value;

	ret_value = 0;
	if (!ft_strcmp(cmd.args[0], "echo"))
		ret_value = ft_echo(cmd.args + 1);
	else if (!ft_strcmp(cmd.args[0], "cd"))
		ret_value = ft_cd(shell, cmd.args[1]);
	else if (!ft_strcmp(cmd.args[0], "pwd"))
		ret_value = ft_pwd();
	else if (!ft_strcmp(cmd.args[0], "export"))
		ret_value = ft_transi_export(shell, cmd);
	else if (!ft_strcmp(cmd.args[0], "unset"))
		ret_value = ft_unset(shell, cmd);
	else if (!ft_strcmp(cmd.args[0], "env"))
		ft_env(shell->env);
	else if (!ft_strcmp(cmd.args[0], "exit"))
		ft_exit(shell, 1);
	else
		return (-1);
	// printf(COUCOU);
	return (ret_value);
}
