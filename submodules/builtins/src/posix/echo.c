/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 22:54:45 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/15 23:28:53 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh/builtin.h>

#define ECHO_USAGE "echo [arg ...]"
#define ECHO_USAGE_OPT "echo [-neE] [arg ...]"
#define ECHO_HELP "Write arguments to the standard output.\n\
\n\
Display the ARGs, separated by a single space character and followed by a\n\
newline, on the standard output.\n\
\n\
Options:\n\
  -n	do not append a newline\n\
\n\
Exit Status:\n\
Returns success unless a write error occurs."
#define ECHO_HELP_OPT "Write arguments to the standard output.\n\
\n\
Display the ARGs, separated by a single space character and followed by a\n\
newline, on the standard output.\n\
\n\
Options:\n\
  -n	do not append a newline\n\
  -e	enable interpretation of the following backslash escapes\n\
  -E	explicitly suppress interpretation of backslash escapes\n\
\n\
`echo' interprets the following backslash-escaped characters:\n\
  \\a	alert (bell)\n\
  \\b	backspace\n\
  \\c	suppress further output\n\
  \\e	escape character\n\
  \\E	escape character\n\
  \\f	form feed\n\
  \\n	new line\n\
  \\r	carriage return\n\
  \\t	horizontal tab\n\
  \\v	vertical tab\n\
  \\\\	backslash\n\
  \\0nnn	the character whose ASCII code is NNN (octal).  NNN can be\n\
		0 to 3 octal digits\n\
  \\xHH	the eight-bit character whose value is HH (hexadecimal).  HH\n\
		can be one or two hex digits\n\
  \\uHHHH	the Unicode character whose value is the hexadecimal value HHHH.\n\
		HHHH can be one to four hex digits.\n\
  \\UHHHHHHHH the Unicode character whose value is the hexadecimal value\n\
		HHHHHHHH. HHHHHHHH can be one to eight hex digits.\n\
\n\
Exit Status:\n\
Returns success unless a write error occurs."

static int	msh_echo(
	ATTR((unused)) int argc,
	ATTR((unused)) char **argv
) {
	return (0);
}

__attribute__((constructor))
void	register_echo(void)
{
	char	*help;
	char	*usage;

	help = ECHO_HELP;
	usage = ECHO_USAGE;
	if (FEAT_BUILTIN_ECHO_OPT)
	{
		help = ECHO_HELP_OPT;
		usage = ECHO_USAGE_OPT;
	}
	msh_builtin_register((t_builtin){
		.name = "echo",
		.usage = usage,
		.help = help,
		.func = msh_echo,
		.enabled = true,
	});
}
