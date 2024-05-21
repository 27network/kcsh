/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 01:45:29 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/21 19:05:05 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/print.h>
#include <ft/string.h>
#include <msh/env.h>
#include <msh/util.h>
#include <msh/log.h>
#include <msh/minishell.h>
#include <unistd.h>

/**
 * @brief A simple hash function for strings.
 *
 * @param data The string to hash.
 * @return uint64_t The hash value.
 */
static uint64_t	msh_string_hash(void *data);

void	msh_init(
	t_minishell *msh,
	__attributes__((unused)) int argc,
	const char **argv,
	const char **envp
) {
	ft_bzero(msh, sizeof(t_minishell));
	msh->binary_name = argv[0];
	msh->name = argv[0];
	msh->interactive = msh_is_interactive();
	if (!msh_env_populate(msh, envp))
	{
		msh_error(msh, "failed to populate env");
		msh_exit(msh, -2);
	}
	msh_env_defaults(msh);
	msh->execution_context.running = true;
	msh->execution_context.line = 0;
}

static uint64_t	msh_string_hash(void *data)
{
	char		*str;
	uint64_t	hash;

	str = (char *) data;
	hash = 5381;
	while (*str)
	{
		hash = ((hash << 5) + hash) + *str;
		str++;
	}
	return (hash);
}
