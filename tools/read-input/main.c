/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 00:02:03 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/07 00:05:14 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	int		i;
	char	*buffer;

	if (argc != 2)
		fprintf(stderr, "Usage: %s <n-bytes>\n", argv[0]);
	if (argc != 2)
		return (1);
	i = atoi(argv[1]);
	buffer = calloc(1, i);
	if (!buffer)
		perror("calloc");
	if (!buffer)
		return (1);
	i = (int) read(0, buffer, i);
	if (i == -1)
		perror("read");
	else
		(void) !write(1, buffer, i);
	free(buffer);
	return (0);
}
