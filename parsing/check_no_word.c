/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_no_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:33:31 by groubaud          #+#    #+#             */
/*   Updated: 2022/07/29 12:44:49 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_chevr_pipe(char *str)
{
	if (ft_strcmp(str, ">") == 0
		|| ft_strcmp(str, ">>") == 0
		|| ft_strcmp(str, "<") == 0
		|| ft_strcmp(str, "<<") == 0
		|| ft_strcmp(str, "|") == 0)
		return (CHECK_OK);
	return (CHECK_ERR);
}

int	ft_check_no_word(t_token *list)
{
	t_token	*tmp;
	int		ctrl;

	tmp = list;
	ctrl = 0;
	while (tmp)
	{
		if (ft_is_chevr_pipe(tmp->content) == CHECK_OK)
		{
			ctrl = 1;
			break ;
		}
		tmp = tmp->next;
	}
	if (ctrl == 0)
		return (CHECK_OK);
	tmp = list;
	while (tmp)
	{
		if (ctrl == 1 && ft_strcmp(tmp->type, "WORD") == 0)
			return (CHECK_OK);
		tmp = tmp->next;
	}
	return (CHECK_ERR);
}
