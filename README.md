# Wataru - A Simple Web Server

Wataru is a lightweight web server written in C, designed to be simple yet extensible. The name comes from Takagi Wataru, the clever detective from the anime *Detective Conan*—because this server aims to be just as sharp and efficient!

## Current Status

Right now, Wataru is a basic server that:
- Listens on port 8080.
- Handles incoming connections using `fork`.
- Echoes back whatever the client sends.

This is a work in progress, and more features are planned for the future.

## Prerequisites
- A C compiler (e.g., gcc)
- Meson and Ninja for building

## Installation and Running

1. Clone the repository:

```bash
git clone https://github.com/mmdbalkhi/wataru.git
cd wataru
```

2. Build the project with Meson:
```bash
meson setup build
ninja -C build
```

3. Run the server

```bash
./build/wataru
```

Once running, the server will be available at `localhost:8080`. You can test it with tools like `telnet`:

```bash
telnet 127.0.0.1:8080
```

## Future Plans

* Add support for standard HTTP requests
* Improve connection handling
* Add configurable settings (e.g., port, paths)

## Contributing

Got ideas or suggestions? I’d love for you to contribute! Feel free to submit a Pull Request or open an Issue.

## License

[MIT](./LICENSE.md)
