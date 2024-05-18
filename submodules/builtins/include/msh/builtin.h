/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 02:55:22 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/17 03:03:46 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# undef BUILTIN_H
# ifndef __MSH_BUILTIN_H__
#  define __MSH_BUILTIN_H__

#  include <msh/minishell.h>
#  include <ft/print.h>
#  include <ft/string.h>

#  define NEEDS_ENV 0b01
#  define NEEDS_MSH 0b10

#  define ATTR __attribute__

/**
 * @brief Builtin structure
 *
 * @param name		Builtin name, used to call the builtin
 * @param usage		Builtin usage, used to print usage from the `help` command
 * @param help		Builtin help, used to print help from the `help` command
 *
 * @param func		Builtin function to call
 * @param needs		Flags to specify what the builtin function requires as
 *					its arguments
 * 
 * @param enabled	Flag to specify if the builtin is enabled or not (can change
 * 					during runtime via the `enable` command)
 * @param hidden	Flag to specify if the builtin should be hidden from the
 *					`help` command (used for `env`)
 */
typedef struct s_builtin
{
	const char	*name;
	const char	*usage;
	const char	*help;

	int			(*func)();
	int			needs;

	bool		enabled;
	bool		hidden;
}	t_builtin;

void		msh_builtin_help_page(char *name, int fd);
void		msh_builtin_print_help(t_builtin *builtin, int fd);
void		msh_builtin_print_usage(t_builtin *builtin, int fd);

// just to be sure
#  define BUILTIN_REGISTRY_SIZE 256

// god i hate C2X 
typedef int	(*t_builtin_fboth)(int, char **, char **, t_minishell *);
typedef int	(*t_builtin_fenv)(int, char **, char **);
typedef int	(*t_builtin_fmsh)(int, char **, t_minishell *);
typedef int	(*t_builtin_fnone)(int, char **);

/**
 * @see src/builtin/msh_builtin_registry.c
 */
t_builtin	*msh_builtin_registry(void);
void		msh_builtin_register(t_builtin builtin);
t_builtin	*msh_builtin_get(const char *name);
size_t		msh_builtin_count(void);

# endif // __MSH_BUILTIN_H__
#endif // BUILTIN_H
