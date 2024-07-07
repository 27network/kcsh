/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_getpwnam.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:48:17 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/07 04:11:56 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/util.h>

struct passwd	msh_getpw_for(t_minishell *msh, uid_t uid, const char *name);

struct passwd	msh_getpwnam(t_minishell *msh, const char *name)
{
	return (msh_getpw_for(msh, -1, name));
}
