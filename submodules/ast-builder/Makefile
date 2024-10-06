# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 07:00:21 by kiroussa          #+#    #+#              #
#    Updated: 2024/10/04 03:51:30 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ast-builder
DEPS		=	ast-lexer

include ../common-prelude.mk

SRC			=	node/msh_ast_node_new.c \
				node/msh_ast_node_free.c \
				node/msh_ast_node_print.c \
				node/msh_ast_node_strtype.c \
				types/msh_ast_node_command.c \
				types/msh_ast_node_group.c \
				types/msh_ast_node_sep.c \
				msh_ast_build.c \
				msh_ast_build_root.c

include ../common.mk
