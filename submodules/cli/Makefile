# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 06:49:07 by kiroussa          #+#    #+#              #
#    Updated: 2024/05/21 15:49:37 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	cli
DEPS		=	executor ast-builder
IS_EXEC		=	1

include ../common-prelude.mk

SRC			=	input/msh_input.c \
				opt/msh_handle_opts.c \
				opt/msh_opt_command.c \
				opt/msh_opt_flags.c \
				opt/msh_opt_help.c \
				opt/msh_opt_version.c \
				runner/msh_run_file.c \
				runner/msh_run_setup_script.c \
				runner/msh_runner_check.c \
				shell/prompt/msh_prompt_bash.c \
				shell/msh_handle_line.c \
				shell/msh_shell_loop.c \
				cli.c

include ../common.mk
