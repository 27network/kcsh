/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_ast_lexer_is_delim.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:32:46 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/28 15:32:30 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/ast/lexer.h>

bool	msh_ast_lexer_check_delim(t_ast_lexer *state, const char c)
{
	if (c == 0 && state->delim != NULL)
		return (false);
	return (c == 0 || ft_strchr(state->delim, c));
}

bool	msh_ast_lexer_is_delim(t_ast_lexer *state, const char c)
{
	if (c == 0 && state->delim != NULL)
		return (false);
	if (!state->delim)
		return (c == 0);
	return (ft_strchr(state->delim, c));
}
