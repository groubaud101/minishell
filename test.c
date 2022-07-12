/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:37:55 by groubaud          #+#    #+#             */
/*   Updated: 2022/07/12 17:54:26 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"

void	ft_bus_error()
{
	char *str = "coucou";

	str[0] = 'a';
}

void	ft_seg_fault()
{
	char *str;
	int		i = 0;

	str[0] = 'a';
}

void	ft_infinite_loop()
{
	while (1)
		;
}

int main()
{
	ft_bus_error();
}