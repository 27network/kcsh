# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 07:00:21 by kiroussa          #+#    #+#              #
#    Updated: 2024/07/05 21:03:17 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	shared
ifeq ($(USES_READLINE), 0)
DEPS		=	shakespeare
endif

include ../common-prelude.mk

SRC			=	env/default/msh_env_defaults.c \
				env/default/msh_env_populate.c \
				env/name/msh_env_is_special_name_starter.c \
				env/name/msh_env_is_valid_name.c \
				env/name/msh_env_is_valid_name_starter.c \
				env/tab/msh_env_sorted.c \
				env/tab/msh_env_tab.c \
				env/tab/msh_env_tab_free.c \
				env/msh_env_find.c \
				env/msh_env_free.c \
				env/msh_env_free_all.c \
				env/msh_env_get.c \
				env/msh_env_print_assignment.c \
				env/msh_env_push.c \
				env/msh_env_set_if_not.c \
				env/msh_env_value.c \
				log/msh_error.c \
				log/msh_log.c \
				log/msh_vlog.c \
				log/msh_warn.c \
				signal/handlers/msh_signal_handler_catch.c \
				signal/handlers/msh_signal_handler_close.c \
				signal/handlers/msh_signal_handler_interactive.c \
				signal/msh_signal_init.c \
				signal/msh_signal_setdfl.c \
				signal/msh_strsignal.c \
				util/io/msh_fileno.c \
				util/io/msh_get_hostname.c \
				util/io/msh_getpw_for.c \
				util/io/msh_getpwnam.c \
				util/io/msh_getpwuid.c \
				util/io/msh_is_directory.c \
				util/io/msh_passwd_free.c \
				util/io/msh_same_file.c \
				util/io/msh_term_size.c \
				util/string/msh_ansicstr.c \
				util/string/msh_contains_shell_metas.c \
				util/string/msh_expand_tilde.c \
				util/string/msh_quote.c \
				util/string/msh_strcoll.c \
				util/msh_geteuid.c \
				util/msh_is_interactive.c \
				util/msh_resolve_path.c \
				msh_destroy.c \
				msh_exit.c \
				msh_fork.c \
				msh_init.c

ifeq ($(KCSH_TESTS), 1)
SRC				+=	util/tests/assert.c \
					util/tests/assert_eq.c \
					util/tests/assert_neq.c \
					util/tests/assert_strs.c
endif

include ../common.mk
