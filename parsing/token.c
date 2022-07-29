/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 18:38:07 by jrobert           #+#    #+#             */
/*   Updated: 2022/07/29 12:45:47 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_spec	find_spec(char *s)
{
	int				i;
	const t_spec	nil = (t_spec){0};
	const t_spec	spec[8] = {{"|", 1, "PIPE"}, {"\n", 1, "NL"},
	{" ", 1, "SPACE"}, {">>", 2, "CHEV_RR"},
	{"<<", 2, "CHEV_LL"}, {">", 1, "CHEV_R"},
	{"<", 1, "CHEV_L"}, {"\t", 1, "TAB"}};

	i = -1;
	while (++i < 8)
	{
		if (!ft_strncmp(spec[i].spec, s, spec[i].size))
			return (spec[i]);
	}
	return (nil);
}

void	tkn_add_back(t_token **alst, t_token *new)
{
	t_token	*ref;

	if (!alst)
		return ;
	ref = *alst;
	if (*alst)
	{
		while (ref->next)
			ref = ref->next;
		ref->next = new;
	}
	else
		*alst = new;
}

t_token	*new_tkn(char *content, int size, char *type)
{
	t_token	*tmp;

	tmp = malloc(sizeof(t_token));
	if (!tmp)
		return (NULL);
	tmp->content = ft_substr(content, 0, size);
	tmp->size = size;
	tmp->type = type;
	tmp->next = NULL;
	return (tmp);
}

void	handle_input(t_token **head, char *input, int *i, int *j)
{
	t_spec	spec;

	spec = (t_spec){0};
	if ((input)[*i] == '\'' || (input)[*i] == '\"')
		handle_quotes(input, i);
	spec = find_spec((input) + *i);
	if (spec.spec)
	{
		if (*i != 0)
		{
			tkn_add_back(head, new_tkn(input, *i, "WORD"));
			*j += *i;
		}
		else
		{
			tkn_add_back(head, new_tkn(spec.spec, spec.size, spec.type));
			*j += spec.size;
		}
		*i = -1;
	}
	(*i)++;
}

int	tokenize(t_shell *shell, char *input, t_token **head)
{
	int		i;
	int		j;

	if (!valid_quotes(input))
		ft_exit_error(shell, errno);
	i = 0;
	while (input[i])
	{
		j = 0;
		handle_input(head, input + j, &i, &j);
		input = input + j;
		if (!input[i])
			break ;
	}
	if (input[0] && &(input[i]) != input)
		tkn_add_back(head, new_tkn(input, i, "WORD"));
	if (ft_check_no_word(*head) == CHECK_ERR)
		return (0);
	if (!replace_env_var(shell, head))
		ft_exit_error(shell, errno);
	if (!remove_quotes(head))
		ft_exit_error(shell, errno);
	return (1);
}
