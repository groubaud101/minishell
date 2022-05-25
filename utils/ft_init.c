/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:08:55 by groubaud          #+#    #+#             */
/*   Updated: 2022/05/25 16:08:55 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_split_once(char *str, char c)
{
	int		i;
	char	**tab;

	i = 0;
	tab = malloc(sizeof(*tab) * 2);
	if (!tab)
		return (NULL);
	while (str[i] && str[i] != c)
		i++;
	tab[0] = ft_strndup(str, i);
	tab[1] = NULL;
	if (str[i] == '\0')
		return (tab);
	str = str + i + 1;
	i = 0;
	while (str[i])
		i++;
	tab[1] = ft_strndup(str, i);
	return (tab);
}// a voir pour les fail malloc

static t_env	*ft_attribute_elem_env(char *envp)
{
	t_env	*lst;
	char	**name_value;

	lst = malloc(sizeof(t_env));
	name_value = ft_split_once(envp, '=');
	if (!name_value)
		exit (0); // malloc fail
	lst->name = name_value[0];
	if (!name_value[0])
		exit (0); // malloc fail ou pas de name ??
	lst->len_name = ft_strlen(lst->name);
	lst->value = name_value[1];
	lst->next = NULL;
	return (lst);
}

static t_env	*ft_init_env(char *envp[])
{
	t_env	*start;
	t_env	*lst;
	int		i;

	i = 0;
	start = NULL;
	while (envp[i])
		i++;
	i--;
	while (i >= 0)
	{
		lst = ft_attribute_elem_env(envp[i]);
		lst->next = start;
		start = lst;
		i--;
	}
	return (start);
}

void	ft_init_mini(t_mini *mini, char **envp)
{
	mini->fd_in = STDIN;
	mini->fd_out = STDOUT;
	mini->env = ft_init_env(envp);
	//ft_aff_env(mini->env);
	mini->env_has_changed = 1;
	mini->envp_tab = NULL;

	mini->paths = ft_split(ft_getenv("PATH", mini->env), ':');
}
