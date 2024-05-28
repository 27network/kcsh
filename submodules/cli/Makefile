# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 06:49:07 by kiroussa          #+#    #+#              #
#    Updated: 2024/05/28 12:12:49 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	cli
DEPS		=	executor ast-builder
IS_EXEC		=	1

include ../common-prelude.mk

SRC			=	opt/msh_handle_opts.c \
				opt/msh_opt_command.c \
				opt/msh_opt_flags.c \
				opt/msh_opt_help.c \
				opt/msh_opt_version.c \
				runner/msh_run_file.c \
				runner/msh_run_setup_script.c \
				runner/msh_runner_check.c \
				shell/input/msh_input.c \
				shell/input/msh_input_forked.c \
				shell/prompt/msh_shell_prompt_parse.c \
				shell/msh_shell_handle_input.c \
				shell/msh_shell_loop.c \
				cli.c

include ../common.mk
