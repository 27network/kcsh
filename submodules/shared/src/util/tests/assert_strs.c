/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert_strs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 02:08:16 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/23 02:08:49 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <stdbool.h>

void	assert(bool condition, const char *file_name, const char *problem);

void	assert_strs(
	const char *a,
	const char *b,
	const char *file_name,
	const char *problem
) {
	assert(!ft_strcmp(a, b), file_name, problem);
}
