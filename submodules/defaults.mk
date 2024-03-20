# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    config.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/16 05:36:04 by kiroussa          #+#    #+#              #
#    Updated: 2024/03/20 03:28:54 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT_NAME	?= minishell
PROJECT_VERSION	?= 0.1.8

SRC_DIR			?= src
INCLUDE_DIR		?= include

CC				= clang
CFLAGS			= -Wall -Wextra -Werror -g3
DFLAGS 			= -MT $@ -MMD -MP -MF $(D_DIR)/$*.tmp.d

#LDFLAGS shouldn't be defined here, as it's shared with `ar`. 
# See `submodules/common-prelude.mk`

EXTRA_DEBUG		?= 0

print_%:
	@echo $($*)
