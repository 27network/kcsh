# libshakespeare
> readline but without memory leaks and normed to death. 

## usage

Typical usage tries to follow the GNU readline library:
```c
#include <shakespeare.h>

void    do_loop()
{
    char    *line;

    while (1)
    {
        line = shakespeare("prompt> ");
        if (!line)
            break ;
        printf("echo: %s", line); // Note: no \n
        fflush(stdout); // to prevent printf buffering, just in case
        free(line);
    }
}
```

## features

To get the most out of the library, you can use some of its features. Most of them will require you to get a hold of a `t_shakespeare_data` struct; you can do so like this:

```c
#include <shakespeare.h>

void    customize_shakespeare(void)
{
    t_shakespeare_data  *shk;

    shk = shk_shared();
    // ...
}
```

### keybinds

A rudimentary key-binding system is implemented. You can either implement your own action functions or use some of the limited built-in ones:

```c
#include <shakespeare.h>

static void custom_vim_bind(t_shakespeare_data *shk, int n);

void    setup_shakespeare_keybinds(t_shakespeare_data *shk)
{
    shk_input_bind(shk, "C-b", &shk_cursor_backward);
    shk_input_bind(shk, "C-f", &shk_cursor_forward);
    // shk_input_bind_vim(shk, SHK_VIM_NORMAL, "<C-P>j", &custom_vim_bind);
}

static void custom_vim_bind(t_shakespeare_data *shk, int n)
{
    while (n-- > 0)
    {
        shk_buffer_append(shk, "Hello");
    }
}
```

### hooks

Through the lifetime of the read-loop, some event functions get fired. You can set hooks and callbacks through the `hooks` property in the `t_shakespeare_data` struct:

```c
void    register_hooks(t_shakespeare_data *shk)
{
    shk->hooks.<hook name> = &<your function hook>;
}
```

Here are the available hooks:

```c
typedef enum e_shk_hook_type
{
    SHK_HOOK_BEFORE = 0,
    SHK_HOOK_AFTER,
}   t_shk_hook_type;

/**
 * Located at `shk->hooks.draw_hook`
 *
 * @return true if the draw should occur (when `type` is `SHK_HOOK_AFTER`, this doesn't matter).
 */
typedef bool    t_shk_hook_draw(
                    t_shakespeare_data *shk,
                    const t_shk_hook_type type);

/**
 * Located at `shk->hooks.draw_word_hook`
 *
 * Called whenever a full-word is drawn. Note that this isn't called in a loop, rather when a word needs redrawing.
 */
typedef void    t_shk_hook_draw_word(
                    t_shakespeare_data *shk,
                    const t_shk_hook_type type,
                    const char *word,
                    const size_t index);

/**
 * Located at `shk->hooks.input_hook`
 *
 * @return true if the function provides input handling and the input should be ignored.
 */
typedef bool    t_shk_hook_input(
                    t_shakespeare_data *shk,
                    const t_shk_hook_type type,
                    const char c,
                    bool *should_ret);
```

## developer todo

- [ ] Registry for termcap strings (cl, bp, dl, etc)
- [ ] Turn everything into binds/motions
- [ ] Documentation
