/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:38:10 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/21 19:01:00 by kiroussa         ###   ########.fr       */
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

#  define ENV_EXPORTED		0x0000001	
#  define ENV_READONLY		0x0000002
#  define ENV_ARRAY			0x0000004
#  define ENV_FUNCTION		0x0000008
#  define ENV_INTEGER		0x0000010
#  define ENV_ASSOC			0x0000020
#  define ENV_DYNGEN		0x0000040
#  define ENV_USER_MASK		0x0000fff

#  define ENV_NO_UNSET		0x0001000
#  define ENV_ALLOC_NAME	0x0002000
#  define ENV_ALLOC_VALUE	0x0004000
#  define ENV_IMPORTED		0x0008000
#  define ENV_INVISIBLE		0x0010000
#  define ENV_INT_MASK		0x00ff000

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
 * @brief Gets a variable by name, or NULL if not found.
 *
 * @param msh The minishell instance.
 * @param name The name of the variable.
 *
 * @return The variable or NULL if not found.
 */
t_variable	*msh_env_find(t_minishell *msh, const char *name);

/**
 * @brief Gets a variable by name, creating it if it doesn't exist.
 *
 * @param msh The minishell instance.
 * @param name The name of the variable.
 * @param flags The flags of the variable if it needs to be created.
 *
 * @return The variable.
 */
t_variable	*msh_env_get(t_minishell *msh, const char *name, int flags);

/**
 * @brief Pushes a new variable to the environment, or updates an existing one.
 *
 * @param msh The minishell instance.
 * @param key The name of the variable.
 * @param name The value of the variable.
 * @param flags The flags of the variable.
 *
 * @return The variable that was pushed, or NULL if something failed.
 */
t_variable	*msh_env_push(t_minishell *msh, const char *key, const char *name,
				int flags);

/**
 * @brief Gets the value of a variable by name.
 *
 * @param msh The minishell instance.
 * @param name The name of the variable.
 *
 * @return The value of the variable or NULL if not found.
 */
char		*msh_env_value(t_minishell *msh, const char *name);

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
