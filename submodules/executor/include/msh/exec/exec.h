/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 07:24:53 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/06 22:11:26 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# undef EXEC_H
# ifndef __MSH_EXEC_EXEC_H__
#  define __MSH_EXEC_EXEC_H__

/**
 * TODO: @kiroussa: rename this header
 */

#  include <msh/minishell.h>

typedef enum e_redir_type
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	REDIR_HERESTRING,
	REDIR_PIPE,
}	t_redir_type;

typedef struct s_command
{
	char	*cmd;
	char	**args;
	int		argc;
}	t_command;

typedef struct s_pipeline
{
	t_command	*commands;
	int			pipe_count;
}	t_pipeline;

typedef enum e_pipeline_separator
{
	PIPELINE_SEP_SEMICOLON,
	PIPELINE_SEP_AND,
	PIPELINE_SEP_OR,
}	t_pipeline_separator;

int	msh_exec_simple(t_minishell *msh, char **line);

# endif // __MSH_EXEC_EXEC_H__
#endif // EXEC_H
