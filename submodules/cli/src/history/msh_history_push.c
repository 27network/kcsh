/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_history_push.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 21:08:42 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/28 21:13:29 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/cli/history.h>
#include <stdio.h>
#include <readline/history.h>

void	msh_history_push(const char *line)
{
	if (!line || !*line)
		return ;
	add_history(line);
	msh_history_print();
}
