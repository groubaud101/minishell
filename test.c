/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:37:55 by groubaud          #+#    #+#             */
/*   Updated: 2022/07/11 18:00:37 by groubaud         ###   ########.fr       */
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

int main()
{
	ft_seg_fault();
}