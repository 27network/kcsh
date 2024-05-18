# TODO list

## Goals

- [x] Basic setup, submodules, Makefiles, dependencies 
- [x] Makefile: transitive dependencies
- [x] Makefile: speedups
- [x] Shell-like input w/ readline, basic prompt
  - [ ] Prompt picker builtin?
- [x] Execution structure
- [x] Tokenizer (part 1), environment manager, `execve`
- [ ] Tokenizer (part 2): Separate environment variables, 
- [ ] Lexer & Parser
- [ ] AST Builder (part 1)
- [x] Builtins (part 1), manager, dynamic registration
- [ ] Pipeline builder
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
      - [ ] Clobber flag?
    - [ ] Out-append
    - [ ] Here-docs
  - [ ] Implement pipes
  - [ ] Handle environment variables
    - [ ] Handle `$?`
  - Signal handling
    - [x] Interactive mode
    - [x] Passed down to subprocesses
  - Builtins
    - [ ] `echo` with `-n`
    - [ ] `cd` with a relative or absolute path
      - [ ] Handle `~`
      - [ ] Handle `-`
    - [ ] `pwd` no flags
    - [ ] `export` no flags
    - [ ] `unset` no flags
    - [x] `env` no flags or arg
      - TODO: fix env ordering 
    - [x] `exit`
- Bonus
  - [ ] Implement `&&`, `||`, and `()`
  - [ ] Wildcards `*` for the current directory
    - [ ] Handle `?` and `[]`

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
- [ ] `minishell test.sh`
  - `bash anything.sh [arg1] [arg2]`, exec script, needs read perm, rejects binary executables 
    - [x] Reject binary executable
    - [x] Check path
    - [x] Check perms
    - [ ] Actually run the damn file 
  - shebang: redirects to `minishell <file>`
