/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_history_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 23:44:37 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/07 00:36:08 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <ft/string.h>
#include <msh/env.h>
#include <msh/features.h>
#include <stdlib.h>
#include <unistd.h>

#if FEAT_HISTORY_FILE

int	msh_history_file(t_minishell *msh, int flags)
{
	char	*path;
	int		fd;

	path = msh_env_value(msh, "HISTFILE");
	if (!path || !*path)
		return (-1);
	fd = open(path, flags, 0644);
	if (fd < 0)
		return (-1);
	return (fd);
}

#else

int	msh_history_file(
	__attribute__((unused)) t_minishell *msh,
	__attribute__((unused)) int flags
) {
	return (-1);
}

#endif // FEAT_HISTORY_FILE
