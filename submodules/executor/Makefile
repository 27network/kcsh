# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 07:00:21 by kiroussa          #+#    #+#              #
#    Updated: 2024/09/10 07:33:21 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	executor
DEPS		=	ast-builder ast-lexer-transformer builtins

include ../common-prelude.mk

SRC			=	extra/msh_exec_simple.c \
				extra/msh_exec_status.c \
				types/msh_exec_command.c \
				types/msh_exec_delim.c \
				types/msh_exec_pipe.c \
				msh_exec_entry.c

include ../common.mk
