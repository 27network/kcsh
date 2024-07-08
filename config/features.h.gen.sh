#!/usr/bin/env bash
# Generator for `features.h`

# > Feature arrays
# Every feature that can be enabled or disabled.
#
# They are also represented in pairs, where:
# - The first element is the name of the feature.
# - The second element is whether that feature is enabled or not.

FEAT_BONUS_MSH=( \
	"PARSER_WILDCARD" 1 \
	"TOK_OR" 1 \
	"TOK_AND" 1 \
	"TOK_PARAN" 1 \
)

FEAT_MANDATORY_42SH=( \
	## Allowed functions (from `man(2)`)
	"SYSCALLS" 1 \

	## Mandatory features

	"TOK_SEMICOLON" 1 \
	"BUILTIN_ECHO_OPT" 1 \
	"BUILTIN_CD_OPT" 1 \
	"BUILTIN_PWD_OPT" 1 \
	"BUILTIN_TYPE" 1 \
	"BUILTIN_SET" 1 \
	"BUILTIN_UNSET" 1 \
	"PARSER_INLINE_ASSIGN" 1 \
	"PARSER_PARAM_EXPANSION" 1 \
	"JOB_CONTROL" 1 \
	"SIG_ALL" 1 \
	"BUILTIN_ENV_DISABLE" 1 \
	
	## Modular features

	"PARSER_INHIBITORS" 1 \

	"PATTERN_MATCHING" 1 \

	"TILDE_EXPANSION" 1 \

	"TOK_GROUP" 1 \

	"PARSER_CONTROL_SUBST" 1 \

	"PARSER_ARITHMETIC" 1 \

	"PARSER_PROCESS_SUBST" 1 \

	"HISTORY_MANAGEMENT" 1 \
	"PARSER_HISTORY_EXPANSION" 1 \
	"HISTORY_FILE" 1 \
	"BUILTIN_FC" 1 \
	"HISTORY_SEARCH" 1 \

	"SMART_COMPLETION" 1 \

	# "VI_SHORTCUTS" 1 \
	# "READLINE_SHORTCUTS" 1 \
	"NO_READLINE" 1 \

	"ALIAS_MANAGEMENT" 1 \
	"BUILTIN_ALIAS" 1 \
	"BUILTIN_UNALIAS" 1 \

	"HASH_TABLE" 1 \
	"BUILTIN_HASH" 1 \

	"BUILTIN_TEST" 1 \
)

FEAT_BONUS_42SH=( \
	## Posix shell features
	"BUILTIN_COLON" 1 \
	"BUILTIN_TRUE" 1 \
	"BUILTIN_FALSE" 1 \
	"BUILTIN_HELP" 1 \
	"BUILTIN_SET_FULL" 1 \
	"BUILTIN_TIMES" 1 \

	"PARSER_ANSI_QUOTING" 1 \
	"PARSER_LOCALIZE_QUOTING" 1 \

	## funny things
	"BUILTIN_ALL_BASH" 1 \
	"SCRIPTING" 1 \
)

# > Category flags
# Every category of flags. 
#
# They are represented in pairs:
# - The first element is the name of the category.
# - The second element is whether that category is enabled or not.
CATEGORY_FLAGS=( \
	"BONUS_MSH" 0 \
	"MANDATORY_42SH" 0 \
	"BONUS_42SH" 0 \
)
CATEGORY_LENGTH=${#CATEGORY_FLAGS[@]}

## Initial config from args

TARGET_MODE="$1"
if [[ -z "$TARGET_MODE" ]]; then
	TARGET_MODE="MANDATORY_MSH"
fi

# Loop in reverse and enable every category after the target mode
found=0
for i in "${!CATEGORY_FLAGS[@]}"; do
	i=$((CATEGORY_LENGTH - i))
	if [[ $(((i-1) % 2)) -eq 0 ]]; then
		if [[ "${CATEGORY_FLAGS[$i-1]}" == "$TARGET_MODE" ]]; then
			found=1
		fi
		if [[ $found -eq 1 ]]; then
			CATEGORY_FLAGS[$i]=1
		fi
	fi
done
unset found

# Generate 42 header
generate_42_header() {
	cat <<EOF
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   features.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: autogen <oss@xtrm.me>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 08:58:04 by kiroussa          #+#    #+#             */
/*   Updated: $(date +'%Y/%m/%d %H:%M:%S') by autogen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

EOF
}

# Auto-gen warning
auto_gen_warning() {
	cat <<EOF
/**
 * @file features.h
 * @brief This file is auto-generated. Do not edit it manually.
 * @date $(date +'%Y/%m/%d %H:%M:%S')
 * @see features.h.gen.sh
 */
EOF
}

# Start header guard
start_header_guard() {
	# this dumb sequence of preprocessor statements is to stop the norm from whining
	# because "bUt FeAtUrEs_H iS a GoOd HeAdEr GuArD nAmE" ffs.
	cat <<EOF

#ifndef FEATURES_H
# define FEATURES_H
# undef FEATURES_H
# ifndef __MSH_FEATURES_H__
#  define __MSH_FEATURES_H__

EOF
}

# Generate category flags
generate_category_flags() {
	array_all="$1[@]"
	array="$1"
	force_disable="$2"
	local i=0
	for feat in "${!array_all}"; do
		statement="${array}[$((${i}-1))]"
		name="${!statement}"
		if [[ "${force_disable}" == 1 && "${feat}" == 1 ]]; then
			feat=0
		fi
		if [[ "${feat}" == 0 ]]; then
			echo "#  define FEAT_$name 0"
		elif [[ "${feat}" == 1 ]]; then
			echo "#  define FEAT_$name 1"
		fi
		((i++))
	done
}

# Generate the enabled feature string
generate_category_enabled_strings() { 
	array_all="$1[@]"
	array="$1"
	local i=0
	for feat in "${!array_all}"; do
		statement="${array}[$((${i}-1))]"
		name="${!statement}"
		if [[ "${feat}" == 1 ]]; then
			echo "$name\\0\\"
		fi
		((i++))
	done
}

# End header guard
end_header_guard() {
	cat <<EOF
# endif // __MSH_FEATURES_H__
#endif // FEATURES_H
EOF
}

## Main execution
generate_42_header
auto_gen_warning
start_header_guard

# Define everything to false
# only use flags that are a 1
for i in "${!CATEGORY_FLAGS[@]}"; do
	name="${CATEGORY_FLAGS[$i-1]}"
	if [[ "${CATEGORY_FLAGS[$i]}" == 1 ]]; then
		echo "/* --- $name --- */"
		generate_category_flags "FEAT_$name" 0
		echo ""
	elif [[ "${CATEGORY_FLAGS[$i]}" == 0 ]]; then
		echo "/* --- $name (disabled) --- */"
		generate_category_flags "FEAT_$name" 1
		echo ""
	fi
done

echo "#  define ENABLED_FEATURES_STRING \"\\"

for i in "${!CATEGORY_FLAGS[@]}"; do
	name="${CATEGORY_FLAGS[$i-1]}"
	if [[ "${CATEGORY_FLAGS[$i]}" == 1 ]]; then
		generate_category_enabled_strings "FEAT_$name"
	fi
done

echo "\\0\""
echo ""

end_header_guard
