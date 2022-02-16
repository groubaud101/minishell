/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_add_slash.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 04:48:07 by groubaud          #+#    #+#             */
/*   Updated: 2022/02/16 04:48:07 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_special_strlen(char const *s, int start, char end)
{
	int	index;

	index = 0;
	while (s[index + start] && s[index + start] != end)
		index++;
	return (index);
}

static size_t	ft_count_word(char const *s, char c)
{
	size_t	ct;

	ct = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
			ct++;
		while (*s && *s != c)
			s++;
	}
	return (ct);
}

static char	**ft_free_tab(char **tab, int len)
{
	while (len)
		free(tab[--len]);
	free(tab);
	return (NULL);
}

static char	**ft_split_two(char const *s, char sep, char **tab, char c)
{
	int		index;
	int		len;

	index = 0;
	while (*s)
	{
		while (*s && *s == sep)
			s++;
		if (*s)
		{
			len = ft_special_strlen(s, 0, sep);
			tab[index] = (char *)ft_calloc(sizeof(**tab), len + 2);
			if (!(tab[index]))
				return (ft_free_tab(tab, index));
			ft_strlcpy(tab[index], s, len + 1);
			tab[index][len] = c;
			s = s + len;
			index++;
		}
	}
	tab[index] = NULL;
	return (tab);
}

char	**ft_split_add_c(char const *s, char sep, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = (char **)malloc(sizeof(*tab) * (ft_count_word(s, sep) + 1));
	if (!tab)
		return (NULL);
	tab = ft_split_two(s, sep, tab, c);
	if (!tab)
		return (NULL);
	return (tab);
}
