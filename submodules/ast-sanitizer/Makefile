# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 07:00:21 by kiroussa          #+#    #+#              #
#    Updated: 2024/07/22 17:58:46 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ast-sanitizer
DEPS		=	ast-lexer

include ../common-prelude.mk

SRC			=	merge/redir/msh_ast_merge_fdtoredir.c \
				merge/redir/msh_ast_merge_septoredir.c \
				merge/string/msh_ast_merge_strtostr.c \
				merge/string/msh_ast_merge_strtow.c \
				merge/string/msh_ast_merge_wtostr.c \
				merge/string/msh_ast_merge_wtow.c \
				msh_ast_sanitize.c \
				msh_ast_sanitize_check.c \
				msh_ast_sanitize_merge.c \
				msh_ast_sanitize_standardize.c \
				msh_ast_sanitize_wordify.c \
				msh_ast_sanitize_simple.c

include ../common.mk
