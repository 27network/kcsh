# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 06:49:07 by kiroussa          #+#    #+#              #
#    Updated: 2024/09/30 12:11:30 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	cli
DEPS		=	ast-builder ast-lexer-sanitizer executor
IS_EXEC		=	1

include ../common-prelude.mk

SRC			=	history/msh_history_file.c \
				history/msh_history_free.c \
				history/msh_history_load.c \
				history/msh_history_modify_last.c \
				history/msh_history_print.c \
				history/msh_history_push.c \
				history/msh_history_raw.c \
				history/msh_history_save.c \
				opt/msh_handle_debug_generic.c \
				opt/msh_handle_opts.c \
				opt/msh_opt_command.c \
				opt/msh_opt_flags.c \
				opt/msh_opt_help.c \
				opt/msh_opt_version.c \
				runner/msh_run_file.c \
				runner/msh_run_setup_script.c \
				runner/msh_runner_check.c \
				shell/ast/msh_ast_create.c \
				shell/ast/msh_ast_lex.c \
				shell/ast/msh_dump_tokens.c \
				shell/input/msh_input.c \
				shell/input/msh_input_forked.c \
				shell/input/msh_input_type.c \
				shell/input/msh_input_wrap.c \
				shell/prompt/msh_shell_prompt_parse.c \
				shell/msh_exec_wrap.c \
				shell/msh_shell_handle_heredocs.c \
				shell/msh_shell_handle_input.c \
				shell/msh_shell_loop.c \
				cli.c

include ../common.mk
