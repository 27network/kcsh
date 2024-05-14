/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 22:54:45 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/14 17:58:18 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/builtin/defaults.h>

static int	msh_builtin_echo(
	__attribute__((unused)) int argc,
	__attribute__((unused)) char **argv
) {
	return (0);
}

__attribute__((constructor))
void	register_echo(void)
{
	msh_builtin_register((t_builtin){
		.name = "echo",
		.func = msh_builtin_echo,
	});
}
