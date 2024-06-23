/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert_neq.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 02:07:58 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/23 02:08:08 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

void	assert(bool condition, const char *file_name, const char *problem);

void	assert_neq(int a, int b, const char *file_name, const char *problem)
{
	assert(a != b, file_name, problem);
}
