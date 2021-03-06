/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:12:23 by user42            #+#    #+#             */
/*   Updated: 2021/08/23 16:35:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_pow_int(int nb, int p)
{
	int	i;
	int	ori;

	i = 1;
	ori = nb;
	if (p == 0)
		return (1);
	else if (p < 0 || nb == 0)
		return (0);
	while (i++ < p)
		nb = ori * nb;
	return (nb);
}
