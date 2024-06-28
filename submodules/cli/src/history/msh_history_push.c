/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_history_push.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 21:08:42 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/28 20:16:35 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/features.h>
#include <msh/cli/history.h>
#if FEAT_NO_READLINE
# define TARGET shk_history_push
#else
# define TARGET add_history
#endif // FEAT_NO_READLINE

void	msh_history_push(const char *line)
{
	if (!line || !*line)
		return ;
	TARGET(line);
}
