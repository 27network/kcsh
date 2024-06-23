/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_same_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 01:52:23 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/21 01:53:20 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/util.h>

bool	msh_same_file(const char *path1, const char *path2,
			struct stat *stat1, struct stat *stat2)
{
	struct stat		s1;
	struct stat		s2;

	if (stat(path1, &s1) == -1)
		return (false);
	if (stat(path2, &s2) == -1)
		return (false);
	if (stat1)
		*stat1 = s1;
	if (stat2)
		*stat2 = s2;
	return (s1.st_dev == s2.st_dev && s1.st_ino == s2.st_ino);
}
