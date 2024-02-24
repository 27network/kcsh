/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:20:10 by kiroussa          #+#    #+#             */
/*   Updated: 2024/02/24 05:21:18 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYSTEM_H
# define SYSTEM_H

# include <msh/minishell.h>

char	*msh_get_hostname(t_minishell *msh);

int		msh_fileno(FILE	*stream);
bool	msh_is_interactive(void);

#endif // SYSTEM_H
