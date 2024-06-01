# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    common-prelude.mk                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 07:06:42 by kiroussa          #+#    #+#              #
#    Updated: 2024/06/01 09:52:40 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifndef NAME
	$(error NAME is not defined)
endif

NAME			?=	$(NAME) # you know what, redefines your name

DEPTH			?=	0
DEPTH_FACTOR	?=  4
SPACING			:=	$(shell for i in $(shell seq 1 $(DEPTH)); do printf "%$(DEPTH_FACTOR)s" ""; done)
SPACING_TARGET	:=	$(SPACING)
#TODO: linear connections
# SPACING			=	$(shell for i in $(shell seq 1 $(DEPTH)); do printf "%$(DEPTH_FACTOR)s│%$(DEPTH_FACTOR)s" "" ""; done)
# SPACING_TARGET	:=	$(shell echo "$(SPACING)")
CACHE_DIR		?=	.cache
IS_EXEC			?=	0
LDFLAGS			?=

LD 				:=	$(CC)
LDFLAGS			+=	-lm
LDFLAGS			+=	-lreadline

ifeq ($(IS_EXEC), 1)
OUTPUT			:=	$(NAME)
else
OUTPUT			:=	lib$(NAME).so
endif

MODULE_CACHE	:=	$(CACHE_DIR)/$(NAME)
OBJ_DIR			?=	$(MODULE_CACHE)/obj
D_DIR			?=	$(MODULE_CACHE)/deps

SELF_DEP		:=	$(D_DIR)/_module.d

include ../defaults.mk

CFLAGS			+=	-I$(shell pwd)/$(INCLUDE_DIR)
ifdef LIBFT_DIR
CFLAGS			+=	-I$(LIBFT_DIR)/include
endif

CFLAGS			+=	-DMSH_DEFAULT_NAME="\"$(PROJECT_NAME)\""
CFLAGS			+=	-DMSH_VERSION="\"$(PROJECT_VERSION)\""

ifdef DEPS
SUBMODULES_DIR	:= $(shell pwd | xargs dirname)
NEW_DEPS		:=
ADD_DEPS		= $(eval NEW_DEPS += $(shell make -s -C $(SUBMODULES_DIR)/$(1) print_DEPS))
_				:= $(foreach dep, $(DEPS), $(call ADD_DEPS,$(dep)))
DEPS			:= $(DEPS) $(shell echo $(NEW_DEPS) | sed 's/ /\n/g' | sort -r | uniq)

TMPDEPDECL 		:= $(DEPS:%=-I$(shell pwd | xargs dirname)/%/include)
CFLAGS			+= $(TMPDEPDECL)
else
DEPS			:=
endif

# static linking
LIBS :=
BUILD_NEW_ARRAY = $(eval LIBS += $(CACHE_DIR)/$(shell echo "$(1)" | xargs)/lib$(shell echo "$(1)" | xargs).so)
_ := $(foreach item, $(DEPS), $(call BUILD_NEW_ARRAY, $(item)))
ifdef DEPS
LDFLAGS			+=	$(LIBS)
endif

ifdef LIBFT_DIR
LDFLAGS			+=	$(LIBFT_DIR)/build/output/libft.so 
endif

ifeq ($(IS_EXEC), 0)
CFLAGS			+=	-fPIC
LDFLAGS			+=	-shared
endif

OUTPUT			:=	$(addprefix $(MODULE_CACHE)/, $(OUTPUT))
