# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    defaults.mk                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/16 05:36:04 by kiroussa          #+#    #+#              #
#    Updated: 2024/06/25 15:07:54 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT_NAME	?= kcsh
PROJECT_VERSION	?= 0.3.1-indev

SRC_DIR			?= src
INCLUDE_DIR		?= include

CC				?= clang
CFLAGS			+= -Wall -Wextra -Werror -g3 -fno-plt -fPIE
DFLAGS 			+= -MT $@ -MMD -MP -MF $(D_DIR)/$*.tmp.d

ifeq ($(KCSH_TESTS), 1)
CFLAGS			+= -DKCSH_TESTS
endif

MAKE_TRACE		?= 0
EXTRA_DEBUG		?= 0
HYPERTHREADING	?= 1

print_%:
	@echo $($*)
