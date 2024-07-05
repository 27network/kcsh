/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_passwd_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:56:02 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/05 15:56:09 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <msh/util.h>

void	msh_passwd_free(struct passwd *pwd)
{
	if (!pwd)
		return ;
	ft_strdel(&pwd->pw_name);
	ft_strdel(&pwd->pw_passwd);
	ft_strdel(&pwd->pw_gecos);
	ft_strdel(&pwd->pw_dir);
	ft_strdel(&pwd->pw_shell);
}
