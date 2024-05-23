/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mbtowc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 23:29:53 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/22 23:32:02 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/wchar.h>

//TODO: actual widechar support
int	ft_mbtowc(wchar_t *pwc, const char *s, size_t n)
{
	if (!n)
		return (-1);
	if (pwc)
		*pwc = (unsigned char) *s;
	return (!!*s);
}
