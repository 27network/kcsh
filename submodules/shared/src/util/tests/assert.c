/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 02:01:35 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/23 02:32:13 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <ft/colors.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void	assert(
	bool condition,
	const char *file_name,
	const char *message
) {
	char	*submodule;

	if (condition)
		return ;
	submodule = NULL;
	if (!file_name || !*file_name)
		file_name = "<unknown>";
	else
	{
		file_name = ft_strstr(file_name, "submodules/");
		file_name += ft_strlen("submodules/");
		submodule = ft_strdup_range(file_name, 0, ft_strchr(file_name, '/')
				- file_name - 1);
		if (!submodule)
			return ;
		file_name = ft_strchr(file_name, '/') + 1;
		file_name = ft_strchr(file_name, '/') + 1;
	}
	if (submodule)
		printf(BG_RED BLACK BOLD " KO " RESET " " BG_CYAN BLACK " %s " RESET " "
			BOLD "%s" RESET ": %s\n", submodule, file_name, message);
	else
		printf(BG_RED BLACK " KO " RESET " " BOLD "%s" RESET ": %s\n",
			file_name, message);
	free(submodule);
}
