/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_cmd1_cmd2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 05:15:30 by groubaud          #+#    #+#             */
/*   Updated: 2022/02/16 05:15:30 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_set_cmd1_cmd2(char ***cmd1, char ***cmd2, char **av)
{
	*cmd1 = ft_split(av[2], ' '); // faudra le changer pour tout ce qui est espace je pense
	if (!(*cmd1))
		return (-1);
	*cmd2 = ft_split(av[3], ' '); // faudra le changer pour tout ce qui est espace je pense
	if (!(*cmd2))
		return (-1);
	return (CHECK_OK);	
}
