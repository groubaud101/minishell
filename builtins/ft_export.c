/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:55:20 by groubaud          #+#    #+#             */
/*   Updated: 2022/06/01 15:55:20 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_shell *shell, char *name, char *value)
{
	if (name == NULL && value)
	{
		printf("-%s: export: '=%s': not a valid identifier\n",
			shell->binary_name, value);
		return (1);
	}
	if (name == NULL && value == NULL)
		ft_display_export(shell->env);
	else
		return (ft_export_to_env(shell, name, value));
	return (0);
}