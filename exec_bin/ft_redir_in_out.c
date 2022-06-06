/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_in_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 10:59:12 by groubaud          #+#    #+#             */
/*   Updated: 2022/02/16 10:59:12 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** TODO
** It must be that in theory but I don't know how to test it
*/

int	ft_redir_in(t_mini *mini, char *infile)
{
	if (infile == NULL)
		mini->fd_in = STDIN;
	else
		mini->fd_in = open(infile, O_RDONLY);
	if (mini->fd_in == -1)
	{
		printf("could not open the infile blah blah blah\n");
		return (CHECK_ERR);
	}
	return (CHECK_OK);	
}

/*
** TODO
** it's the <<END thing
*/

int	ft_double_redir_in(t_mini *mini, char *infile)
{
	// a faire
	// <<EXPRESSION indique à une lecture sur l'entrée standard (?)
	//  de continuer jusqu'à EXPRESSION non incluse
	mini->fd_in = open(infile, O_RDONLY);
	if (mini->fd_in == -1)
	{
		printf("could not open the infile blah blah blah\n");
		return (CHECK_ERR);
	}
	return (CHECK_OK);	
}

/*
** TO TEST
** mini : the master structure
** outfile : the path of the output file
**
** Attribute the 'fd_out' to the outfile called by '>'
**  create a new if not exist
**  give  write privileges
**  will replace content
*/

int	ft_redir_out(t_mini *mini, char *outfile)
{
	mini->fd_out = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (mini->fd_out == -1)
	{
		printf("could not open the outfile blah blah blah\n");
		return (CHECK_ERR);
	}
	// voir pour un fichier qui existe mais dont on a pas les droits
	return (CHECK_OK);
}

/*
** TO TEST
** mini : the master structure
** outfile : the path of the output file
**
** Attribute the 'fd_out' to the outfile called by '>>'
**  create a new if not exist
**  give write privilege
**  will append new content
*/

int	ft_double_redir_out(t_mini *mini, char *outfile)
{
	mini->fd_out = open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (mini->fd_out == -1)
	{
		printf("could not open the outfile blah blah blah\n");
		return (CHECK_ERR);
	}
	return (CHECK_OK);
}