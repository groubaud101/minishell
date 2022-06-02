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

int	ft_export(t_mini *mini, char *name, char *value)
{
	if (value && name == NULL)
		return (printf("-%s: export: '=%s': not a valid identifier\n", mini->binary_name, value)); // erreur
	if (name == NULL && value == NULL)
		ft_display_export(mini->env);
	return (CHECK_OK);
}