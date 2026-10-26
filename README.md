_This project has been created as part of the 42 curriculum by darmarti_

# minitalk

## Description

`minitalk` is a small client-server communication program for 42. The client
sends a text message to the server using only `SIGUSR1` and `SIGUSR2`.
Each signal represents one bit, and the server reconstructs and prints the
message. An acknowledgement is sent after every bit so that messages are
transmitted reliably.

## Build

Requirements: a Unix-like system, `cc`, `make`, and the project `libft`.

```bash
make
```

Useful targets:

```bash
make clean    # Remove object files
make fclean   # Remove objects, libraries and executables
make re       # Rebuild from scratch
make norme    # Run Norminette on the project files
```

## Usage

Start the server first and copy the PID printed in the terminal:

```bash
./server
```

Send a message from another terminal:

```bash
./client <SERVER_PID> "<MESSAGE>"
```

Example:

```bash
./client 4242 "Hello from minitalk!"
```

The server prints the received message and the client reports when the
transmission is complete.

## Implementation

- `server.c`: installs signal handlers and rebuilds characters bit by bit.
- `client.c`: validates the PID and sends each character with flow control.
- `utils.c`: signal setup, signal sending and error handling.
- `libft/`: supporting 42 C library.
