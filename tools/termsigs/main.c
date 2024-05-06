/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 20:14:46 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/06 20:44:13 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

static void	segfault(void)
{
	char	*ptr;

	ptr = NULL;
	*ptr = 42;
}

static void	fpe(void)
{
	int	res;

	res = 1 / 0;
	printf("Result: %d\n", res);
}

static void	term(void)
{
	raise(SIGTERM);
}

static void	quit(void)
{
	raise(SIGQUIT);
}

static void	sigint(void)
{
	raise(SIGINT);
}

static void	killed(void)
{
	raise(SIGKILL);
}

int	main(int argc, char **argv)
{
	static void	(*func)(void) = NULL;

	if (argc == 1 || argc >= 3)
	{
		fprintf(stderr, "Usage: %s <type>\n", argv[0]);
		fprintf(stderr, "Available types: kill, term, quit, int, segfault, fpe, abort\n");
		return (1);
	}
	if (strcmp(argv[1], "segfault") == 0)
		func = segfault;
	else if (strcmp(argv[1], "fpe") == 0)
		func = fpe;
	else if (strcmp(argv[1], "abort") == 0)
		func = abort;
	else if (strcmp(argv[1], "term") == 0)
		func = term;
	else if (strcmp(argv[1], "quit") == 0)
		func = quit;
	else if (strcmp(argv[1], "int") == 0)
		func = sigint;
	else if (strcmp(argv[1], "kill") == 0)
		func = killed;
	else
	{
		fprintf(stderr, "Invalid type\n");
		return (1);
	}
	printf("Running \"%s\"...\n", argv[1]);
	func();
	while (1)
		;
	return (1);
}
