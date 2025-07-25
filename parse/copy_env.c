/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:49:58 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/04 16:47:43 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_equal(char *s)
{
	int	cnt;

	cnt = 0;
	while (s[cnt] && s[cnt] != '=')
		cnt++;
	return (cnt);
}

void	default_env(t_env **env)
{
	int		i;
	char	*ret;

	ret = NULL;
	i = 0;
	if (!environ[i])
	{
		ret = getcwd(NULL, 0);
		env_add_back(env, lstnew_env(ft_strdup("PWD"), ret));
		env_add_back(env, lstnew_env(ft_strdup("SHLVL"), ft_strdup("1"))); 
		env_add_back(env, lstnew_env(ft_strdup("_"), \
		ft_strdup("/usr/bin/env")));
	}
}

char	*env_value(char *name, int i)
{
	char	*value;
	char	*tmp;

	value = ft_substr(environ[i], \
	len_equal(environ[i]) + 1, ft_strlen(environ[i]));
	if (ft_strcmp(name, "SHLVL") == 0)
	{
		tmp = ft_itoa(ft_atoi(value, NULL) + 1);
		free_null(&value);
		value = tmp;
	}
	return (value);
}

void	copy_env(t_env **env)
{
	int		i;
	t_env	*new;
	char	*name;
	char	*value;

	i = 0;
	default_env(env);
	while (environ[i])
	{
		name = ft_substr(environ[i], 0, len_equal(environ[i]));
		if (ft_strcmp(name, "OLDPWD") == 0)
			free_null(&name);
		else
		{
			value = env_value(name, i);
			if (ft_strcmp(name, "_") == 0)
			{
				free_null(&value);
				value = ft_strdup("/usr/bin/env");
			}
			new = lstnew_env(name, value);
			env_add_back(env, new);
		}
		i++;
	}
}
