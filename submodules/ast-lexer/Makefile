# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 07:00:21 by kiroussa          #+#    #+#              #
#    Updated: 2024/09/28 17:04:06 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ast-lexer
DEPS		=	ast-shared

include ../common-prelude.mk

SRC			=	token/print/msh_ast_print_delim.c \
				token/print/msh_ast_print_group.c \
				token/print/msh_ast_print_keyword.c \
				token/print/msh_ast_print_redir.c \
				token/print/msh_ast_print_string.c \
				token/msh_ast_strtoken.c \
				token/msh_ast_token_clone.c \
				token/msh_ast_token_free.c \
				token/msh_ast_token_new.c \
				token/msh_ast_token_print.c \
				token/msh_ast_token_trace.c \
				types/redir/msh_ast_redir_filltype.c \
				types/subst/impl/msh_ast_token_subst_var.c \
				types/subst/impl/msh_ast_token_subst_wildcard.c \
				types/subst/msh_ast_is_substituable.c \
				types/subst/msh_ast_is_substituable_var.c \
				types/subst/msh_ast_token_substitution.c \
				types/msh_ast_token_comment.c \
				types/msh_ast_token_delim.c \
				types/msh_ast_token_group.c \
				types/msh_ast_token_keyword.c \
				types/msh_ast_token_number.c \
				types/msh_ast_token_redirection.c \
				types/msh_ast_token_sep.c \
				types/msh_ast_token_simple.c \
				types/msh_ast_token_single_quote.c \
				types/msh_ast_token_string.c \
				types/msh_ast_token_word.c \
				msh_ast_lexer_debug.c \
				msh_ast_lexer_is_delim.c \
				msh_ast_lexer_root.c \
				msh_ast_lexer_sub.c \
				msh_ast_tokenize.c

include ../common.mk
