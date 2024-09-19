/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_token_subst_var.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:53:03 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/19 16:31:44 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <msh/ast/lexer.h>
#include <msh/env.h>

#define TKN_ACTUAL TKN_SUBST
#define ALLOC_FAIL "failed to allocate memory for substitution token"

size_t	msh_ast_get_var_length(char *input, bool is_braces);

static char	*msh_find_variable(const char *input, size_t *len)
{
	size_t	size;
	char	*env;

	if (msh_env_is_special_name_starter(*input))
	{
		*len = 1;
		return (ft_ctostr(*input));
	}
	size = msh_ast_get_var_length((char *) input, false);
	if (!size)
		return (NULL);
	*len = size;
	env = ft_strndup(input, size);
	if (!env)
		return (NULL);
	return (env);
}

/**
 * Simple variable substitution:
 *  - $?
 *  - $VARIABLE_NAME
 *  - $_
 */
t_ast_error	msh_ast_token_subst_var(t_ast_lexer *state, t_ast_token **tknret,
				size_t *inc)
{
	const char	*input = state->input + state->cursor;
	t_ast_token	*token;
	t_ast_error	err;
	char		*value;
	size_t		len;

	if (!input || *input != '$')
		return (msh_ast_errd(AST_ERROR_UNEXPECTED, "unexpected substitution",
				false));
	value = msh_find_variable(input + 1, &len);
	if (!value)
		return (msh_ast_errd(AST_ERROR_ALLOC, ALLOC_FAIL, false));
	err = msh_ast_token_new(TKN_SUBST, &token);
	if (err.type != AST_ERROR_NONE)
		free(value);
	if (err.type != AST_ERROR_NONE)
		return (err);
	token->value.string = value;
	token->kind = SUBST_VAR;
	*tknret = token;
	*inc = len + 1;
	return (msh_ast_ok());
}
