/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_token_keyword.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 08:17:41 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/04 11:52:52 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/ast/lexer.h>
#include <msh/features.h>

#if FEAT_SCRIPTING
# include <ft/string.h>
# include <stdlib.h>

# define TKN_ACTUAL TKN_KEYWORD
# define KEYWORD_ALLOC_FAIL ": failed to allocate keyword"

static t_ast_keyword_type	msh_find_keyword(char *string)
{
	static const char	*keyword_map[] = {
	[KW_IF] = "if", [KW_THEN] = "then", [KW_ELSE] = "else", [KW_ELIF] = "elif",
	[KW_FI] = "fi", [KW_DO] = "do", [KW_DONE] = "done", [KW_CASE] = "case",
	[KW_ESAC] = "esac", [KW_WHILE] = "while", [KW_UNTIL] = "until", [KW_FOR]
		= "for", [KW_IN] = "in", [KW_BREAK] = "break", [KW_CONTINUE]
		= "continue", [KW_RETURN] = "return", [KW_FUNCTION] = "function",
	[KW_OPEN_BRACE] = "{", [KW_CLOSE_BRACE] = "}", [KW_BANG] = "!",
	[KW_OPEN_BRACKET_BRACKET] = "[["
	};
	size_t				i;

	i = 0;
	while (i < sizeof(keyword_map) / sizeof(*keyword_map))
	{
		if (!ft_strcmp(string, keyword_map[i]))
			return (i);
		i++;
	}
	return (KW_UNKNOWN);
}

static t_ast_error	msh_keyword_token(t_ast_token **token,
						size_t *inc, char *word)
{
	t_ast_keyword_type	type;
	size_t				size;

	size = ft_strlen(word);
	type = msh_find_keyword(word);
	free(word);
	if (size == 0 || type == KW_UNKNOWN)
	{
		msh_ast_token_free(*token);
		return (msh_ast_errd(AST_ERROR_CANCEL, "unexpected keyword",
				false));
	}
	(*token)->kind = type;
	(*token)->value.string = NULL;
	*inc = size;
	return (msh_ast_ok());
}

static void	msh_log_errors(t_ast_lexer *state, t_ast_error err)
{
	if (err.type != AST_ERROR_NONE)
		TRACE(state, TKN_ACTUAL, 2);
	else
		TRACE(state, TKN_ACTUAL, 0);
}

t_ast_error	msh_ast_token_keyword(t_ast_lexer *state, t_ast_token **token,
				size_t *inc)
{
	t_ast_error	err;
	size_t		size;
	char		*value;

	TRACE(state, TKN_ACTUAL, 1);
	size = ft_strcspn(state->input + state->cursor, DELIM_CHARS);
	if (size == 0)
		err = msh_ast_errd(AST_ERROR_CANCEL, "unexpected EOW", false);
	else
	{
		value = ft_strndup(state->input + state->cursor, size);
		if (!value)
			err = msh_ast_errd(AST_ERROR_ALLOC, KEYWORD_ALLOC_FAIL, false);
		else
		{
			err = msh_ast_token_new(TKN_KEYWORD, token);
			if (err.type != AST_ERROR_NONE)
				free(value);
			else
				err = msh_keyword_token(token, inc, value);
		}
	}
	msh_log_errors(state, err);
	return (err);
}

#else

t_ast_error	msh_ast_token_keyword(t_ast_lexer *state, t_ast_token **token,
				size_t *inc)
{
	(void) state;
	(void) token;
	(void) inc;
	return (msh_ast_errd(AST_ERROR_CANCEL, "unexpected keyword",
			false));
}

#endif // FEAT_SCRIPTING
