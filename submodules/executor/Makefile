# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 07:00:21 by kiroussa          #+#    #+#              #
#    Updated: 2024/05/14 18:24:08 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	executor
DEPS		=	builtins shared

include ../common-prelude.mk

SRC			=	builtin/msh_builtin_get.c \
				builtin/msh_builtin_register.c \
				builtin/msh_builtin_registry.c \
				msh_exec_simple.c \
				msh_exec_status.c

include ../common.mk
