/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_getpwuid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 21:25:43 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/05 15:48:58 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/util.h>

struct passwd	msh_getpw_for(t_minishell *msh, uid_t uid, const char *name);

struct passwd	msh_getpwuid(t_minishell *msh, uid_t uid)
{
	return (msh_getpw_for(msh, uid, NULL));
}
