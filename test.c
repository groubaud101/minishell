/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:37:55 by groubaud          #+#    #+#             */
/*   Updated: 2022/07/13 17:29:21 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/errno.h>

void	ft_bus_error(void)
{
	char	*str;

	str = "coucou";
	str[0] = 'a';
}

void	ft_seg_fault(void)
{
	char	*str;
	int		i;

	i = 0;
	str[0] = 'a';
}

void	ft_infinite_loop(void)
{
	while (1)
		;
}

int	ft_return_errno(int ret_value)
{
	printf("ret : %i\n", ret_value);
	open("./no_write", O_RDWR);
	return (ret_value);
}

int	main(void)
{
	int	ret;

	open("dsad", O_RDONLY);
	perror(NULL);
	ret = ft_return_errno(errno);
	printf("errno : %i\n", errno);
	perror(NULL);
	printf("ret_value : %i\n", ret);
}
