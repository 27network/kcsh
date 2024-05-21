# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    config.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/16 05:36:04 by kiroussa          #+#    #+#              #
#    Updated: 2024/05/22 00:03:08 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT_NAME	?= kcsh
PROJECT_VERSION	?= 0.3.1-indev

SRC_DIR			?= src
INCLUDE_DIR		?= include

CC				= clang
CFLAGS			= -Wall -Wextra -Werror -g3
DFLAGS 			= -MT $@ -MMD -MP -MF $(D_DIR)/$*.tmp.d

#LDFLAGS shouldn't be defined here, as it's shared with `ar`. 
# See `submodules/common-prelude.mk`

MAKE_TRACE		?= 0
EXTRA_DEBUG		?= 0
HYPERTHREADING	?= 1

print_%:
	@echo $($*)
