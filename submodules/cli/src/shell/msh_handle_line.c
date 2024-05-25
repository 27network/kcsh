/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_handle_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 05:22:17 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/25 09:34:35 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/ast/lexer.h>
#include <msh/cli/shell.h>
#include <msh/exec/exec.h>
#include <msh/env.h>
#include <stdio.h>
#include <readline/history.h>
#include <stdlib.h>

static t_list	*msh_build_ast_tokens(t_minishell *msh, char *line)
{
	t_ast_lexer	lexer;
	t_ast_error	err;
	char		*prompt;

	prompt = msh_env_value(msh, "PS2");
	if (!prompt || !*prompt)
		prompt = ENV_DEFAULT_PS2;
	msh_ast_lexer_init(&lexer, msh, line);
	err = msh_ast_tokenize(&lexer);
	while (err.retry)
	{
		lexer.input = msh_input(prompt);
		err = msh_ast_tokenize(&lexer);
	}
	if (err.type != AST_ERROR_NONE)
	{
		msh_ast_error_print(msh, err);
		if (lexer.tokens)
			ft_lst_free(&lexer.tokens, free);
		return (NULL);
	}
	return (lexer.tokens);
}

static void	msh_debug_exec(t_minishell *msh, char *line)
{
	char	**array;
	size_t	i;
	int		ret;

	array = ft_splits(line, " \t\n");
	if (!array)
		return ;
	ret = msh_exec_simple(msh, array);
	msh->execution_context.exit_code = ret;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	msh_handle_line(t_minishell *msh, char *line)
{
	msh_handle_ast(msh, line);
	if (*line && msh->interactive)
		add_history(line);
	msh_debug_exec(msh, line);
}
