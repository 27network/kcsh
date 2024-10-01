/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_shell_handle_heredocs.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:36:25 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/01 12:05:31 by kiroussa         ###   ########.fr       */
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
#include <msh/signal.h>
#include <msh/util.h>
#include <string.h>
#include <unistd.h>

char	*msh_input_wrap(t_minishell *msh, const char *prompt, const char *delim,
			bool *borked);

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
				ft_strcat(buffer, tkn->value.string);
				len += ft_strlen(tkn->value.string);
			}
			if (tkn->type == TKN_DELIM && tkn->kind == DELIM_NEWLINE)
				ft_strcat(buffer, "\n");
			if (tkn->type == TKN_DELIM && tkn->kind == DELIM_NEWLINE)
				len++;
		}
		tokens = tokens->next;
	}
	return (len);
}

static int	msh_heredoc_input_strip(char *line, bool strip, int fd,
					const char *delim)
{
	if (!line || (*line && line[1] && ft_strncmp(line, delim,
				ft_strlen(line) - 1) == 0))
		return (1);
	while (strip && *line && *line == '\t')
		line++;
	if (write(fd, line, ft_strlen(line)) == -1)
		msh_error(NULL, "failed to write to heredoc file: %s\n",
			strerror(errno));
	else
		return (0);
	return (1);
}

static bool	msh_listen_heredoc(t_minishell *msh, t_ast_token *token,
				const char *delim, const char *prompt)
{
	const char	*tmp_file = msh_tmpfile("heredoc.", ".tmp");
	const bool	strip = token->kind == REDIR_HEREDOC_STRIP;
	const int	fd = open(tmp_file, O_RDWR | O_CREAT | O_TRUNC, 0600);
	char		*line;
	bool		borked;

	if (fd == -1)
		msh_error(msh, "failed to open heredoc file: %s\n", strerror(errno));
	line = NULL;
	borked = false;
	while (fd != -1 && !msh->forked)
	{
		ft_strdel(&line);
		line = msh_input_wrap(msh, prompt, delim, &borked);
		if (msh_heredoc_input_strip(line, strip, fd, delim))
			break ;
	}
	ft_strdel(&line);
	if (fd == -1 || msh->forked)
		ft_strdel((char **) &tmp_file);
	close(fd);
	if (fd != -1 && !msh->forked)
		token->value.redir.right_string = (char *) tmp_file;
	return (borked);
}

static bool	msh_fill_heredoc(t_minishell *msh, t_ast_token *token,
				const char *prompt, int *res)
{
	const char	*delim;
	size_t		len;

	len = msh_heredoc_delim_size(msh, NULL, token->value.redir.right_word);
	if (!len)
	{
		msh_error(msh, "empty heredoc delimiter\n");
		*res = 3;
		return (false);
	}
	delim = ft_calloc(len + 1, sizeof(char));
	if (!delim)
		msh_error(msh, "failed to allocate heredoc delimiter\n");
	else
		msh_heredoc_delim_size(msh, (char *)delim,
			token->value.redir.right_word);
	if (!delim)
		*res = 2;
	else if (msh_listen_heredoc(msh, token, delim, prompt))
		*res = 128 + SIGINT + 1;
	ft_strdel((char **) &delim);
	return (*res < 1);
}

bool	msh_handle_heredocs(t_minishell *msh, t_list *tokens,
			const char *prompt, int *res)
{
	t_list		*token;
	t_ast_token	*tkn;
	bool		ret;

	ret = true;
	token = tokens;
	while (token && !msh->forked && ret)
	{
		tkn = token->content;
		if (tkn->type == TKN_REDIR)
		{
			if (tkn->kind == REDIR_HEREDOC || tkn->kind == REDIR_HEREDOC_STRIP)
				ret &= msh_fill_heredoc(msh, tkn, prompt, res);
		}
		token = token->next;
	}
	return (ret);
}
