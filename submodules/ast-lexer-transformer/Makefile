# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 07:00:21 by kiroussa          #+#    #+#              #
#    Updated: 2024/08/21 17:42:26 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ast-lexer-transformer
DEPS		=	ast-builder ast-lexer

include ../common-prelude.mk

SRC			=	merge/redir/msh_ast_merge_fdtoredir.c \
				merge/redir/msh_ast_merge_late_redirtostring.c \
				merge/redir/msh_ast_merge_redirtosep.c \
				merge/string/msh_ast_merge_strtostr.c \
				merge/string/msh_ast_merge_strtow.c \
				merge/string/msh_ast_merge_wtostr.c \
				merge/string/msh_ast_merge_wtow.c \
				msh_ast_transform.c \
				msh_ast_transform_merge.c \
				msh_ast_transform_merge_late.c \
				msh_ast_transform_standardize.c \
				msh_ast_transform_wordify.c

include ../common.mk
