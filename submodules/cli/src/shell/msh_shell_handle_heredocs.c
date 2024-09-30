/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_shell_handle_heredocs.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:36:25 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/30 15:23:09 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <ft/mem.h>
#include <ft/string.h>
#include <msh/ast/builder.h>
#include <msh/ast/lexer.h>
#include <msh/cli/input.h>
#include <msh/log.h>
#include <msh/util.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

char	*msh_input_wrap(t_minishell *msh, const char *prompt,
			const char *delim, const char *old_line);

size_t	msh_heredoc_delim_size(t_minishell *msh, char *buffer,
					t_list *tokens)
{
	size_t		len;
	t_ast_token	*tkn;

	len = 0;
	while (tokens)
	{
		tkn = (t_ast_token *) tokens->content;
		if (tkn->value.data)
		{
			if (tkn->type == TKN_STRING)
				len += msh_heredoc_delim_size(msh, buffer, tkn->value.list);
			if (tkn->type == TKN_WORD || tkn->type == TKN_SUBST
				|| tkn->type == TKN_SEP)
			{
				ft_strlcat(buffer, tkn->value.string, 5000000);
				len += ft_strlen(tkn->value.string);
			}
			if (tkn->type == TKN_DELIM && tkn->kind == DELIM_NEWLINE)
				ft_strlcat(buffer, "\n", 5000000);
			if (tkn->type == TKN_DELIM && tkn->kind == DELIM_NEWLINE)
				len++;
		}
		tokens = tokens->next;
	}
	return (len);
}

static int	msh_heredoc_input_strip(char *line, bool strip, int fd)
{
	while (strip && *line && *line == '\t')
		line++;
	if (write(fd, line, ft_strlen(line)) == -1)
		msh_error(NULL, "failed to write to heredoc file: %s\n",
			strerror(errno));
	else
		return (0);
	return (1);
}

static void	msh_listen_heredoc(t_minishell *msh, t_ast_token *token,
				const char *delim, const char *prompt)
{
	const char	*tmp_file = msh_tmpfile("heredoc.", ".tmp");
	const bool	strip = token->kind == REDIR_HEREDOC_STRIP;
	const int	fd = open(tmp_file, O_RDWR | O_CREAT | O_TRUNC, 0600);
	char		*line;

	if (fd == -1)
		msh_error(msh, "failed to open heredoc file: %s\n", strerror(errno));
	line = NULL;
	while (fd != -1 && !msh->forked)
	{
		line = msh_input_wrap(msh, prompt, delim, line);
		if (!line || (*line && line[1] && ft_strncmp(line, delim,
					ft_strlen(line) - 1) == 0))
			break ;
		if (msh_heredoc_input_strip(line, strip, fd))
			break ;
	}
	ft_strdel(&line);
	if (fd == -1 || msh->forked)
		ft_strdel((char **) &tmp_file);
	close(fd);
	if (fd != -1 && !msh->forked)
		token->value.redir.right_string = (char *) tmp_file;
}

static void	msh_fill_heredoc(t_minishell *msh, t_ast_token *token,
				const char *prompt)
{
	const char	*delim;
	size_t		len;

	len = msh_heredoc_delim_size(msh, NULL, token->value.redir.right_word);
	if (!len)
	{
		msh_error(msh, "empty heredoc delimiter\n");
		return ;
	}
	delim = ft_calloc(len + 1, sizeof(char));
	if (!delim)
		msh_error(msh, "failed to allocate heredoc delimiter\n");
	else
		msh_heredoc_delim_size(msh, (char *)delim,
			token->value.redir.right_word);
	if (!delim)
		return ;
	msh_listen_heredoc(msh, token, delim, prompt);
	free((void *)delim);
}

void	msh_handle_heredocs(t_minishell *msh, t_list *tokens,
			const char *prompt)
{
	t_list		*token;
	t_ast_token	*tkn;

	token = tokens;
	while (token && !msh->forked)
	{
		tkn = token->content;
		if (tkn->type == TKN_REDIR)
		{
			if (tkn->kind == REDIR_HEREDOC || tkn->kind == REDIR_HEREDOC_STRIP)
				msh_fill_heredoc(msh, tkn, prompt);
		}
		token = token->next;
	}
}
