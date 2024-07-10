/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:07:41 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/10 14:41:13 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/builtin.h>
#include <msh/env.h>
#include <msh/log.h>
#include <msh/util.h>
#include <stdio.h>

static size_t	msh_variable_flags(t_minishell *msh, t_variable *var,
					char *flags)
{
	size_t	nflags;

	nflags = 0;
	if (var->flags & ENV_ARRAY)
		flags[nflags++] = 'a';
	if (var->flags & ENV_ASSOC)
		flags[nflags++] = 'A';
	if (var->flags & ENV_FUNCTION)
		flags[nflags++] = 'f';
	if (!msh->flags.posix)
	{
		if (var->flags & ENV_INTEGER)
			flags[nflags++] = 'i';
		if (var->flags & ENV_READONLY)
			flags[nflags++] = 'r';
		if (var->flags & ENV_EXPORTED)
			flags[nflags++] = 'x';
	}
	flags[nflags] = 0;
	return (nflags);
}

static void	msh_print_export_declaration(t_minishell *msh, char *argv0,
				t_variable *var)
{
	char	flags[32];
	size_t	nflags;

	nflags = msh_variable_flags(msh, var, flags);
	if (!msh->flags.posix)
		printf("declare -%s ", flags);
	else if (nflags)
		printf("%s -%s ", argv0, flags);
	else if (!ft_strcmp(argv0, "declare"))
		printf("%s -- ", argv0);
	else
		printf("%s ", argv0);
	msh_env_print_assignment(msh, var, QUOTING_ESCAPE_QUOTES);
	printf("\n");
}

void	msh_export_print(t_minishell *msh, char *argv0)
{
	t_variable	*root;
	t_variable	*tmp;
	bool		dealloc;

	root = msh_env_sorted(msh);
	if (!root)
		msh_error(msh, "msh_export_print: msh_env_sorted failed, "
			"printing unsorted\n");
	dealloc = !!root;
	if (!root)
		root = msh->variables;
	while (root)
	{
		if ((root->flags & ENV_EXPORTED) && !(root->flags & ENV_INVISIBLE))
			msh_print_export_declaration(msh, argv0, root);
		tmp = root;
		root = root->next;
		if (dealloc)
			msh_env_free(tmp);
	}
}
