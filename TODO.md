# TODO list

- [ ] Make the ast-builder tree_tokens support nested tokens (TKN_GROUP, TKN_STRING)
- [ ] Make the free function from tree_tokens ignore nested tokens (basically cleanup before calling ast_tkn_free)

## Goals

- [x] Basic setup, submodules, Makefiles, dependencies 
- [x] Makefile: transitive dependencies
- [x] Makefile: speedups
- [x] Shell-like input w/ readline, basic prompt
- [x] Execution structure
- [x] Tokenizer (part 1), environment manager, `execve`
- [x] Tokenizer (part 2): Separate environment variables, 
- [x] Lexer & Parser
- [x] AST Builder (part 1)
  - [x] Make a simple separation system where only `TKN_DELIM` & `TKN_PIPE` are used as separators
    - This will allow for expansion at execution time
  - [x] Maybe cleanup `TKN_SEP`???
- [x] Builtins (part 1), manager, dynamic registration
- [ ] Execution (part 1)

- [ ] To be defined

### Minishell goals

- Basic goals
  - [x] Makefile structure, compilation, dependencies as submodules
  - [x] Have a prompt in interactive mode
  - [x] Utilize readline's history module
- Execution goals
  - [x] Find executable using the `PATH` environment variable
  - [x] Not interpret unclosed quotes or special characters such as `\` or `;`
  - Handle single and double quotes as well as their interpretation
    - [x] Parsing part
    - [ ] Execution part (expansion)
  - Implement redirections
    - [ ] In
    - [ ] Out
    - [ ] Out-append
    - [ ] Here-docs
  - [ ] Implement pipes
  - [x] Handle environment variables
    - [x] Handle `$?`
  - Signal handling
    - [x] Interactive mode
    - [x] Passed down to subprocesses
  - Builtins
    - [x] `echo` with `-n`
    - [x] `cd` with a relative or absolute path
      - [ ] EXTRA: Handle `~` (transformer)
      - [x] EXTRA: Handle `-`
    - [x] `pwd` no flags
    - [x] `export` no flags
    - [x] `unset` no flags
    - [x] `env` no flags or arg
    - [x] `exit`
- Bonus
  - [ ] Implement `&&`, `||`, and `()`
  - [ ] Wildcards `*` for the current directory
    - [ ] EXTRA: Handle `?` and `[]`

- Extras (outstanding):
  - [ ] Implement `alias`
  - [ ] PS1 parsing
  - [ ] Auto-completion feature

<!--
### 42sh

- Requirements
  - Redirections
    - [ ] Aggregators `>&` and `<&`
  - [ ] Separators `;`
  - [ ] `cd`, `echo`, `exit`, and `type` builtins
- Mandatory
  - [ ] `set` and `unset` builtins
  - [ ] Parameter expansion `${...}`
  - [ ] Job control
    - [ ] `jobs`, `bg`, `fg`
    - [ ] `&` operator
  - [ ] Monitoring of all signals
  - [ ] Each builtin must have the POSIX standard options, except for explicit case as `set` or `unset`

- Bonuses are another story \o/
  - [x] Inhibitors `\` for quotes and double-quotes
  - Pattern matching (globbing)
    - [ ] `*`
    - [ ] `?`
    - [ ] `[a-Z]`
    - [ ] `!`
    - [ ]

-->

## Execution sources

- [x] `minishell` interactive
- [x] `minishell -c "cmd"`
  - `bash -c "echo meow"` exec la cmd
  - `bash -c "meow echo" "arg0" "arg1"` exec la cmd, change le nom du shell (arg0) et passe les args script (arg1)
- [x] `echo "echo lol" | minishell`
- [x] `minishell test.sh`
  - `bash anything.sh [arg1] [arg2]`, exec script, needs read perm, rejects binary executables 
    - [x] Reject binary executable
    - [x] Check path
    - [x] Check perms
    - [x] Actually run the damn file 
  - shebang: redirects to `minishell <file>`
