/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 19:02:35 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/23 20:20:27 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPT_H
# define OPT_H
# undef OPT_H
# ifndef __FT_OPT_H__
#  define __FT_OPT_H__

#  include <stdbool.h>
#  include <stddef.h>

/* Globals */

typedef struct s_opt_globals
{
	char	*optarg;
	int		optind;
	int		optopt;
	int		opterr;

	int		_optpos;

	char	*_optchar;
	int		_optchar_len;
}	t_opt_globals;

t_opt_globals	ft_opt_globals(void);
void			ft_opt_reset(t_opt_globals *globals);

/* Arguments */

typedef struct s_opt_args
{
	int			argc;
	char		**argv;
	bool		posix;
	const char	*optstring;
}	t_opt_args;

t_opt_args		ft_opt_args(int argc, char **argv, bool posix,
					const char *optstring);

/* getopt */

int				ft_opt_get(t_opt_globals *g_opt, t_opt_args *args);

/* getopt_long */

enum e_argument_req
{
	no_argument = 0,
	required_argument = 1,
	optional_argument = 2
};

typedef struct s_opt_option
{
	const char	*name;
	int			has_arg;
	int			*flag;
	int			val;
}	t_opt_option;

int				ft_opt_get_long(t_opt_globals *g_opt, t_opt_args *args,
					const t_opt_option *longopts, int *longindex);

#  ifdef __FT_OPT_INTERNAL__

int				ft_opt_get_posix(t_opt_globals *g_opt, t_opt_args *args);

void			ft_opt_msg(const char *a, const char *b,
					const char *c, size_t size_c);

#  endif // __FT_OPT_INTERNAL__

# endif // __FT_OPT_H__
#endif // OPT_H
