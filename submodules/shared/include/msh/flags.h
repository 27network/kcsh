/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:55:22 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/29 23:54:46 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLAGS_H
# define FLAGS_H
# undef FLAGS_H
# ifndef __MSH_FLAGS_H__
#  define __MSH_FLAGS_H__

#  include <stdbool.h>

typedef struct s_msh_flags
{
	bool	debug_generic;
	bool	debug_ast;
	bool	debug_executor;
	bool	debug_pipelines;
	bool	debug_sanitizer;
	bool	debug_tokenizer;
}	t_msh_flags;

# endif // __MSH_FLAGS_H__
#endif // FLAGS_H
