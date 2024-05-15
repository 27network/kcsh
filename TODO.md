# TODO list

## Goals

- [ ] Makefile related: transitive dependencies

- [x] Basic setup, submodules, Makefiles, dependencies 
- [x] Shell-like input w/ readline, basic prompt
- [x] Execution structure
- [x] Tokenizer (part 1), environment manager, `execve`
- [ ] Tokenizer (part 2): Separate environment variables, 
- [ ] Lexer & Parser
- [ ] AST Builder (part 1)
- [ ] Builtins (part 1), manager, dynamic registration
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
    - [ ] `env` no flags or arg
    - [ ] `exit` no flags
- Bonus
  - [ ] Implement `&&`, `||`, and `()`
  - [ ] Wildcards `*` for the current directory
    - [ ] Handle `?` and `[]`

- Extras (outstanding):
  - [ ] Implement `alias`
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
## bordel

Feature management system ideas:
- `features.h` + `features.mk`

Make related:
- [x] Dependency system
  - [x] Automatically make
  - [x] Fix submodules trying to relink deps
  - [x] Build dependency tree
  - [x] Generate .d files
  - [x] Depend on .d files
    - [x] in ./Makefile
    - [x] in ./submodules/common.mk
  - [x] Fix bug where .c files dont recompile .o
- [x] Add /third-party to compilation
- [ ] Better output

## Execution sources

- [x] `minishell` interactive
- [x] `minishell -c "cmd"`
  - `bash -c "echo meow"` exec la cmd
  - `bash -c "meow echo" "minishell"` exec la cmd, change le nom du shell
- [x] `echo "echo lol" | minishell`
- [ ] `minishell test.sh`
  - `bash anything.sh [arg1] [arg2]`, exec script, needs read perm, rejects binary executables 
  - shebang: redirects to `minishell <file>`
