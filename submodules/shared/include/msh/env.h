/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouchet <ebouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:38:10 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/02 20:19:16 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# undef ENV_H
# ifndef __MSH_ENV_H__
#  define __MSH_ENV_H__

#  include <msh/minishell.h>

#  define ENV_DEFAULT_PS1 "\\u@\\h:\\w\\$ "
#  define ENV_DEFAULT_PS2 "> "
#  define ENV_DEFAULT_PS3 "# "
#  define ENV_DEFAULT_PS4 "+ "
#  define ENV_DEFAULT_HISTFILE "~/.kcsh_history"
#  define ENV_DEFAULT_HISTFILESIZE 500
#  define ENV_DEFAULT_HISTSIZE 500

#  define ENV_DEFAULT_PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:\
/usr/bin:/sbin:/bin"
#  define ENV_DEFAULT_IFS " \t\n"
#  define ENV_DEFAULT_TERM "dumb"

#  define ENV_EXPORTED		0x0000001	
#  define ENV_READONLY		0x0000002
#  define ENV_ARRAY			0x0000004
#  define ENV_FUNCTION		0x0000008
#  define ENV_INTEGER		0x0000010
#  define ENV_ASSOC			0x0000020
#  define ENV_DYNGEN		0x0000040

#  define ENV_NO_UNSET		0x0001000
#  define ENV_ALLOC_NAME	0x0002000
#  define ENV_ALLOC_VALUE	0x0004000
#  define ENV_IMPORTED		0x0008000
#  define ENV_INVISIBLE		0x0010000
#  define ENV_COPIED		0x0020000

typedef struct s_variable	t_variable;

typedef char				*t_variable_fn(t_minishell *msh,
	t_variable *variable, size_t array_idx, const char *target);

typedef struct s_variable
{
	char				*name;
	char				*value;
	t_variable_fn		*value_fn;
	t_variable_fn		*set_fn;
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
 * @param value The value of the variable.
 * @param flags The flags of the variable.
 *
 * @return The variable that was pushed, or NULL if something failed.
 */
t_variable	*msh_env_push(t_minishell *msh, const char *key, const char *value,
				int flags);

/**
 * @brief Sets the value of a variable by name, only if it doesn't exist.
 *
 * @param msh The minishell instance.
 * @param key The name of the variable.
 * @param value The value of the variable.
 * @param flags The flags of the variable.
 *
 * @return The variable that was set, or NULL if something failed.
 */
t_variable	*msh_env_set_if_not(t_minishell *msh, const char *key,
				const char *value, int flags);

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
 * @brief Gets an array of variables sorted by name.
 *
 * @param msh The minishell instance.
 *
 * @return The array of variables.
 */
t_variable	*msh_env_sorted(t_minishell *msh);

/**
 * @brief Whether a variable name is valid.
 *
 * @param name The name of the variable.
 * @param assignment Whether the name is part of an assignment.
 *					 (Thus disallowing special names like ?, 0, etc.)
 *
 * @return Whether the name is valid.
 */
bool		msh_env_is_valid_name(const char *name, bool assignment);

/**
 * @brief Whether a character is a valid variable name starter.
 *
 * @param c The character.
 *
 * @return Whether the character is a valid variable name starter.
 */
bool		msh_env_is_valid_name_starter(const char c);

/**
 * @brief Whether a character is a valid special name starter.
 *
 * @param c The character.
 *
 * @return Whether the character is a valid special name starter.
 */
bool		msh_env_is_special_name_starter(const char c);

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

/**
 * @brief Prints an assignment statement for a variable (such as NAME=VALUE)
 *
 * @param msh The minishell instance.
 * @param variable The variable to print the assignment for.
 * @param quote_type The quoting strategy to use.
 */
void		msh_env_print_assignment(t_minishell *msh, t_variable *variable,
				int quote_type);

#  if 0
/**
 * @brief Debug function used to print all flags of a variable.
 *
 * @param variable The variable to print the flags of.
 */
void		msh_env_print_flags(t_variable *variable);
#  endif

# endif // __MSH_ENV_H__
#endif // ENV_H
