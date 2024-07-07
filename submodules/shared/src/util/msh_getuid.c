/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_getuid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 01:14:58 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/07 02:06:27 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/features.h>
#include <msh/minishell.h>
#if FEAT_SYSCALLS
# include <unistd.h>
#endif

int	msh_uid(t_minishell *msh, bool real);

int	msh_getuid_internal(t_minishell *msh)
{
	return (msh_uid(msh, true));
}

#if !FEAT_SYSCALLS
# define TARGET msh_getuid_internal
#else
# define TARGET msh_getuid_syscall

int	msh_getuid_syscall(t_minishell *msh)
{
	int	id;

	id = getuid();
	if (id == -1)
		return (msh_getuid_internal(msh));
	return (id);
}

#endif // !FEAT_SYSCALLS

int	msh_getuid(t_minishell *msh)
{
	return (TARGET(msh));
}
