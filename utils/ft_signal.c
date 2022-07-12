/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 11:01:34 by groubaud          #+#    #+#             */
/*   Updated: 2022/07/12 19:52:12 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_ctrl_c(int sig)
{
	if (sig != SIGINT)
		return ;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_ctrl_bs(int sig)
{
	if (sig != SIGQUIT)
		return ;
}

void	ft_attribute_signal(void (*sig_int)(int), void (*sig_quit)(int))
{
	signal(SIGINT, sig_int);
	signal(SIGQUIT, sig_quit);
}
