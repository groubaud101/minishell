/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 18:11:23 by jrobert           #+#    #+#             */
/*   Updated: 2022/07/12 19:06:35 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	odd_quote_bef(char **strs, int i)
{
	int	n;
	int	j;

	n = 0;
	while (i--)
	{
		j = -1;
		while (strs[i][++j])
		{
			if (strs[i][j] == '\'')
				n++;
		}
	}
	return (n % 2);
}

int	odd_quote_aft(char **strs, int i)
{
	int	n;
	int	j;

	n = 0;
	while (strs[i])
	{
		j = -1;
		while (strs[i][++j])
		{
			if (strs[i][j] == '\'')
				n++;
		}
		i++;
	}
	return (n % 2);
}
