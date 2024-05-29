/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_input_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 00:23:25 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/30 00:24:48 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/cli/input.h>

const char	*msh_input_type(t_input_result_type type)
{
	static const char	*types[] = {
	[INPUT_OK] = "OK",
	[INPUT_EOF] = "EOF",
	[INPUT_ERROR] = "ERROR",
	[INPUT_IGNORED] = "IGNORED",
	[INPUT_INTERRUPTED] = "INTERRUPTED",
	};

	if (type < 0 || type >= _INPUT_RESULT_COUNT)
		return ("unknown type");
	return (types[type]);
}
