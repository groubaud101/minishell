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

	// ft_puttab(cmd.args, "___");
	if (shell->cmds && cmd.args[1])
	{
		name_value = ft_split_once(cmd.args[1], '='); // check malloc
		// ft_puttab(name_value, "===");
		if (name_value[1])
			ft_export(shell, name_value[0], name_value[1]);
		else
			ft_export(shell, name_value[0], NULL);	
		//ft_free_tab(name_value);
		return (CHECK_OK);
	}
	return (ft_export(shell, NULL, NULL));
}

int	ft_exec_builtin(t_shell *shell, t_cmd cmd)
{
	if (!ft_strcmp(cmd.args[0], "echo"))
		ft_puttab(cmd.args + 1, " "); // tmp
	else if (!ft_strcmp(cmd.args[0], "cd"))
		ft_cd(shell, cmd.args[1]);
	else if (!ft_strcmp(cmd.args[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(cmd.args[0], "export"))
		ft_transi_export(shell, cmd);
	else if (!ft_strcmp(cmd.args[0], "unset"))
		ft_unset(shell, cmd);
	else if (!ft_strcmp(cmd.args[0], "env"))
		ft_env(shell->env);
	// else if (!ft_strcmp(cmd.args[0], "exit"))
	// 	ft_exit(shell);
	else
		return (CHECK_ERR);
	return (CHECK_OK);
}
