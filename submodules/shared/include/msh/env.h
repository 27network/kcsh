/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:38:10 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/20 20:30:35 by kiroussa         ###   ########.fr       */
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

#  define ENV_FLAG_EXPORTED		0x0000001	
#  define ENV_FLAG_READONLY		0x0000002
#  define ENV_FLAG_ARRAY		0x0000004
#  define ENV_FLAG_FUNCTION		0x0000008
#  define ENV_FLAG_INTEGER		0x0000010
#  define ENV_FLAG_ASSOC		0x0000020
#  define ENV_FLAG_DYNGEN		0x0000040
#  define ENV_FLAG_USER_MASK	0x0000fff

#  define ENV_FLAG_NO_UNSET		0x0001000
#  define ENV_FLAG_ALLOC_NAME	0x0002000
#  define ENV_FLAG_ALLOC_VALUE	0x0004000
#  define ENV_FLAG_INT_MASK		0x00ff000

typedef struct s_variable	t_variable;

typedef char				*t_variable_fn(t_minishell *msh,
								t_variable *variable);

typedef struct s_variable
{
	char				*name;
	char				*value;
	t_variable_fn		*fn;
	int					flags;
	struct s_variable	*next;
}	t_variable;

int			msh_env_populate(t_minishell *msh, const char **envp);
void		msh_env_defaults(t_minishell *msh);

/**
 * @brief Gets a variable by name.
 *
 * @param msh The minishell instance.
 * @param name The name of the variable.
 *
 * @return The variable or NULL if not found.
 */
t_variable	*msh_env_get(t_minishell *msh, const char *name);

/**
 * @brief Gets the value of a variable by name.
 *
 * @param msh The minishell instance.
 * @param name The name of the variable.
 *
 * @return The value of the variable or NULL if not found.
 */
char		*msh_env_get_value(t_minishell *msh, const char *name);

/**
 * @brief Adds a new variable, or updates an existing one.
 *
 * @param msh The minishell instance.
 * @param variable The new variable.
 *
 * @return The added variable, the already existing variable,
 *		   or NULL if an error occurred.
 */
t_variable	*msh_env_push(t_minishell *msh, t_variable *variable);

/**
 * @brief Checks if a variable has a flag.
 *
 * @param variable The variable to check.
 * @param flag The flag to check.
 *
 * @return `true` if the variable has the flag, `false` otherwise.
 */
bool		msh_env_is_flag(t_variable *variable, int flag);

/**
 * @brief Sets a flag on a variable.
 *
 * @param variable The variable to set the flag on.
 * @param flag The flag to set.
 */
void		msh_env_set_flag(t_variable *variable, int flag);

/**
 * @brief Frees all variables.
 *
 * @param msh The minishell instance.
 */
void		msh_env_free_all(t_minishell *msh);

/**
 * @brief Frees a variable.
 *
 * @param variable The variable to free.
 */
void		msh_env_free(t_variable *variable);

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
 * @brief Frees the array of variables.
 *
 * @param tab The array of variables.
 */
void		msh_env_tab_free(char **tab);

# endif // __MSH_ENV_H__
#endif // ENV_H
