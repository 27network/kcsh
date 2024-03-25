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
	"TOK_SEMICOLON" 1 \
	"BUILTIN_ECHO_OPT" 1 \
	"BUILTIN_CD_OPT" 1 \
	"BUILTIN_TYPE" 1 \
	"BUILTIN_SET" 1 \
	"BUILTIN_UNSET" 1 \
	"PARSER_INLINE_ASSIGN" 1 \
	"PARSER_PARAM_EXPANSION" 1 \
	"JOB_CONTROL" 1 \
	"SIG_ALL" 1 \
	"BUILTIN_ENV_DISABLE" 1 \
)

FEAT_MODULAR_42SH=( \
	"PARSER_INHIBITORS" 1 \
)

FEAT_BONUS_42SH=( \
	# Posix shell features
	"BUILTIN_COLON" 1 \
	"BUILTIN_TRUE" 1 \
	"BUILTIN_FALSE" 1 \
	"BUILTIN_HELP" 1 \
	"BUILTIN_HELP_SET" 1 \
)

FEAT_EXTRAS=( \
)

# > Category flags
# Every category of flags. 
#
# They are represented in pairs:
# - The first element is the name of the category.
# - The second element is whether that category is enabled or not.
CATEGORY_FLAGS=( \
	"BONUS_MSH" 1 \
	"MANDATORY_42SH" 1 \
	"MODULAR_42SH" 1 \
	"BONUS_42SH" 1 \
	"EXTRAS" 1 \
)
DEP_BONUS_MSH=()
DEP_MANDATORY_42SH=(BONUS_MSH)
DEP_MODULAR_42SH=(MANDATORY_42SH)
DEP_BONUS_42SH=(MODULAR_42SH)
DEP_EXTRAS=()

## Functions

resolve_deps() {
	local changed=0
	for i in "${!CATEGORY_FLAGS[@]}"; do
		if [[ $(((i-1) % 2)) -eq 0 ]]; then
			name="${CATEGORY_FLAGS[$i-1]}"
			dep_name="DEP_$name"
			dep_array="${!dep_name}"
			for dep in "${dep_array[@]}"; do
				# search for dep in category flags
				for j in "${!CATEGORY_FLAGS[@]}"; do
					# if j-1 is dep
					if [[ "${CATEGORY_FLAGS[$j-1]}" == "$dep" ]]; then
						# if dep is disabled
						if [[ "${CATEGORY_FLAGS[$j]}" == 0 ]]; then
							# if we're enabled
							if [[ "${CATEGORY_FLAGS[$i]}" == 1 ]]; then
								# kil- uh, disable yourself.
								CATEGORY_FLAGS[$i]=0
								changed=1
							fi
						fi
					fi
				done
			done
		fi
	done

	# State has changed, might wanna re-check stuff out :3
	if [[ $changed -eq 1 ]]; then
		resolve_deps
	fi
}

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

# End header guard
end_header_guard() {
	cat <<EOF
# endif // __MSH_FEATURES_H__
#endif // FEATURES_H
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

## Main execution
resolve_deps

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

end_header_guard
