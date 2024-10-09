/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pattern_match.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 22:12:57 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/09 01:54:43 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <errno.h>
#include <ft/mem.h>
#include <ft/string.h>
#include <msh/ast/transformer.h>
#include <stdlib.h>
#include <string.h>

void	msh_ast_transform_pattern_sort(t_minishell *msh, t_list **matches);

static bool	msh_pattern_match_check(const char *pattern, const char *candidate,
				size_t p, size_t c)
{
	if (pattern[p] == '\0')
		return (candidate[c] == '\0');
	else if (pattern[p] == '\\')
		return (pattern[p + 1] == candidate[c]
			&& msh_pattern_match_check(pattern, candidate, p + 2, c + 1));
	else if (pattern[p] == '*')
	{
		while (candidate[c] != '\0')
		{
			if (msh_pattern_match_check(pattern, candidate, p + 1, c))
				return (true);
			c++;
		}
		return (msh_pattern_match_check(pattern, candidate, p + 1, c));
	}
	else if (pattern[p] != '?' && pattern[p] != candidate[c])
		return (false);
	return (msh_pattern_match_check(pattern, candidate, p + 1, c + 1));
}

static t_ast_error	msh_pattern_check(const char *pattern,
				const char *candidate, const char *cwd, t_list **match_stack)
{
	t_ast_error	err;
	char		*path;

	err = msh_ast_ok();
	if (msh_pattern_match_check(pattern, candidate, 0, 0))
	{
		if (cwd)
			path = ft_strjoins(2, "/", 0, cwd, candidate);
		else
			path = ft_strdup(candidate);
		if (!path || !ft_lst_tadd(match_stack, path))
			err = msh_ast_errd(AST_ERROR_ALLOC, NULL, false);
	}
	return (err);
}

static t_ast_error	msh_pattern_match_readdir(const char *cwd, const char *part,
						t_list **match_stack)
{
	t_ast_error		err;
	DIR				*dir;
	struct dirent	*ent;

	if (cwd)
		dir = opendir(cwd);
	else
		dir = opendir(".");
	err = msh_ast_ok();
	while (dir && !err.type)
	{
		errno = 0;
		ent = readdir(dir);
		if (errno)
			err = msh_ast_errd(AST_ERROR_SYSTEM, strerror(errno), false);
		if (!ent || errno)
			break ;
		if (ent->d_name[0] == '.' && part[0] != '.')
			continue ;
		err = msh_pattern_check(part, ent->d_name, cwd, match_stack);
	}
	if (dir)
		closedir(dir);
	return (err);
}

static t_ast_error	msh_pattern_match_part(const char *part,
						t_list **match_stack)
{
	t_ast_error	err;
	t_list		*curr_stack;
	t_list		*new_stack;
	t_list		*buffer;

	new_stack = NULL;
	curr_stack = *match_stack;
	err = msh_ast_ok();
	while (curr_stack)
	{
		buffer = curr_stack;
		if (!err.type)
			err = msh_pattern_match_readdir(buffer->content, part, &new_stack);
		curr_stack = curr_stack->next;
		ft_lst_delete(buffer, (t_lst_dealloc) free);
	}
	if (err.type)
		ft_lst_free(&new_stack, (t_lst_dealloc) free);
	else
		*match_stack = new_stack;
	return (err);
}

t_ast_error	msh_pattern_match(t_minishell *msh, const char *pattern,
				t_list **match_stack)
{
	const char	**paths = (const char **) ft_split(pattern, '/');
	size_t		i;
	t_ast_error	err;

	if (!paths)
		return (msh_ast_errd(AST_ERROR_ALLOC, NULL, false));
	i = 0;
	err = msh_ast_ok();
	while (paths[i])
	{
		if (!err.type)
			err = msh_pattern_match_part(paths[i], match_stack);
		if (!err.type)
			msh_ast_transform_pattern_sort(msh, match_stack);
		ft_strdel((char **) paths + i);
		i++;
	}
	free((char *) paths);
	return (err);
}
