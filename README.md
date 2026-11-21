# minishell

A Unix shell in C with command parsing, environment expansion, pipelines, redirections, and built-ins.

## In this repository

- Tokenizes command lines, interprets quotes, and expands environment variables and exit status.
- Runs external programs and built-in commands such as `cd`, `echo`, `export`, and `unset`.
- Connects command pipelines, supports input and output redirections plus heredocs, and handles interactive signals.

## Build and run

```sh
make
./minishell
```

Build on a Unix-like system with a C compiler, Make, and GNU Readline development headers. Run it in an interactive terminal. Try `echo "hello" | wc -c` at the shell prompt.

## Credits

Created as part of the 42 curriculum by akella and zaissi.
