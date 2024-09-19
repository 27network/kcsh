# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 07:00:21 by kiroussa          #+#    #+#              #
#    Updated: 2024/09/19 05:06:58 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ast-lexer-sanitizer
DEPS		=	ast-lexer ast-builder

include ../common-prelude.mk

SRC			=	ast/msh_ast_sanitize.c \
				token/impl/msh_ast_sanitize_token_dropseps.c \
				token/impl/msh_ast_sanitize_token_duplicate.c \
				token/impl/msh_ast_sanitize_token_first.c \
				token/impl/msh_ast_sanitize_token_recurse.c \
				token/impl/msh_ast_sanitize_token_word_before.c \
				token/msh_ast_sanitize_tokens.c \
				token/msh_ast_strtoken_simple.c \
				msh_ast_syntax_error.c

include ../common.mk
