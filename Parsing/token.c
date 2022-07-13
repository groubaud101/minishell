/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 18:38:07 by jrobert           #+#    #+#             */
/*   Updated: 2022/07/13 18:33:20 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_spec	find_spec(char *s)
{
	int				i;
	const t_spec	nil = (t_spec){0};
	const t_spec	spec[7] = {{"|", 1, "PIPE"}, {"\n", 1, "NL"},
	{" ", 1, "SPACE"}, {">>", 2, "CHEV_RR"},
	{"<<", 2, "CHEV_LL"}, {">", 1, "CHEV_R"},
	{"<", 1, "CHEV_L"}};

	i = -1;
	while (++i < 7)
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

void	handle_input(t_token **head, char **input, int *i)
{
	t_spec	spec;

	spec = (t_spec){0};
	printf(COUCOU);
	printf("input1 : |%s|, i : %i\n", *input, *i);
	if ((*input)[*i] == '\'' || (*input)[*i] == '\"')
		handle_quotes(input, i);
	spec = find_spec(&((*input)[*i]));
	if (spec.spec)
	{
		printf(COUCOU);
		printf("input2 : |%s|, i : %i\n", *input, *i);
		if (input[*i] != *input)
		{
			printf(COUCOU);
			tkn_add_back(head, new_tkn(*input, *i, "WORD"));
			*input += *i;
		}
		printf(COUCOU);
		printf("input4 : |%s|, i : %i, spec.size : %i\n",
		*input, *i, spec.size);
		tkn_add_back(head, new_tkn(spec.spec, spec.size, spec.type));
		*input += spec.size;
		*i = -1;
	}
		printf(COUCOU);
		printf("input_final : |%s|, i : %i\n", *input, *i);
}

int	tokenize(t_shell *shell, char *input, t_token **head)
{
	int		i;

	if (!valid_quotes(input))
		ft_exit_error(shell, errno);
	i = -1;
	while (input[++i])
		handle_input(head, &input, &i);
	if (&input[i] != input)
		tkn_add_back(head, new_tkn(input, i, "WORD"));
	if (!replace_env_var(shell, head))
		ft_exit_error(shell, errno);
	if (!remove_quotes(head))
		ft_exit_error(shell, errno);
	return (1);
}
