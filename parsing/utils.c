/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 17:48:16 by jrobert           #+#    #+#             */
/*   Updated: 2022/07/13 18:30:46 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_tknlst(t_token **head, void (*del)(void *))
{
	t_token	*temp;
	t_token	*ptr;

	if (!head || !del)
		return ;
	temp = *head;
	while (temp)
	{
		(*del)(temp->content);
		ptr = temp;
		temp = temp->next;
		free(ptr);
	}
	*head = NULL;
}

int	free_all(t_token **head)
{
	clear_tknlst(head, free);
	return (0);
}

int	fail(char *err)
{
	ft_putstr_fd("bash: ", 2);
	ft_putendl_fd(err, 2);
	return (0);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*ret;
	size_t	i;
	size_t	j;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ret = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!ret)
		return (NULL);
	i = -1;
	j = -1;
	while (++i < s1_len)
		ret[i] = s1[i];
	while (++j < s2_len)
		ret[i++] = s2[j];
	ret[i] = '\0';
	free(s1);
	s1 = NULL;
	return (ret);
}
