# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 07:00:21 by kiroussa          #+#    #+#              #
#    Updated: 2024/09/26 00:50:57 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ast-lexer-transformer
DEPS		=	ast-builder ast-lexer ast-lexer-sanitizer

include ../common-prelude.mk

SRC			=	merge/redir/msh_ast_merge_fdtoredir.c \
				merge/redir/msh_ast_merge_redirtosep.c \
				merge/redir/msh_ast_merge_redirtostring.c \
				merge/string/msh_ast_merge_strtostr.c \
				merge/string/msh_ast_merge_strtow.c \
				merge/string/msh_ast_merge_wtostr.c \
				merge/string/msh_ast_merge_wtow.c \
				merge/msh_ast_merge_septosep.c \
				subst/msh_ast_transform_subst_var.c \
				msh_ast_transform.c \
				msh_ast_transform_merge.c \
				msh_ast_transform_standardize.c \
				msh_ast_transform_substitute.c \
				msh_ast_transform_wordify.c

include ../common.mk
