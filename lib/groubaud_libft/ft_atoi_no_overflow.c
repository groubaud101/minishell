/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_no_overflow.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:29:30 by groubaud          #+#    #+#             */
/*   Updated: 2021/10/22 14:11:57 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	ft_atoi_no_overflow(const char *nbr)
{
	unsigned int	index;
	int				neg;
	unsigned int	limit_div;
	int				limit_mod;
	unsigned int	nb;

	index = 0;
	nb = 0;
	neg = 1;
	while (ft_isspace(nbr[index]) == 1)
		index++;
	if (nbr[index] == '+' || nbr[index] == '-')
		if (nbr[index++] == '-')
			neg = -1;
	limit_div = INT_MAX / 10;
	limit_mod = INT_MAX % 10;
	while (ft_isdigit(nbr[index]) == 1)
	{
		if (nb > limit_div
			|| (nb == limit_div && nbr[index] - '0' - (neg < 0) > limit_mod))
			return (0);
		nb = (nb * 10) + (nbr[index] - '0');
		index++;
	}
	return ((unsigned int)nb * neg);
}
