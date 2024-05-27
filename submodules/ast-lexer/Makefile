# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 07:00:21 by kiroussa          #+#    #+#              #
#    Updated: 2024/05/27 05:39:56 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ast-lexer
DEPS		=	ast-shared

include ../common-prelude.mk

SRC			=	token/msh_ast_strtoken.c \
				token/msh_ast_token_free.c \
				token/msh_ast_token_new.c \
				token/msh_ast_token_print.c \
				types/msh_ast_token_comment.c \
				types/msh_ast_token_delim.c \
				types/msh_ast_token_keyword.c \
				types/msh_ast_token_sep.c \
				types/msh_ast_token_simple.c \
				types/msh_ast_token_single_quote.c \
				types/msh_ast_token_string.c \
				types/msh_ast_token_word.c \
				msh_ast_lexer_debug.c \
				msh_ast_lexer_root.c \
				msh_ast_lexer_sub.c \
				msh_ast_tokenize.c

include ../common.mk
