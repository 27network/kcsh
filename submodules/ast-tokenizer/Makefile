# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 07:00:21 by kiroussa          #+#    #+#              #
#    Updated: 2024/04/26 20:42:51 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ast-tokenizer
DEPS		=	shared

include ../common-prelude.mk

SRC			=	types/msh_ast_tokenize_escape.c \
				types/msh_ast_tokenize_single.c \
				types/msh_ast_tokenize_string.c \
				types/msh_ast_tokenize_word.c \
				types/msh_ast_tokenize_variable.c \
				msh_ast_tkn_free.c \
				msh_ast_tkn_new.c \
				msh_ast_tkn_print.c \
				msh_ast_tkn_type.c \
				msh_ast_tokenize.c

include ../common.mk
