## Simple text editor called Picsart written in C using SDL and STB_IMAGE

This is a simple text editor written in C using the SDL (Simple DirectMedia Layer) library for graphics and STB_IMAGE library for image loading. 

### Prerequisites

Before building and running this project, make sure you have the following dependencies installed:

- pkg-config
- SDL2

If you haven't installed them yet, you can usually install them using your system's package manager. For example, on Ubuntu or Debian, you can use the following commands:

```bash
sudo apt-get update
sudo apt-get install pkg-config libsdl2-dev
```

## Building and Running

To build and run the text editor, follow these steps:

1. Clone this repository to your local machine:

```bash
git clone https://github.com/your-username/Picsart.git
```

2. Navigate to the project directory:

```bash
cd Picsart
```

3. Compile the source code using the provided Makefile:

```bash
make
```

4. Run the text editor:

```bash
./picsart
```