/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_command_redirections.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:51:19 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/01 12:29:56 by kiroussa         ###   ########.fr       */
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
int		msh_exec_simple(t_exec_state *state, char **args);
void	msh_dump_tokens(t_minishell *msh, t_list *tokens);

bool	msh_ast_token_heredoc_expand(t_ast_token *token);
char	*msh_exec_command_heredoc_expand(t_exec_state *state, const char *path,
			const char *new_path);

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
	return (msh_exec_command_heredoc_expand(state, path, new_path));
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

#define TODO_42SH 1

static int	msh_exec_command_setup_redir(t_exec_state *state,
				t_ast_token *token)
{
	if (token->kind == REDIR_HERESTRING)
		return (TODO_42SH);
	if (token->kind == REDIR_HEREDOC_STRIP || token->kind == REDIR_HEREDOC)
		return (msh_exec_command_redirect_file_in(state, token));
	if (token->kind == REDIR_FILE_CLOBBER_A
		|| token->kind == REDIR_FILE_CLOBBER)
		return (TODO_42SH);
	if (token->kind == REDIR_FILE_APPEND)
		return (msh_exec_command_redirect_file_out(state, token));
	if (token->kind == REDIR_FILE_INOUT)
		return (msh_exec_command_redirect_file_in(state, token));
	if (token->kind == REDIR_FD_IN)
		return (TODO_42SH);
	if (token->kind == REDIR_FD_OUT)
		return (TODO_42SH);
	if (token->kind == REDIR_FILE_OUT_A)
		return (msh_exec_command_redirect_file_out(state, token));
	if (token->kind == REDIR_FILE_IN)
		return (msh_exec_command_redirect_file_in(state, token));
	if (token->kind == REDIR_FILE_OUT)
		return (msh_exec_command_redirect_file_out(state, token));
	return (1);
}

static int	msh_exec_command_setup_redirs(t_exec_state *state,
				t_ast_node *node)
{
	t_list		*token;
	t_ast_token	*tkn;
	int			ret;

	token = node->command.redirs;
	ret = 0;
	while (token && !ret)
	{
		tkn = (t_ast_token *) token->content;
		ret = msh_exec_command_setup_redir(state, tkn);
		token = token->next;
	}
	return (ret);
}

static int	msh_exec_command_execute_final(t_exec_state *state,
				t_ast_node *node)
{
	char	**args;
	size_t	i;
	t_list	*token;
	int		ret;

	args = ft_calloc(ft_lst_size(node->command.args) + 1, sizeof(char *));
	if (!args)
		msh_error(state->msh, "failed to allocate args\n");
	if (!args)
		return (1);
	token = node->command.args;
	i = 0;
	while (token)
	{
		args[i++] = ((t_ast_token *) token->content)->value.string;
		token = token->next;
	}
	ret = msh_exec_simple(state, args);
	msh_signal_init(state->msh, false);
	free(args);
	return (ret);
}

int	msh_exec_command_redirections(t_exec_state *state,
				t_ast_node *node)
{
	int		ret;

	ret = msh_exec_command_setup_redirs(state, node);
	if (ret != 0)
	{
		state->msh->execution_context.exit_code = ret;
		return (ret);
	}
	if (ft_lst_size(node->command.args) != 0)
		ret = msh_exec_command_execute_final(state, node);
	return (ret);
}
