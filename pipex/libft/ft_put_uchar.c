/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_uchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 22:36:15 by groubaud          #+#    #+#             */
/*   Updated: 2021/06/12 17:51:30 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"

void	ft_put_uchar(unsigned char c)
{
	write(1, &c, 1);
}

void	ft_put_uchar_fd(unsigned char c, int fd)
{
	write(fd, &c, 1);
}
