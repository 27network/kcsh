/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_command_redirect_setup.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:00:20 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/01 18:07:56 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <ft/io.h>
#include <ft/mem.h>
#include <ft/string.h>
#include <msh/ast/builder.h>
#include <msh/ast/transformer.h>
#include <msh/exec.h>
#include <msh/log.h>
#include <msh/signal.h> 
#include <msh/util.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define LEVEL MSG_DEBUG_EXECUTOR

char	*msh_ast_strredir(t_ast_redir_type type);
bool	msh_ast_token_heredoc_expand(t_ast_token *token);
char	*msh_exec_command_heredoc_expand(t_exec_state *state,
			t_ast_token *token, const char *path, const char *new_path);

char	*msh_exec_command_heredoc_in(t_exec_state *state,
			t_ast_token *token, bool heredoc_expand)
{
	char	*path;
	char	*new_path;

	path = token->value.redir.right_string;
	if (!path || access(path, F_OK) == -1)
	{
		msh_error(state->msh, "heredoc file not found: %s\n", path);
		if (path)
			free(path);
		return (NULL);
	}
	if (!heredoc_expand)
		return (path);
	new_path = (char *) msh_tmpfile("heredoc-xpand.", ".tmp");
	if (!new_path)
		return (path);
	return (msh_exec_command_heredoc_expand(state, token, path, new_path));
}

char	*msh_exec_command_extrapolate_path(t_exec_state *state,
			t_ast_token *token, bool heredoc_expand)
{
	char		*path;
	t_ast_error	err;

	if (token->kind == REDIR_HEREDOC_STRIP || token->kind == REDIR_HEREDOC)
		return (msh_exec_command_heredoc_in(state, token, heredoc_expand));
	if (!token->value.redir.right_word)
		msh_error(state->msh, "Missing right word for redirection\n");
	if (!token->value.redir.right_word)
		return (NULL);
	err = msh_ast_transform(state->msh, &token->value.redir.right_word);
	if (err.type)
		msh_ast_error_print(state->msh, err);
	if (err.type)
		return (NULL);
	if (ft_lst_size(token->value.redir.right_word) != 1)
		msh_error(state->msh, "ambiguous redirect\n");
	if (ft_lst_size(token->value.redir.right_word) != 1)
		return (NULL);
	path = ((t_ast_token *) token->value.redir.right_word->content)
		->value.string;
	if (!path)
		msh_error(state->msh, "Missing right word for redirection\n");
	return (path);
}

int	msh_exec_command_redirect_file_in(t_exec_state *state, t_ast_token *token)
{
	const bool	heredoc_expand = msh_ast_token_heredoc_expand(token);
	int			flags;
	char		*path;
	int			fd;

	flags = O_RDONLY;
	if (token->kind == REDIR_FILE_INOUT)
		flags = (flags & ~O_RDONLY) | O_RDWR | O_CREAT;
	path = msh_exec_command_extrapolate_path(state, token, heredoc_expand);
	if (!path)
		return (1);
	msh_log(state->msh, LEVEL, "opening (in) %s\n", path);
	fd = open(path, flags, DEFAULT_MODE);
	if (fd == -1)
		msh_error(state->msh, "%s: %s\n", path, strerror(errno));
	else if (dup2(fd, STDIN_FILENO) == -1)
	{
		msh_error(state->msh, "%s: %s\n", path, strerror(errno));
		free((void *)path);
		return (close(fd) | 1);
	}
	if (fd != -1)
		return (close(fd));
	return (fd == -1);
}

int	msh_exec_command_redirect_file_out(t_exec_state *state, t_ast_token *token)
{
	int		flags;
	char	*path;
	int		fd;

	flags = O_WRONLY | O_CREAT | O_TRUNC;
	if (token->kind == REDIR_FILE_APPEND)
		flags = (flags & ~O_TRUNC) | O_APPEND;
	path = msh_exec_command_extrapolate_path(state, token, false);
	if (!path)
		return (1);
	msh_log(state->msh, LEVEL, "opening (out) %s from %s\n", path,
		msh_ast_strredir(token->kind));
	fd = open(path, flags, DEFAULT_MODE);
	if (fd == -1)
		msh_error(state->msh, "%s: %s\n", path, strerror(errno));
	if (fd == -1)
		return (1);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		msh_error(state->msh, "%s: %s\n", path, strerror(errno));
		close(fd);
		return (1);
	}
	return (close(fd));
}
