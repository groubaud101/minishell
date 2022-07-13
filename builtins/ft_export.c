/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:55:20 by groubaud          #+#    #+#             */
/*   Updated: 2022/07/14 01:20:05 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_shell *shell, char *name, char *value)
{
	if (name == NULL && value)
	{
		ft_printf_fd(STDERR_FILENO, "bash: export: '=%s': "\
			"not a valid identifier\n", value);
		return (1);
	}
	if (name == NULL && value == NULL)
		ft_display_export(shell->env);
	else
		return (ft_export_to_env(shell, name, value));
	return (0);
}
