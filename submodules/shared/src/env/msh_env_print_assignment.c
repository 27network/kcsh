/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_print_assignment.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 00:54:44 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/08 18:03:52 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/print.h>
#include <msh/env.h>
#include <msh/log.h>
#include <msh/util.h>

//TODO: ANSI C non-posix quoting
static void	msh_env_print_value(t_minishell *msh, t_variable *var, int quote)
{
	char	*tmp;

	if (!var->value)
		return ;
	printf("=");
	if (quote == QUOTING_ANSI_C && msh_contains_shell_metas(var->value))
	{
		tmp = msh_quote(var->value);
		if (!tmp)
			msh_error(msh, "msh_env_print_value: msh_quote failed\n");
		if (!tmp)
			return ;
		printf("%s", tmp);
		free(tmp);
	}
	else if (quote == QUOTING_ESCAPE_QUOTES)
		printf("\"%s\"", var->value);
	else
		printf("%s", var->value);
}

void	msh_env_print_assignment(t_minishell *msh, t_variable *var,
			int quote_type)
{
	printf("%s", var->name);
	if (!var->value)
		return ;
	if (var->flags & ENV_FUNCTION)
		printf(" ()\n{\n    unimplemented\n}");
	else if (var->flags & ENV_ARRAY)
		printf("unimplemented");
	else if (var->flags & ENV_ASSOC)
		printf("unimplemented");
	else
		msh_env_print_value(msh, var, quote_type);
}
