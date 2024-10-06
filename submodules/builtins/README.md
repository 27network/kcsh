# builtins

This module contains every shell builtin available in kcsh.

## File Hierarchy

The sources are arranged in the following way:

- `src/`
    - `core/`
        - The core builtin system, including the builtin registry and helper functions.
    - `minishell/`
        - The builtins that are required for the minishell project.
    - `42sh/`
        - The builtins that are required for the 42sh project, both mandatory and modular parts.
    - `posix/`
        - The POSIX-mandated builtins, which are also for the bonus part of 42sh.
    - `bash/`
        - Builtins taken from the bash, which are not POSIX-mandated, but are still useful/fun.
