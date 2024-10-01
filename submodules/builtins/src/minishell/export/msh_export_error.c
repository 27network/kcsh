/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:58:46 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/01 18:05:37 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/log.h>

#define UNKNOWN_ERROR -1

int	msh_export_error(t_minishell *msh, const char *data, int errtype)
{
	static const char	*error_messages[] = {
		"export: `%s': not a valid identifier\n",
		"export: name allocation error\n",
		"export: value allocation error\n",
		"export: env allocation error\n",
		"export: `%s': not a function\n",
		"%s: readonly variable\n",
	};
	const char			*message;

	if (errtype == UNKNOWN_ERROR)
		message = "export: unknown error\n";
	else
		message = error_messages[errtype - 1];
	msh_error(msh, message, data);
	return (1);
}
