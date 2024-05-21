/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_handle_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 05:22:17 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/21 15:57:18 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/ast/tokenizer.h>
#include <msh/cli/shell.h>
#include <msh/exec/exec.h>
#include <stdio.h>
#include <readline/history.h>
#include <stdlib.h>

static void	msh_handle_ast(t_minishell *msh, char *line)
{
	t_list	*tokens;

	tokens = msh_ast_tokenize(line);
	if (!tokens)
		return ;
	if (*line && msh->interactive)
		add_history(line);
	if (msh->flags.print_tokens)
		printf("\nFinal token list:\n");
	if (msh->flags.print_tokens)
		ft_lst_foreach(tokens, (void (*)(void *)) & msh_ast_tkn_print);
	ft_lst_free(&tokens, (t_lst_dealloc) & msh_ast_tkn_free);
}

static void	msh_debug_exec(t_minishell *msh, char *line)
{
	char	**array;
	size_t	i;
	int		ret;

	array = ft_splits(line, " \t\n");
	if (!array)
		return (-1);
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
	// msh_debug_exec(msh, line);
}
