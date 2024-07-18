/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:54:24 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/18 18:32:22 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H
# undef TYPES_H
# ifndef __MSH_EXEC_TYPES_H__
#  define __MSH_EXEC_TYPES_H__

#  include <msh/minishell.h>

typedef enum e_redir_from
{
	REDIR_FROM_FILE = 0,
	REDIR_FROM_FD,
	REDIR_FROM_PIPE,
}	t_redir_from;

typedef enum e_redir_to
{
	REDIR_TO_FILE = 0,
	REDIR_TO_FD,
	REDIR_TO_PIPE,
}	t_redir_to;

typedef enum e_redir_action
{
	REDIR_IN = 0,
	REDIR_OUT,
	REDIR_OUT_APPEND,
}	t_redir_action;

typedef struct s_redir
{
	t_redir_from	from;
	int				from_fd;

	t_redir_to		to;
	int				to_fd;

	t_redir_action	action;

	const char		*filename;
	bool			clobber;
	int				fd;
}	t_redir;

typedef struct s_command
{
	t_list		*env_mutators;
	t_list		*args;
	t_list		*redirs;
}	t_command;

typedef struct s_pipeline
{
	t_list		*commands;
}	t_pipeline;

# endif // __MSH_EXEC_TYPES_H__
#endif // TYPES_H
