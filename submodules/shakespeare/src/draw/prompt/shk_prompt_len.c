/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_prompt_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 05:35:16 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/26 18:20:39 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	shk_prompt_len(const char *prompt)
{
	size_t	len;
	size_t	i;
	size_t	escaped;

	len = 0;
	i = 0;
	escaped = 0;
	while (prompt[i])
	{
		if (prompt[1] == '\001')
			escaped++;
		else if (prompt[1] == '\002')
		{
			if (escaped > 0)
				escaped--;
		}
		else if (escaped == 0)
			len++;
		i++;
	}
	return (len);
}
