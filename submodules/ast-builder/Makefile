# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 07:00:21 by kiroussa          #+#    #+#              #
#    Updated: 2024/08/26 13:38:40 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ast-builder
DEPS		=	ast-lexer

include ../common-prelude.mk

SRC			=	node/types/msh_ast_node_command.c \
				node/types/msh_ast_node_sep.c \
				node/msh_ast_node_new.c \
				node/msh_ast_node_free.c \
				node/msh_ast_node_print.c \
				node/msh_ast_node_strtype.c \
				msh_ast_build.c

include ../common.mk
