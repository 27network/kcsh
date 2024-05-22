/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 19:02:35 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/22 19:17:05 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPT_H
# define OPT_H
# undef OPT_H
# ifndef __FT_OPT_H__
#  define __FT_OPT_H__

#  include <stdbool.h>

typedef struct s_opt_globals
{
	char	*optarg;
	int		optind;
	int		optopt;
	int		opterr;
}	t_opt_globals;

t_opt_globals	*ft_opt_globals(void);
void			ft_resetopt(void);

#  define G_OPT ft_opt_globals

typedef struct s_opt_args
{
	int			argc;
	char		**argv;
	char		**envp;
	const char	*optstring;
}	t_opt_args;

t_opt_args		ft_opt_args(int argc, char **argv, char **envp,
					const char *optstring);

# endif // __FT_OPT_H__
#endif // OPT_H
