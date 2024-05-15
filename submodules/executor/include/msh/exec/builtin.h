/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 22:50:53 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/15 12:50:45 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# undef BUILTIN_H
# ifndef __MSH_EXEC_BUILTIN_H__
#  define __MSH_EXEC_BUILTIN_H__

#  include <msh/minishell.h>
#  include <msh/builtin/defaults.h>

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
t_builtin	*msh_builtin_get(const char *name);

# endif // __MSH_EXEC_BUILTIN_H__
#endif // BUILTIN_H
