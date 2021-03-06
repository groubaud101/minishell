/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 21:03:56 by groubaud          #+#    #+#             */
/*   Updated: 2022/07/29 12:44:27 by groubaud         ###   ########.fr       */
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
		name_value = ft_split_once(cmd.args[i], '=');
		if (name_value == NULL)
			ft_exit_error(shell, errno);
		if (!name_value[0][0])
		{
			ft_printf_fd(STDERR, "bash: export: `=%s': not a valid "\
				"identifier\n", name_value[1]);
			return (1);
		}
		if (name_value[1])
			ft_export(shell, name_value[0], name_value[1]);
		else
			ft_export(shell, name_value[0], NULL);
		free(name_value);
		i++;
	}
	return (0);
}

int	ft_transi_exit(t_shell *shell, t_cmd cmd)
{
	printf("exit\n");
	if (cmd.args[1])
	{
		if (cmd.args[2])
		{
			ft_printf_fd(STDERR_FILENO, "bash: exit: too many arguments\n");
			return (1);
		}
		if (ft_str_isdigit(cmd.args[1]) == 1)
			shell->ret_value = ft_atoi_no_overflow(cmd.args[1]);
		else
		{
			ft_printf_fd(STDERR_FILENO, "bash: exit: %s: numeric argument"
				" required\n", cmd.args[1]);
			shell->ret_value = 255;
		}
	}
	ft_exit(shell);
	return (shell->ret_value);
}

int	ft_exec_builtin(t_shell *shell, t_cmd cmd)
{
	int	ret_value;

	ret_value = shell->ret_value;
	if (!ft_strcmp(cmd.args[0], "echo"))
		ret_value = ft_echo(shell, cmd.args + 1);
	else if (!ft_strcmp(cmd.args[0], "cd"))
		ret_value = ft_cd(shell, cmd.args[1]);
	else if (!ft_strcmp(cmd.args[0], "pwd"))
		ret_value = ft_pwd(shell);
	else if (!ft_strcmp(cmd.args[0], "export"))
		ret_value = ft_transi_export(shell, cmd);
	else if (!ft_strcmp(cmd.args[0], "unset"))
		ret_value = ft_unset(shell, cmd);
	else if (!ft_strcmp(cmd.args[0], "env"))
		ft_env(shell->env);
	else if (!ft_strcmp(cmd.args[0], "exit"))
		ret_value = ft_transi_exit(shell, cmd);
	else
		return (-19);
	return (ret_value);
}
