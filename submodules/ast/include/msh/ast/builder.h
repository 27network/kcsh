/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 22:11:56 by kiroussa          #+#    #+#             */
/*   Updated: 2024/03/19 22:44:41 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDER_H
# define BUILDER_H

# include <msh/ast/defs.h>

t_ast_node	*msh_ast_node_new(t_ast_node_type type, void *data);
t_list		*msh_ast_build(t_list *tokens);

#endif // BUILDER_H
