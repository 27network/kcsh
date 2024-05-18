/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _wip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:23:04 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/17 04:04:17 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/builtin.h>
#define WIP_BUILTINS "job_spec\0\
.\0\
[\0\
[[\0\
alias\0\
bg\0\
break\0\
builtin\0\
caller\0\
case\0\
command\0\
continue\0\
coproc\0\
declare\0\
dirs\0\
disown\0\
enable\0\
eval\0\
exec\0\
fc\0\
fg\0\
for\0\
for2idk\0\
function\0\
getopts\0\
hash\0\
history\0\
if\0\
jobs\0\
kill\0\
let\0\
local\0\
logout\0\
mapfile\0\
popd\0\
printf\0\
pushd\0\
read\0\
readarray\0\
readonly\0\
return\0\
select\0\
set\0\
shift\0\
shopt\0\
source\0\
suspend\0\
test\0\
time\0\
times\0\
trap\0\
type\0\
typeset\0\
ulimit\0\
umask\0\
unalias\0\
unset\0\
until\0\
variables\0\
wait\0\
while\0\
{\0\0"

static int	msh_builtin_not_implemented(
	ATTR((unused)) int argc,
	ATTR((unused)) char **argv,
	t_minishell *msh
) {
	msh_error(msh, "%s: this builtin is not implemented yet.\n", argv[0]);
	return (1);
}

// Using __attribute__ instead of ATTR here because the norminette either
// crashes or breaks horribly. Understandably so, but still, lol.
__attribute__((constructor))
void	msh_register_wip_builtins(void)
{
	const char	*string = WIP_BUILTINS;
	const char	*name;
	size_t		i;

	i = 0;
	while (string[i])
	{
		name = string + i;
		msh_builtin_register((t_builtin){
			.name = name,
			.help = "Unimplemented builtin",
			.usage = "Unimplemented builtin",
			.func = msh_builtin_not_implemented,
			.needs = NEEDS_MSH,
			.enabled = false,
		});
		i += ft_strlen(string + i) + 1;
	}
}
