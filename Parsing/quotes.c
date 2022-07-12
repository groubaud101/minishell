/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:58:47 by jrobert           #+#    #+#             */
/*   Updated: 2022/07/12 18:14:30 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cpy_in_quotes(char *content, int *i, int *j, char *new)
{
	char	c;

	if (content[*i] == '\'' || content[*i] == '\"')
	{
		c = content[(*i)++];
		while (content[*i] != c)
			new[(*j)++] = content[(*i)++];
	}
	else
		new[(*j)++] = content[*i];
}

int	len_wo_quotes(char *str)
{
	int		len;
	int		i;
	char	c;

	len = ft_strlen(str);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			c = str[i++];
			while (str[i] != c)
				i++;
			len -= 2;
		}
	}
	return (len);
}

int	remove_quotes(t_token **head)
{
	t_token	*tmp;
	int		i;
	int		j;
	char	*new;

	tmp = *head;
	while (tmp)
	{
		new = malloc(sizeof(char) * (len_wo_quotes(tmp->content) + 1));
		if (!new)
			return (0);
		i = -1;
		j = 0;
		while (tmp->content[++i])
			cpy_in_quotes(tmp->content, &i, &j, new);
		new[j] = '\0';
		free(tmp->content);
		tmp->content = new;
		tmp = tmp->next;
	}
	return (1);
}

int	valid_quotes(char *input)
{
	while (*input++)
	{
		if (*input == '\'')
		{
			input++;
			while (*input && *input != '\'')
				input++;
			if (!*input)
				return (0);
		}
		if (*input == '\"')
		{
			input++;
			while (*input && *input != '\"')
				input++;
			if (!*input)
				return (0);
		}
	}
	return (1);
}

void	handle_quotes(char **input, int *i)
{
	char	c;

	c = (*input)[(*i)++];
	while ((*input)[*i] && (*input)[*i] != c)
		++*i;
	++*i;
}
