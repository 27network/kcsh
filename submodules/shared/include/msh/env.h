/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:38:10 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/18 02:22:21 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# undef ENV_H
# ifndef __MSH_ENV_H__
#  define __MSH_ENV_H__

#  include <msh/minishell.h>

int		msh_env_populate(t_minishell *msh, const char **envp);
void	msh_env_defaults(t_minishell *msh);

char	*msh_env_get(t_minishell *msh, const char *key);

void	msh_env_free(t_minishell *msh);
void	msh_env_node_free(t_map_node *node);

char	**msh_env_tab(t_minishell *msh);
void	msh_env_tab_free(char **tab);

# endif // __MSH_ENV_H__
#endif // ENV_H
