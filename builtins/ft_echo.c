/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 09:05:51 by groubaud          #+#    #+#             */
/*   Updated: 2022/06/30 09:05:51 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_puttab_echo(char **tab)
{
	int		index;

	index = 0;
	if (!tab)
		return (1);
	while (tab[index])
	{
		if (write(1, tab[index], ft_strlen(tab[index])) < 0)
			return (1);
		index++;
		if (tab[index])
			if (write(1, " ", 1) < 0)
				return (1);
	}
	return (0);
}

int	ft_echo(char **next_args)
{
	int	ret_value;

	if (next_args[0] && ft_strcmp(next_args[0], "-n") == 0)
		ret_value = ft_puttab_echo(next_args + 1);
	else
	{
		ret_value = ft_puttab_echo(next_args);
		if (write(1, "\n", 1) < 0)
			return (1);
	}
	return (ret_value);
}
