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

int	ft_redir_in(int *fd_in, char *infile)
{
	if (infile == NULL)
		*fd_in = 0;
	else
		*fd_in = open(infile, O_RDONLY);
	if (*fd_in == -1)
	{
		printf("could not open the infile blah blah blah\n");
		return (CHECK_ERR);
	}
	return (CHECK_OK);	
}

int	ft_double_redir_in(int *fd_in, char *infile)
{
	// a faire
	// <<EXPRESSION indique à une lecture sur l'entrée standard (?)
	//  de continuer jusqu'à EXPRESSION non incluse
	*fd_in = open(infile, O_RDONLY);
	if (*fd_in == -1)
	{
		printf("could not open the infile blah blah blah\n");
		return (CHECK_ERR);
	}
	return (CHECK_OK);	
}

int	ft_redir_out(int *fd_out, char *outfile)
{
	*fd_out = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (*fd_out == -1)
	{
		printf("could not open the outfile blah blah blah\n");
		return (CHECK_ERR);
	}
	// voir pour un fichier qui existe mais dont on a pas les droits
	return (CHECK_OK);
}

int	ft_double_redir_out(int *fd_out, char *outfile)
{
	*fd_out = open(outfile, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (*fd_out == -1)
	{
		printf("could not open the outfile blah blah blah\n");
		return (CHECK_ERR);
	}
	return (CHECK_OK);
}