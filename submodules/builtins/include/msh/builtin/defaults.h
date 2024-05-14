/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defaults.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 02:55:22 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/14 13:37:02 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFAULTS_H
# define DEFAULTS_H
# undef DEFAULTS_H
# ifndef __MSH_BUILTIN_DEFAULTS_H__
#  define __MSH_BUILTIN_DEFAULTS_H__

#  include <msh/minishell.h>
#  include <ft/print.h>
#  include <ft/string.h>

#  define NEEDS_ENV 0b01
#  define NEEDS_MSH 0b10

typedef struct s_builtin
{
	const char	*name;
	const char	*usage;

	int			(*func)();
	int			needs;
}	t_builtin;

void		msh_builtin_register(t_builtin builtin);

# endif // __MSH_BUILTIN_DEFAULTS_H__
#endif // DEFAULTS_H
