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

char	**ft_convert_env_list_to_tab(t_mini *mini)
{
	t_env	*env;
	char	**envp_tab;
	int		i;

	if (mini->env_has_changed == 0)
		return (mini->envp_tab);
	ft_free_envp_tab(mini->envp_tab);
	env = mini->env;
	envp_tab = malloc(sizeof(*envp_tab) * (ft_list_len(env) + 1));
	i = 0;
	while (env)
	{
		envp_tab[i] = ft_strjoin_gnl(NULL, env->name);
		envp_tab[i] = ft_strjoin_gnl(envp_tab[i], "=");
		envp_tab[i] = ft_strjoin_gnl(envp_tab[i], env->value);
		printf("envp_tab[%i] : |%s|\n", i, envp_tab[i]);
		i++;
		env = env->next;
	}
	envp_tab[i] = NULL;
	ft_puttab(envp_tab, " COUCOU\n");
	mini->env_has_changed = 0;
	return (NULL);
}