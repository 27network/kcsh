/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shk_input_bind.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:09:29 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/02 16:28:49 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <shakespeare.h>

#define BIND_CAPACITY_GROWTH 32

static bool	shk_grow_binds(t_shakespeare_data *shk)
{
	t_shk_input_bind	*new_binds;
	size_t				new_size;
	size_t				old_size;

	old_size = shk->input.binds_capacity;
	new_size = old_size + BIND_CAPACITY_GROWTH;
	old_size *= sizeof(t_shk_input_bind);
	new_size *= sizeof(t_shk_input_bind);
	shk->input.binds = ft_realloc(shk->input.binds, old_size, new_size);
	return (!!shk->input.binds);
}

void	shk_input_bind(t_shakespeare_data *shk, int mode_flag, const char *key,
			t_shk_input_action *func)
{
	t_shk_input_bind	*bind;

	bind = shk_create_bind(mode_flag, key, func);
	if (!bind)
		ft_putstr_fd("shk_input_bind: failed to alloc bind\n", STDERR_FILENO);
	if (!bind)
		return ;
	if (shk->input.binds_capacity == shk->inputs.binds_size)
	{
		if (!shk_grow_binds(shk))
		{
			free(bind);
			return ;
		}
	}
	shk->input.bindings[shk->input.binds_size++] = bind;
}
