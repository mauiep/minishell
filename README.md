# Minishell

This school's project ask us to make our own shell (command-line interpreter), based on bash. The objective of the Minishell project was to implement various features, including redirections, pipes, env variables, and built-ins.

# Features

* Prompt for user input
* Functional history
* Execute the appropriate command based on the '**PATH**' environment variable or a relative or absolute path
* Handle single and double quotes
* Implement redirections:
    * '**<**' redirects input
    * '**>**' redirects output
    * '**<<**' receives a delimiter and reads input until encountering a line containing the delimiter (*heredoc*)
    * '**>>**' redirects output in append mode
* Implement pipes using the '**|**' character
* Handle environment variables (a '**$**' followed by a sequence of characters) by substituting their contents
* Handle '**$?**' by substituting the exit status of the last foreground pipeline executed
* Handle '**ctrl-C**', '**ctrl-D**', and '**ctrl-\\**' as they work in bash
* In interactive mode:
    * '**ctrl-C**' displays a new prompt on a new line
    * '**ctrl-D**' exits the shell
    * '**ctrl-\\**' does nothing
* Implement the following builtins:
    * '**echo**' with the option '**-n**'
    * '**cd**' only with a relative or absolute path
    * '**pwd**'
    * '**export**'
    * '**unset**'
    * '**env**'
    * '**exit**'

## How to Run

To run the program, navigate to the project directory and run the following command:

```
make
./minishell
```

*Then enjoy yourself ;)*

# Examples

![Screenshot from 2023-04-07 19-23-33](https://user-images.githubusercontent.com/31923839/230650910-ed9835c4-a731-4ee1-a617-b9e1ffdc3a4f.png)
