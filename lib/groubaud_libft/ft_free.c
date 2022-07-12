/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 22:46:04 by groubaud          #+#    #+#             */
/*   Updated: 2022/07/12 19:39:08 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void	ft_free_tab_tab_int(int **tab, int size)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (i < size)
		free(tab[i++]);
	free(tab);
}

void	ft_free_tab_tab(char ***tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		ft_free_tab(tab[i++]);
	free(tab);
}

static int	ft_free_part_tab(char *format, va_list params, int i)
{
	int	**tab_int;
	int	size;

	if (format[i] == 'i')
		free((int *)va_arg(params, int *));
	else if (format[i] == 's')
		ft_free_tab((char **)va_arg(params, char **));
	else if (format[i++] == 't')
	{
		if (format[i] == 's')
			ft_free_tab_tab((char ***)va_arg(params, char ***));
		else if (format[i] == 'i')
		{
			tab_int = (int **)va_arg(params, int **);
			size = (int)va_arg(params, int);
			ft_free_tab_tab_int(tab_int, size);
		}
	}
	return (i);
}

/*
** ret_value : value to return
** format : string to implement what has to be freed
** ... : params to free
**
** free the params, type defined by format
**
** 	"%s %ts %ti %tts %tti %special"
** 	s : string of characters
** 	ts : tab of string
** 	ti : tab of int
** 	tts : tab of tab of string
** 	tti : tab of tab of int, second param for the size of the tab
**
** ex : ft_free(0, "%ti %s %s %tti", tab_int, str, str2, size_tab_int);
*/

int	ft_free(int ret_value, char *format, ...)
{
	int		i;
	va_list	params;

	va_start(params, format);
	i = 0;
	while (format[i])
	{
		while (format[i] && format[i++] != '%')
			;
		if (format[i] == 's')
			free((char *)va_arg(params, char *));
		else if (format[i++] == 't')
		{
			i = ft_free_part_tab(format, params, i);
		}
		i++;
	}
	return (ret_value);
}
