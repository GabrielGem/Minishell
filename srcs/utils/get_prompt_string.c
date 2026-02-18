/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 16:48:32 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/17 19:44:54 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*compress_to_tilde(char *cwd, t_hash_table *table);
static int	calc_prompt_size(char *username, char *hostname, char *cwd);
static char	*construct_string(char *username, char *hostname, char *cwd, int size);

char	*get_prompt_string(t_data *context)
{
	char	*username;
	char	*hostname;
	char	*cwd;
	int		size;
	char	*prompt;

	username = hash_search(context->env, "LOGNAME", ENV);
	if (!username)
		username = "user";
	hostname = hash_search(context->env, "NAME", ENV);
	if (!hostname)
		hostname = "unknown";
	cwd = compress_to_tilde(getcwd(NULL, 0), context->env);
	if (!cwd)
		cwd = ft_strdup("unknown");
	size = calc_prompt_size(username, hostname, cwd);
	prompt = construct_string(username, hostname, cwd, size);
	free(cwd);
	if (!prompt)
		return (NULL);
	return (prompt);
}

static char	*compress_to_tilde(char *cwd, t_hash_table *table)
{
	char	*home;
	char	*new_cwd;
	int		len_home;
	int		len_cwd;
	int		not_home;

	home = hash_search(table, "HOME", ENV);
	len_home = ft_strlen(home);
	if (ft_strncmp(cwd, home, len_home) != 0)
		return (cwd);
	len_cwd = ft_strlen(cwd);
	not_home = len_cwd - len_home;
	new_cwd = ft_calloc(not_home + 2, sizeof(char));
	new_cwd[0] = '~';
	ft_strlcpy(&new_cwd[1], &cwd[len_home], not_home + 1);
	return (new_cwd);
}

static int	calc_prompt_size(char *username, char *hostname, char *cwd)
{
	int	size;

	size = ft_strlen(GREEN);
	size += ft_strlen(username);
	size += 1;
	size += ft_strlen(hostname);
	size += ft_strlen(RESET);
	size += 1;
	size += ft_strlen(BLUE);
	size += ft_strlen(cwd);
	size += ft_strlen(RESET);
	size += 2;
	size += 1;
	return (size);
}

static char	*construct_string(char *username, char *hostname, char *cwd, int size)
{
	char	*prompt;

	prompt = ft_calloc(size, sizeof(char));
	if (!prompt)
		return (NULL);
	ft_strlcat(prompt, GREEN, size);
	ft_strlcat(prompt, username, size);
	ft_strlcat(prompt, "@", size);
	ft_strlcat(prompt, hostname, size);
	ft_strlcat(prompt, RESET, size);
	ft_strlcat(prompt, ":", size);
	ft_strlcat(prompt, BLUE, size);
	ft_strlcat(prompt, cwd, size);
	ft_strlcat(prompt, RESET, size);
	ft_strlcat(prompt, "$ ", size);
	return (prompt);
}
