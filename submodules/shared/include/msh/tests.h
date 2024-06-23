/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 01:55:52 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/23 02:08:39 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H
# undef TESTS_H
# ifdef KCSH_TESTS
#  ifndef __MSH_TESTS_H__
#   define __MSH_TESTS_H__

#   include <stdbool.h>

void	assert(bool condition,
			const char *file_name, const char *problem);
void	assert_eq(int a, int b,
			const char *file_name, const char *problem);
void	assert_neq(int a, int b,
			const char *file_name, const char *problem);
void	assert_strs(const char *a, const char *b,
			const char *file_name, const char *problem);

#  endif // __MSH_TESTS_H__
# endif // KCSH_TESTS
#endif // TESTS_H
