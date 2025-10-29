# miniRT - Mini Ray Tracer (Graphics Engine)

A simple, real-time ray tracer built as a project for Ecole 42. It can parse scene files, render various geometric shapes, and display the result in a window or save it as a BMP image.

## Building the Project

This project supports both **macOS** and **Linux**. Please follow the instructions for your operating system.

### macOS

You will need the Xcode Command Line Tools installed. Then, simply clone the repository and run `make`:

```sh
git clone <repository-url> miniRT
cd miniRT
make
```

### Linux

**1. Install Prerequisites**

Before building, you must install the X11 development libraries and other required tools. These are essential for the MiniLibX graphics library to function.

*   **For Debian / Ubuntu / Mint:**
    ```sh
    sudo apt-get update && sudo apt-get install -y xorg libxext-dev zlib1g-dev libbsd-dev
    ```
*   **For Fedora / CentOS / RHEL:**
    ```sh
    sudo dnf install -y libXext-devel libX11-devel zlib-devel
    ```
*   **For Arch Linux:**
    ```sh
    sudo pacman -Syu libxext libx11 zlib
    ```

**2. Configure and Build the Project**

After cloning the repository, you must first run the `configure` script inside the `minilibx_linux` directory. This step only needs to be done **once** to generate a `Makefile` tailored to your specific system.

```sh
git clone <repository-url> miniRT
cd miniRT/minilibx_linux/
./configure
cd ..
make
```

## Usage

To run the program and display a scene in a window, execute the binary with a scene file as an argument:

```sh
./miniRT scenes/map.rt
```
*(You can choose any scene from the `scenes/` directory. You can also modify the `.rt` files to add shapes, light sources, or change the camera.)*

To render a scene and save it as a `.bmp` image file **without** opening a window, add the `--save` flag as a second argument:

```sh
./miniRT scenes/map.rt --save
```
The saved image will appear in the `scenes/` folder with the same name as the scene file and a `.bmp` extension.

> **Note:** <br>
> The project supports both **macOS** and **Linux**.<br>
> Saving a frame as a `.bmp` file does not use the MiniLibX graphics library and works independently.<br>
> The program handles memory correctly, freeing all dynamically allocated memory upon exit.<br>
> This project was successfully defended at Ecole 42 (Sberbank 21 Kazan).<br>

## Some Screenshots

![cylinder (1)](https://user-images.githubusercontent.com/63866548/115561257-11242700-a2be-11eb-8cff-d414937be578.png)
![cylinder](https://user-images.githubusercontent.com/63866548/115564480-29497580-a2c1-11eb-9b3e-9bd617c5af1b.png)
![map](https://user-images.githubusercontent.com/63866548/115565701-46327880-a2c2-11eb-84ad-63ef78b6df19.png)
