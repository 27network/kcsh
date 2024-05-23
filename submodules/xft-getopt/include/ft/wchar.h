/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wchar.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 23:30:09 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/23 00:13:26 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WCHAR_H
# define WCHAR_H
# undef WCHAR_H
# ifndef __FT_WCHAR_H__
#  define __FT_WCHAR_H__

#  include <wchar.h>

int		ft_mbtowc(wchar_t *pwc, const char *s, size_t n);

# endif // __FT_WCHAR_H__
#endif // WCHAR_H
