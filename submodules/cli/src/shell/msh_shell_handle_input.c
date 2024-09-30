/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_shell_handle_input.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 05:22:17 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/30 09:25:40 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/ast/builder.h>
#include <msh/cli/history.h>
#include <msh/cli/input.h>
#include <msh/cli/shell.h>
#include <msh/exec.h>
#include <msh/env.h>
#include <msh/log.h>
#include <stdio.h>
#include <stdlib.h>

void	msh_handle_history(t_input_result input, bool should_pop)
{
	size_t	size;
	bool	change;

	if (input.type != INPUT_OK)
		return ;
	if (!input.buffer || !*input.buffer)
		return ;
	size = ft_strlen(input.buffer);
	change = (size && input.buffer[size - 1] == '\n');
	if (change)
		input.buffer[size - 1] = 0;
	if (should_pop)
		msh_history_modify_last(input.buffer);
	else
		msh_history_push(input.buffer);
	if (change)
		input.buffer[size - 1] = '\n';
}

static bool	msh_handle_ast(t_minishell *msh, t_input_result input,
				t_ast_node **result, bool *res)
{
	t_list	*tokens;
	char	*prompt;
	char	*line;

	line = ft_strdup(input.buffer);
	if (!line)
		msh_error(msh, "allocation error while duplicating input\n");
	if (!line)
		return (false);
	input.buffer = line;
	msh_env_set_if_not(msh, "PS2", ENV_DEFAULT_PS2, 0);
	prompt = msh_env_value(msh, "PS2");
	if (!prompt || !*prompt)
		prompt = ENV_DEFAULT_PS2;
	*result = NULL;
	if (!msh_ast_lex(msh, input, prompt, &tokens))
		return (false);
	*res = (tokens == NULL);
	msh_dump_tokens(msh, tokens);
	if (!*res && !msh_ast_create(msh, tokens, result))
		ft_lst_free(&tokens, (t_lst_dealloc) msh_ast_token_free);
	if (*result && msh->flags.debug_ast)
		msh_ast_node_print(msh, *result);
	return (*result != NULL);
}

static void	msh_takeoff(t_minishell *msh, t_input_result input)
{
	t_ast_node	*ast;
	bool		ast_ok;
	bool		ret;

	ret = false;
	ast_ok = msh_handle_ast(msh, input, &ast, &ret);
	ft_strdel((char **) &input.buffer);
	if (ret)
		return ;
	if (ast_ok && !msh->forked)
	{
		if (msh_exec_wrap(msh, ast))
			msh->execution_context.exit_code = 1;
		msh_ast_node_free(ast);
	}
	else
		msh->execution_context.exit_code = 1;
}

void	msh_shell_handle_input(t_minishell *msh, t_input_result input)
{
	if (input.type == INPUT_ERROR)
	{
		ft_strdel((char **) &input.buffer);
		msh->execution_context.exit_code = 1;
		msh_error(msh, "error while reading input\n");
	}
	if (!input.buffer || !*input.buffer || !ft_strcmp(input.buffer, "\n"))
		ft_strdel((char **) &input.buffer);
	if (!input.buffer || !*input.buffer || !ft_strcmp(input.buffer, "\n"))
		return ;
	msh_handle_history(input, false);
	msh_takeoff(msh, input);
}
