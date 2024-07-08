/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 15:37:43 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/08 15:17:16 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !FEAT_SYSCALLS
# include <ft/print.h>
#endif // !FEAT_SYSCALLS
#include <msh/features.h>
#include <msh/builtin.h>

#define TIMES_HELP "Display process times.\n\
\n\
Prints the accumulated user and system times for the shell and all of its\n\
child processes.\n\
\n\
Exit Status:\n\
Always succeeds."
#define TIMES_USAGE "times"

#if FEAT_SYSCALLS
# include <stdio.h>
# include <sys/times.h>
# include <time.h>

static void	msh_clock_secs(
	clock_t t,
	time_t *sp,
	int *sfp
) {
	const static long	clk_tck = 100;

	*sfp = t % clk_tck;
	*sfp = (*sfp * 1000) / clk_tck;
	*sp = t / clk_tck;
	if (*sfp >= 1000)
	{
		*sp += 1;
		*sfp -= 1000;
	}
}

static void	msh_print_clock_t(clock_t t)
{
	time_t	timestamp;
	long	minutes;
	int		seconds;
	int		seconds_fraction;

	msh_clock_secs(t, &timestamp, &seconds_fraction);
	minutes = timestamp / 60;
	seconds = timestamp % 60;
	printf("%ldm%d%c%03ds", minutes, seconds, '.', seconds_fraction);
}

static int	msh_builtin_times(
	__attribute__((unused)) int argc,
	__attribute__((unused)) char **argv,
	__attribute__((unused)) t_minishell *msh
) {
	struct tms	tms;

	times(&tms);
	msh_print_clock_t(tms.tms_utime);
	printf(" ");
	msh_print_clock_t(tms.tms_stime);
	printf("\n");
	msh_print_clock_t(tms.tms_cutime);
	printf(" ");
	msh_print_clock_t(tms.tms_cstime);
	printf("\n");
	return (0);
}

#else

static int	msh_builtin_times(
	__attribute__((unused)) int argc,
	__attribute__((unused)) char **argv,
	t_minishell *msh
) {
	msh_error(msh, "times: not implemented\n");
	ft_printf("0.00 0.00\n0.00 0.00\n");
	return (0);
}

#endif // FEAT_SYSCALLS

__attribute__((constructor))
void	register_times(void)
{
	msh_builtin_register((t_builtin){
		.name = "times",
		.usage = TIMES_USAGE,
		.help = TIMES_HELP,
		.func = msh_builtin_times,
		.needs = NEEDS_MSH,
		.enabled = FEAT_BUILTIN_TIMES,
	});
}
