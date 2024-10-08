# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    config.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/16 05:36:04 by kiroussa          #+#    #+#              #
#    Updated: 2024/10/09 02:39:03 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT_NAME	?= kcsh
PROJECT_VERSION	?= 0.7.0

SRC_DIR			?= src
INCLUDE_DIR		?= include

CC				?= clang
CFLAGS			+= -Wall -Wextra -Werror -g3 -fno-plt -fPIE
DFLAGS 			+= -MT $@ -MMD -MP -MF $(D_DIR)/$*.tmp.d

ifeq ($(KCSH_TESTS), 1)
CFLAGS			+= -DKCSH_TESTS
endif

# :trollface:
FREEZE_LOGS		?= 0
# additional info for debugging gnu make
MAKE_TRACE		?= 0
# log all commands executed
EXTRA_DEBUG		?= 0
# enable super duper cool hyper multithreading
HYPERTHREADING	?= 1

print_%:
	@echo $($*)
