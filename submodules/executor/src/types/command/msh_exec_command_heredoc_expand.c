/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_command_heredoc_expand.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:21:46 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/01 12:28:41 by kiroussa         ###   ########.fr       */
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

size_t		msh_heredoc_delim_size(t_minishell *msh, char *buffer,
				t_list *tokens);

bool	msh_ast_token_heredoc_expand(t_ast_token *token)
{
	t_list	*tokens;

	if (token->kind != REDIR_HEREDOC_STRIP && token->kind != REDIR_HEREDOC)
		return (false);
	tokens = token->value.redir.right_word;
	if (!tokens)
		return (false);
	if (ft_lst_size(tokens) != 1)
		return (false);
	return (true);
}

char	*msh_exec_command_heredoc_to_string(t_exec_state *state, t_list *tokens)
{
	size_t		len;
	char		*line;

	len = msh_heredoc_delim_size(state->msh, NULL, tokens);
	line = ft_calloc(len + 1, sizeof(char));
	if (!line)
		return (NULL);
	msh_heredoc_delim_size(state->msh, (char *)line, tokens);
	return (line);
}

char	*msh_exec_command_expand_transform(t_exec_state *state, char *line)
{
	t_ast_lexer		lexer;
	t_ast_error		err;
	const uint64_t	fork_state = state->msh->forked;

	lexer = msh_ast_lexer_root(state->msh, line);
	lexer.allow_subst = true;
	lexer.discrim_mode = true;
	state->msh->forked = 0;
	err = msh_ast_tokenize(&lexer);
	if (!err.type)
		err = msh_ast_transform(state->msh, &lexer.tokens);
	state->msh->forked = fork_state;
	free(line);
	if (err.type)
	{
		msh_ast_error_print(state->msh, err);
		ft_lst_free(&lexer.tokens, (t_lst_dealloc) msh_ast_token_free);
		return (NULL);
	}
	return (msh_exec_command_heredoc_to_string(state, lexer.tokens));
}

void	msh_exec_command_heredoc_expand_loop(t_exec_state *state,
			int fd, int fd2)
{
	char	*line;

	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		line = msh_exec_command_expand_transform(state, line);
		if (!line)
			break ;
		if (write(fd2, line, ft_strlen(line)) == -1)
			msh_error(state->msh, "failed to write to heredoc file: %s\n",
				strerror(errno));
		free(line);
	}
}

char	*msh_exec_command_heredoc_expand(t_exec_state *state, const char *path,
			const char *new_path)
{
	int		fd;
	int		fd2;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		free((void *)new_path);
	if (fd == -1)
		return (NULL);
	fd2 = open(new_path, O_WRONLY | O_CREAT | O_TRUNC, DEFAULT_MODE);
	if (fd2 == -1)
	{
		free((void *)new_path);
		close(fd);
		return (NULL);
	}
	msh_exec_command_heredoc_expand_loop(state, fd, fd2);
	close(fd2);
	close(fd);
	return ((char *) new_path);
}
