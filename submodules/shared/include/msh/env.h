/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:38:10 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/20 13:17:16 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# undef ENV_H
# ifndef __MSH_ENV_H__
#  define __MSH_ENV_H__

#  include <msh/minishell.h>

#  define DEFAULT_ENV_PS1 "\u@\h:\w\$ "
#  define DEFAULT_ENV_PS2 "> "
#  define DEFAULT_ENV_PS3 "# "
#  define DEFAULT_ENV_PS4 "+ "

#  define DEFAULT_IFS " \t\n"

#  define ENV_ATTR_EXPORTED  0x0000001	
#  define ENV_ATTR_READONLY	 0x0000002
#  define ENV_ATTR_ARRAY	 0x0000004
#  define ENV_ATTR_FUNCTION	 0x0000008
#  define ENV_ATTR_INTEGER	 0x0000010
#  define ENV_ATTR_ASSOC	 0x0000020
#  define ENV_ATTR_USER_MASK 0x0000fff

#  define ENV_ATTR_NO_UNSET  0x0001000
#  define ENV_ATTR_INT_MASK  0x00ff000

typedef struct s_variable
{
	char	*name;
	char	*value;
	int		attributes;
}	t_variable;

int			msh_env_populate(t_minishell *msh, const char **envp);
void		msh_env_defaults(t_minishell *msh);

// char	*msh_env_get(t_minishell *msh, const char *key);
//
// void	msh_env_free(t_minishell *msh);
// void	msh_env_node_free(t_map_node *node);

t_variable	msh_env_get(t_minishell *msh, const char *name);

/**
 * @brief Builds a new array of name-sorted variables.
 *
 * @param msh The minishell instance.
 * @param match_flags The flags to match the variables.
 *
 * @return A new array of name-sorted variables.
 */
char		**msh_env_tab(t_minishell *msh, int match_flags);

/**
 * @brief
 */
void		msh_env_tab_free(char **tab);

# endif // __MSH_ENV_H__
#endif // ENV_H
