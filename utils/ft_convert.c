/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 23:05:41 by groubaud          #+#    #+#             */
/*   Updated: 2022/05/25 23:05:41 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** t_env *env : the first element of the list
**
** Count the number of element in the list
*/

static int	ft_list_len(t_env *env)
{
	int	len;

	len = 0;
	while (env)
	{
		len++;
		env = env->next;
	}
	return (len);
}

/*
** t_mini *mini : the general structure with everything
**
** Convert the environnement list into a char ** to be like envp
**  it's needed for excve
** It will be stocked in mini as 'envp_tab'
** If it hasn't changed, it won't be reconvert
**  else the previous is freed and envp_tab is (re)made
*/

char	**ft_convert_env_list_to_tab(t_mini *mini)
{
	t_env	*env;
	char	**envp_tab;
	int		i;

	if (mini->env_has_changed == 0)
		return (mini->envp_tab);
	ft_free_tab(mini->envp_tab);
	env = mini->env;
	envp_tab = malloc(sizeof(*envp_tab) * (ft_list_len(env) + 1));
	i = 0;
	while (env)
	{
		envp_tab[i] = ft_strjoin_gnl(NULL, env->name);
		envp_tab[i] = ft_strjoin_gnl(envp_tab[i], "=");
		envp_tab[i] = ft_strjoin_gnl(envp_tab[i], env->value);
		i++;
		env = env->next;
	}
	envp_tab[i] = NULL;
	mini->envp_tab = envp_tab;
	mini->env_has_changed = 0;
	return (NULL);
}