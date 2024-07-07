/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 06:32:59 by kiroussa          #+#    #+#             */
/*   Updated: 2024/07/07 08:23:33 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define COMP_MAX 2048

static bool	msh_handle_dotslash(const char **inptr)
{
	const char	*in;

	in = *inptr;
	if (in[0] == '.' && (in[1] == '/' || in[1] == 0))
	{
		*inptr = in + 1;
		return (true);
	}
	return (false);
}

static bool	msh_handle_dotdotslash(
	const char **inptr,
	char ***topptr,
	char **outptr,
	int flags
) {
	const char	*in;
	char		**top;
	char		*out;

	in = *inptr;
	top = *topptr;
	out = *outptr;
	if (in[0] == '.' && in[1] == '.' && (in[2] == '/' || in[2] == 0))
	{
		in += 2;
		if (flags & 0x2)
			out = *--top;
		else if (flags & 0x1)
			out = top[-1];
		else
		{
			strcpy(out, "../");
			out += 3;
		}
		*inptr = in;
		*topptr = top;
		*outptr = out;
		return (true);
	}
	return (false);
}

static void	msh_normalize_epilogue(
	const char **inptr,
	char ***topptr,
	char **outptr
) {
	const char	*in;
	char		**top;
	char		*out;

	in = *inptr;
	top = *topptr;
	out = *outptr;
	*top++ = out;
	while (!(*in == 0 || *in == '/'))
		*out++ = *in++;
	if (*in == '/')
		*out++ = '/';
	*inptr = in;
	*topptr = top;
	*outptr = out;
}

static char	*msh_normalize0(char *out, const char *in)
{
	const bool	isabs = *in == '/';
	char		*pos[COMP_MAX];
	char		**top;
	char		*head;

	top = pos;
	head = out;
	if (isabs)
		*out++ = '/';
	*top++ = out;
	while (*in != 0)
	{
		while (*in == '/')
			++in;
		if (*in == 0)
			break ;
		if (msh_handle_dotslash(&in) || msh_handle_dotdotslash(&in, &top, &out,
				isabs * 1 + (top - pos > 1) * 2))
			continue ;
		if (top - pos >= COMP_MAX)
			return (NULL);
		msh_normalize_epilogue(&in, &top, &out);
	}
	*out = '\0';
	return (head);
}

char	*msh_canonicalize(const char *path, bool debug)
{
	char		*ret;
	const bool	abs = path[0] == '/';
	size_t		size;

	ret = calloc(strlen(path) + 1, sizeof(char));
	if (!ret)
		return (NULL);
	msh_normalize0(ret, path);
	size = strlen(ret);
	if (size > 1 && ret[size - 1] == '/')
		ret[size - 1] = '\0';
	return (ret);
}

/*










































*/


#define RED "\033[0;31m"
#define BOLD_BLUE "\033[1;34;42m"
#define GREEN "\033[0;32m"
#define BG_RED "\033[41m"
#define BG_GREEN "\033[42m"
#define RESET "\033[0m"

// Helper function to run a single test case
void run_test(const char *input, const char *expected, int *pass_count, int *fail_count) {
	// printf("[TRY] %s\r", input);
	// fflush(stdout);
    char *result = msh_canonicalize(input, false);
    if ((result == NULL && expected == NULL) || (result != NULL && expected != NULL && strcmp(result, expected) == 0)) {
        printf(BG_GREEN""BOLD_BLUE" OK "RESET" \"%s\" -> \"%s\"\n", input, result ? result : "NULL");
        (*pass_count)++;
    } else {
        printf(BG_RED" KO "RESET" \"%s\" -> \"%s\" [\"%s\"]\n", input, result ? result : "NULL", expected ? expected : "NULL");
        (*fail_count)++;
    }
    if (result) {
        free(result);
    }
}

// Function to run all test cases
void run_tests() {
    int pass_count = 0;
    int fail_count = 0;

    printf("Running tests:\n");

    // Absolute paths
    run_test("/a/b/c", "/a/b/c", &pass_count, &fail_count);
    run_test("/a//b/c", "/a/b/c", &pass_count, &fail_count);
    run_test("/a/b/c/", "/a/b/c", &pass_count, &fail_count);
    run_test("/a/b/c/.", "/a/b/c", &pass_count, &fail_count);
    run_test("/a/b/./c", "/a/b/c", &pass_count, &fail_count);
    run_test("/a/b/c/..", "/a/b", &pass_count, &fail_count);
    run_test("/a/b/c/../", "/a/b", &pass_count, &fail_count);
    run_test("/a/b/c/../..", "/a", &pass_count, &fail_count);
    run_test("/a/b/c/../../..", "/", &pass_count, &fail_count);
    run_test("/a/b/c/../../../..", "/", &pass_count, &fail_count);
    run_test("/a/b/c/../../../../d", "/d", &pass_count, &fail_count);
    run_test("/a/./b/./c/./d", "/a/b/c/d", &pass_count, &fail_count);
    run_test("/a/../b/../c/../d", "/d", &pass_count, &fail_count);

    // Relative paths
    run_test("a/b/c", "a/b/c", &pass_count, &fail_count);
    run_test("a//b/c", "a/b/c", &pass_count, &fail_count);
    run_test("a/b/c/", "a/b/c", &pass_count, &fail_count);
    run_test("a/b/c/.", "a/b/c", &pass_count, &fail_count);
    run_test("a/b/./c", "a/b/c", &pass_count, &fail_count);
    run_test("a/b/c/..", "a/b", &pass_count, &fail_count);
    run_test("a/b/c/../", "a/b", &pass_count, &fail_count);
    run_test("a/b/c/../..", "a", &pass_count, &fail_count);
    run_test("a/b/c/../../..", "", &pass_count, &fail_count);
    run_test("a/b/c/../../../..", "..", &pass_count, &fail_count);
    run_test("a/b/c/../../../../d", "../d", &pass_count, &fail_count);
    run_test("a/./b/./c/./d", "a/b/c/d", &pass_count, &fail_count);
    run_test("a/../b/../c/../d", "d", &pass_count, &fail_count);

    // Unusual cases
    run_test("", "", &pass_count, &fail_count);
    run_test("/", "/", &pass_count, &fail_count);
    run_test("/////", "/", &pass_count, &fail_count);
    run_test("/./././.", "/", &pass_count, &fail_count);
    run_test("/.././../", "/", &pass_count, &fail_count);
    run_test("/a/../../../../b/c", "/b/c", &pass_count, &fail_count);
    run_test("/a/b/../../../../c/d", "/c/d", &pass_count, &fail_count);
    run_test("/a/b/c/d/e/../../../f/g", "/a/b/f/g", &pass_count, &fail_count);
    run_test("./a/b/c", "a/b/c", &pass_count, &fail_count);
    run_test("a/b/.././../c", "c", &pass_count, &fail_count);
    run_test("a/b/../../../c", "../c", &pass_count, &fail_count);
    run_test("../a/b/c", "../a/b/c", &pass_count, &fail_count);
    run_test("../../a/b/c", "../../a/b/c", &pass_count, &fail_count);
    run_test("./.././a/b/./c", "../a/b/c", &pass_count, &fail_count);
   // Valid absolute paths
    run_test("/usr/local/bin", "/usr/local/bin", &pass_count, &fail_count);
    run_test("/home/user/documents", "/home/user/documents", &pass_count, &fail_count);
    run_test("/etc/nginx/nginx.conf", "/etc/nginx/nginx.conf", &pass_count, &fail_count);

    // Valid relative paths
    run_test("projects/python/app", "projects/python/app", &pass_count, &fail_count);
    run_test("../workspace/src", "../workspace/src", &pass_count, &fail_count);
    run_test("./config/settings", "config/settings", &pass_count, &fail_count);

    // Mixed and edge cases
    run_test("/////", "/", &pass_count, &fail_count);
    run_test("/a/./b/./c", "/a/b/c", &pass_count, &fail_count);
    run_test("/a/../b/../c", "/c", &pass_count, &fail_count);
    run_test("./a/./b/./c", "a/b/c", &pass_count, &fail_count);
    run_test("/a/../../b/./../c/", "/c", &pass_count, &fail_count);
    run_test("/../a/b/c/../d/./../", "/a/b", &pass_count, &fail_count);
    run_test("/a/../../.././../../b", "/b", &pass_count, &fail_count);
    run_test("/a/../../../b/../../", "/", &pass_count, &fail_count);

    // Complex relative paths
    run_test("../../a/b/c/./../d", "../../a/b/d", &pass_count, &fail_count);
    run_test("a/../b/./../c/../", "", &pass_count, &fail_count);
    run_test("../a/../b/../c/./d", "../c/d", &pass_count, &fail_count);
    run_test("a/b/c/../../..", "", &pass_count, &fail_count);
    run_test("../../a/b/c/../././../d", "../../a/d", &pass_count, &fail_count);

    // Edge cases with empty segments
    run_test("a//b//c", "a/b/c", &pass_count, &fail_count);
    run_test("a/b/c/../../d/e", "a/d/e", &pass_count, &fail_count);
    run_test("/./a/./b/./c/../", "/a/b", &pass_count, &fail_count);
    run_test("a/b/c/.././.././d", "a/d", &pass_count, &fail_count);
	run_test("c/../../d", "../d", &pass_count, &fail_count);
	run_test("c/../../d/..", "..", &pass_count, &fail_count);
	run_test("c/../../d/../..", "../..", &pass_count, &fail_count);
	run_test("c/../../d/../../..", "../../..", &pass_count, &fail_count);

    // Summary
    printf("\nSummary:\n");
    printf("Passed: %d\n", pass_count);
    printf("Failed: %d\n", fail_count);
}

#include <readline/readline.h>

int main(int argc, char **argv) {
	if (argc == 1)
		run_tests();
	else
	{
		char *line = readline("> ");
		if (!line)
			return 0;
		char *result = msh_canonicalize(line, true);
		printf("%s\n", result);
		free(result);
		free(line);
	}
    return 0;
}
