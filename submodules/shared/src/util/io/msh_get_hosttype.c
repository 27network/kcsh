/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_get_hosttype.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 02:17:08 by kiroussa          #+#    #+#             */
/*   Updated: 2024/09/21 13:38:16 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/print.h>
#include <ft/string.h>
#include <msh/features.h>
#include <msh/util.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

// Credit to maldavid
// START NORMINETTE CRINGE
#ifdef __x86_64__
# define DEFAULT_ARCH "x86_64"
#else
# ifdef _M_X64
#  define DEFAULT_ARCH "x86_64"
# else
#  ifdef _M_AMD64
#   define DEFAULT_ARCH "x86_64"
#  else
#   ifdef __amd64__
#    define DEFAULT_ARCH "x86_64"
#   else
#    ifdef __amd64
#     define DEFAULT_ARCH "x86_64"
#    else
#     ifdef __x86_64
#      define DEFAULT_ARCH "x86_64"
#     else
#      ifdef _X86_
#       define DEFAULT_ARCH "x86"
#      else
#       ifdef i386
#        define DEFAULT_ARCH "x86"
#       else
#        ifdef __i386__ 
#         define DEFAULT_ARCH "x86"
#        else
#         ifdef __i386
#          define DEFAULT_ARCH "x86"
#         else
#          ifdef _M_IX86
#           define DEFAULT_ARCH "x86"
#          else
#           ifdef __aarch64__
#            define DEFAULT_ARCH "aarch64"
#           else
#            ifdef _M_ARM64
#             define DEFAULT_ARCH "aarch64"
#            else
#             ifdef __arm64__
#              define DEFAULT_ARCH "aarch64"
#             else
#              ifdef __arm__
#               define DEFAULT_ARCH "arm"
#              else
#               ifdef __arm
#                define DEFAULT_ARCH "arm"
#               else
#                ifdef mips
#                 define DEFAULT_ARCH "mips"
#                else
#                 ifdef __mips__
#                  define DEFAULT_ARCH "mips"
#                 else
#                  ifdef __mips
#                   define DEFAULT_ARCH "mips"
#                  else
#                   ifdef __sh__
#                    define DEFAULT_ARCH "superh"
#                   else
#                    ifdef __powerpc
#                     define DEFAULT_ARCH "powerpc"
#                    else
#                     ifdef __powerpc__
#                      define DEFAULT_ARCH "powerpc"
#                     else
#                      ifdef _ARCH_PPC
#                       define DEFAULT_ARCH "powerpc"
#                      else
#                       ifdef __POWERPC__
#                        define DEFAULT_ARCH "powerpc"
#                       else
#                        ifdef __ppc__
#                         define DEFAULT_ARCH "powerpc"
#                        else
#                         ifdef __PPC__
#                          define DEFAULT_ARCH "powerpc"
#                         else
#                          ifdef __powerpc64__
#                           define DEFAULT_ARCH "powerpc64"
#                          else
#                           ifdef __PPC64__
#                            define DEFAULT_ARCH "powerpc64"
#                           else
#                            ifdef __ppc64__
#                             define DEFAULT_ARCH "powerpc64"
#                            else
#                             ifdef _ARCH_PPC64
#                              define DEFAULT_ARCH "powerpc64"
#                             else
#                              ifdef __sparc__
#                               define DEFAULT_ARCH "sparc"
#                              else
#                               ifdef __sparc
#                                define DEFAULT_ARCH "sparc"
#                               else
#                                ifdef __m68k__
#                                 define DEFAULT_ARCH "m68k"
#                                else
#                                 define DEFAULT_ARCH "unknown"
#                                endif
#                               endif
#                              endif
#                             endif
#                            endif
#                           endif
#                          endif
#                         endif
#                        endif
#                       endif
#                      endif
#                     endif
#                    endif
#                   endif
#                  endif
#                 endif
#                endif
#               endif
#              endif
#             endif
#            endif
#           endif
#          endif
#         endif
#        endif
#       endif
#      endif
#     endif
#    endif
#   endif
#  endif
# endif
#endif
// END NORMINETTE CRINGE

#if FEAT_SYSCALLS
# include <sys/utsname.h>
#endif // FEAT_SYSCALLS

char	*msh_resolve_path_internal(t_minishell *msh, const char *filename);

static int	msh_get_hosttype_exec(t_minishell *msh, char **args, int fds[2],
				char *result)
{
	pid_t	pid;
	int		status;

	pid = msh_fork(msh);
	if (pid == -1)
		return (0);
	if (pid == 0)
	{
		dup2(fds[1], 1);
		close(fds[0]);
		close(fds[1]);
		execve(args[0], args, NULL);
		free(args[0]);
		ft_putstr(DEFAULT_ARCH);
		msh_exit(msh, 1);
		return (0);
	}
	waitpid(pid, &status, 0);
	if (read(fds[0], result, 1024) <= 0)
		return (0);
	return (1);
}

char	*msh_gethosttype(t_minishell *msh)
{
	char	*path;
	int		fds[2];
	char	result[1024];

	path = msh_resolve_path_internal(msh, "uname");
	if (!path)
		return (ft_strdup(DEFAULT_ARCH));
	if (pipe(fds) == -1)
	{
		free(path);
		return (ft_strdup(DEFAULT_ARCH));
	}
	ft_bzero(result, 1024);
	if (path && !msh_get_hosttype_exec(msh, (char *[]){path, "-m", NULL},
		fds, result))
		ft_strcpy(result, DEFAULT_ARCH);
	close(fds[0]);
	close(fds[1]);
	if (path)
		free(path);
	return (ft_strdup(result));
}

char	*msh_get_hosttype_internal(t_minishell *msh)
{
	return (msh_gethosttype(msh));
}

#if !FEAT_SYSCALLS
# define TARGET msh_get_hosttype_internal
#else
# define TARGET msh_get_hosttype_syscall

char	*msh_get_hosttype_syscall(t_minishell *msh)
{
	struct utsname	uts;
	char			*name;

	if (uname(&uts) != -1)
	{
		if (*uts.machine)
		{
			name = ft_strdup(uts.machine);
			if (name)
				return (name);
		}
	}
	return (msh_get_hosttype_internal(msh));
}

#endif // !FEAT_SYSCALLS

char	*msh_get_hosttype(t_minishell *msh)
{
	return (TARGET(msh));
}
