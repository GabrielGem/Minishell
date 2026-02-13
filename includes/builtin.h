/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 10:24:41 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/11 18:44:27 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

typedef int	(*t_builtin)(t_data *context, char **args);

int	b_cd(t_data *context, char **args);
int	b_echo(t_data *context, char **args);
int	b_env(t_data *context, char **args);
int	b_exit(t_data *context, char **args);
int	b_export(t_data *context, char **args);
int	b_pwd(t_data *context, char **args);
int	b_unset(t_data *context, char **args);

#endif
