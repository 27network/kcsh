# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebouchet <ebouchet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 06:49:07 by kiroussa          #+#    #+#              #
#    Updated: 2024/10/01 18:01:56 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	builtins
DEPS		=	shared

include ../common-prelude.mk

SRC			=	42sh/jobs/bg.c \
				42sh/jobs/fg.c \
				42sh/jobs/jobs.c \
				42sh/alias.c \
				42sh/fc.c \
				42sh/hash.c \
				42sh/set.c \
				42sh/test.c \
				42sh/type.c \
				42sh/unalias.c \
				core/msh_builtin_count.c \
				core/msh_builtin_get.c \
				core/msh_builtin_help_page.c \
				core/msh_builtin_print_help.c \
				core/msh_builtin_print_usage.c \
				core/msh_builtin_register.c \
				core/msh_builtin_registry.c \
				core/msh_builtin_registry_sort.c \
				bash/help.c \
				minishell/cd/msh_cd_absolute.c \
				minishell/cd/msh_cd_home.c \
				minishell/cd/msh_cd_oldpwd.c \
				minishell/cd/msh_cd_relative.c \
				minishell/export/msh_export_assign.c \
				minishell/export/msh_export_error.c \
				minishell/export/msh_export_print.c \
				minishell/cd.c \
				minishell/echo.c \
				minishell/env.c \
				minishell/exit.c \
				minishell/export.c \
				minishell/pwd.c \
				minishell/unset.c \
				posix/no-op.c \
				posix/times.c

include ../common.mk
