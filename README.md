# Image Processing Project

*Project carried out in 1 year 1 semester*

![Image produced by example script](path/to/your/image.png)

## Overview

This project focuses on representing and processing RGB color images using **C++**, with each RGB channel allocated 8 bits. The initial codebase provided skeleton structures, alongside support for reading and writing images in the **PNG** format and test code to validate functionality.

## Features

### Core Classes

- **`prog::Color`**
  - Represents RGB colors.
  - Manages color manipulation and operations at the pixel level.

- **`prog::Image`**
  - Represents images composed of `prog::Color` pixels.
  - Supports various image processing operations such as loading, saving, and editing images.

- **`prog::Script`**
  - Processes scripts containing image manipulation commands.
  - Enables batch processing and automation of image editing tasks.

### Advanced Functionality

- **Median Filter**
  - Applies a median filter to images to reduce noise while preserving edges.
  - Useful for enhancing image quality in preprocessing steps.

- **XPM2 File Support**
  - Adds capability to load and save images in the **XPM2** format.
  - Expands compatibility with different image file standards.
