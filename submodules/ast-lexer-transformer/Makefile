# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 07:00:21 by kiroussa          #+#    #+#              #
#    Updated: 2024/10/09 01:55:35 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ast-lexer-transformer
DEPS		=	ast-builder ast-lexer ast-lexer-sanitizer

include ../common-prelude.mk

SRC			=	merge/pattern/msh_ast_merge_pattopat.c \
				merge/pattern/msh_ast_merge_pattostr.c \
				merge/pattern/msh_ast_merge_strtopat.c \
				merge/redir/msh_ast_merge_fdtoredir.c \
				merge/sep/msh_ast_merge_septosep.c \
				merge/string/msh_ast_merge_strtostr.c \
				merge/string/msh_ast_merge_strtow.c \
				merge/string/msh_ast_merge_wtostr.c \
				merge/string/msh_ast_merge_wtow.c \
				merge/msh_ast_token_is_subst_pattern.c \
				merge/msh_ast_transform_merge_recurse.c \
				merge/msh_ast_transform_try_merge.c \
				pattern/msh_ast_transform_pattern_build_str.c \
				pattern/msh_ast_transform_pattern_sort.c \
				pattern/msh_ast_transform_run_pattern_matching.c \
				pattern/msh_pattern_match.c \
				subst/msh_ast_transform_subst_var.c \
				msh_ast_transform.c \
				msh_ast_transform_merge.c \
				msh_ast_transform_standardize.c \
				msh_ast_transform_substitute_pattern.c \
				msh_ast_transform_substitute_tilde.c \
				msh_ast_transform_substitute_var.c \
				msh_ast_transform_wordify.c

include ../common.mk
