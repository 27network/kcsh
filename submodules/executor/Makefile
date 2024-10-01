# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 07:00:21 by kiroussa          #+#    #+#              #
#    Updated: 2024/10/01 18:01:11 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	executor
DEPS		=	ast-builder ast-lexer-transformer builtins

include ../common-prelude.mk

SRC			=	extra/msh_exec_simple.c \
				extra/msh_exec_status.c \
				types/command/msh_exec_command_heredoc_expand.c \
				types/command/msh_exec_command_not_builtin.c \
				types/command/msh_exec_command_redirect_setup.c \
				types/command/msh_exec_command_redirections.c \
				types/command/msh_exec_command_setup_fds.c \
				types/msh_exec_command.c \
				types/msh_exec_delim.c \
				types/msh_exec_group.c \
				types/msh_exec_pipe.c \
				msh_exec_entry.c

include ../common.mk
