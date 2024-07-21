/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_is_interactive.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 05:02:54 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/21 17:50:18 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/features.h>
#include <msh/util.h>
#include <unistd.h>

#if !FEAT_NO_READLINE
# include <readline/readline.h>

static void	fdprovider(int *in, int *err)
{
	*in = STDIN_FILENO;
	*err = STDERR_FILENO;
	if (rl_instream)
		*in = msh_fileno(rl_instream);
	if (rl_outstream)
		*err = msh_fileno(rl_outstream);
}

#else

static void	fdprovider(int *in, int *err)
{
	*in = msh_fileno(stdin);
	*err = msh_fileno(stderr);
}

#endif // !FEAT_NO_READLINE

bool	msh_is_interactive(t_minishell *msh)
{
	int	in;
	int	err;

	if (msh->flags.force_interactive)
		return (true);
	if (msh->execution_context.show_line)
		return (false);
	fdprovider(&in, &err);
	return (isatty(in) && isatty(err));
}
