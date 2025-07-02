/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfartah <sfartah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:36:50 by ychedmi           #+#    #+#             */
/*   Updated: 2025/07/02 20:32:20 by sfartah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

t_parce	*main_parse(char *s, t_env *env)
{
	t_token	*head;
	t_parce	*list;

	list = NULL;
	head = NULL;
	if (calc_qout(s) == -1 || valid_word(s) == -1)
		return (NULL);
	tokenization(s, &head);
	if (!head)
		return (NULL);
	pars_ing(&list, head, env);
	ft_lstclear(head);
	return (list);
}

int	int_while(t_env **env)
{
	char	*line;
	t_parce	*lst;

	lst = NULL;
	rl_catch_signals = 0;
	while (1)
	{
		signalss();
		line = readline("minishell$ ");
		if (!line)
			return (free_env(*env), *env = NULL, \
			free_doublst(&lst), printf("exit\n"), 0);
		if (*line)
			add_history(line);
		lst = main_parse(line, *env);
		free_null(&line);
		if (lst)
			execute(lst, env);
		free_doublst(&lst);
	}
	return (g_status);
}

int	main(int ac, char **av)
{
	t_env	*env;
	int		ret;

	(void)av;
	ret = 0;
	env = NULL;
	if (ac == 1)
	{
		copy_env(&env);
		ret = int_while(&env);
		free_env(env);
	}
	return (ret);
}
