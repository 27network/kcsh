/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_is_valid_name.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 22:13:45 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/28 16:47:49 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/env.h>
#include <msh/tests.h>

static bool	msh_env_is_valid_name_char(char c)
{
	return (c == '_' || ft_isalnum(c));
}

static bool	msh_has_valid_chars(const char *name)
{
	while (*name)
	{
		if (!msh_env_is_valid_name_char(*name))
			return (false);
		name++;
	}
	return (true);
}

bool	msh_env_is_valid_name(const char *name, bool assignment)
{
	if (!name || !*name)
		return (false);
	if (*name == '=')
		return (false);
	if (msh_env_is_special_name_starter(*name))
	{
		if (assignment)
			return (false);
		return (!name[1]);
	}
	if (!msh_env_is_valid_name_starter(*name))
		return (false);
	name++;
	return (msh_has_valid_chars(name));
}

#ifdef KCSH_TESTS
# define TARGET msh_env_is_valid_name

__attribute__((constructor))
void	msh_env_is_valid_name_test(void)
{
	assert(TARGET("HOME", false), __FILE__, "HOME isn't a valid name");
	assert(TARGET("HOME", true), __FILE__, "HOME isn't a valid name (assign)");
	assert(TARGET("?", false), __FILE__, "? isn't a valid name");
	assert(!TARGET("?", true), __FILE__, "? is a valid name (assign)");
	assert(!TARGET("1", true), __FILE__, "1 is a valid name (assign)");
	assert(TARGET("_", true), __FILE__, "_ isn't a valid name (assign)");
	assert(TARGET("_", true), __FILE__, "_ it a valid name (assign)");
	assert(!TARGET("=", false), __FILE__, "= is a valid name");
	assert(!TARGET("1SALUT", false), __FILE__, "1SALUT is a valid name");
	assert(!TARGET("1SALUT", true), __FILE__,
		"1SALUT is a valid name (assign)");
	if (FEAT_SCRIPTING)
	{
		assert(TARGET("1", false), __FILE__,
			"1 isn't a valid name (FEAT_SCRIPTING)");
		assert(!TARGET("11", false), __FILE__,
			"11 is a valid name (FEAT_SCRIPTING)");
	}
	else
		assert(!TARGET("1", false), __FILE__,
			"1 is a valid name (!FEAT_SCRIPTING)");
}

#endif
