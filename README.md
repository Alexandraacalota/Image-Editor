Copyright 2021 Alexandra-Maria Calota
# Image Editor

## Overview
The program represents the implementation of a text editor, which supports performing a set of operations on PPM or PGM formatted images, with the maximum color intensity value of 255.

## Input and Output Files
- The input and output files of the program are identified by the magic words P2, P3, P5, and P6, specific to the PBM standard.

## Data Structures Used
- Used an RGB structure for storing the red, green, and blue color matrices in char variables and an RGB_d structure for storing them in double variables.

## Main Functionality
- The main function of the program reads the command name from stdin and contains a switch case based on this input.

## Supported Commands
- 0 -> LOAD
- 1 -> SELECT
- 2 -> ROTATE
- 3 -> CROP
- 4 -> APPLY
- 5 -> SAVE
- 6 -> EXIT

## Loading Functionality
- The image loading function is implemented using two reading functions, one ASCII and the other binary. Memory is dynamically allocated for an RGB image if no image is already loaded in the program. If an image exists, the previously allocated memory is released, and memory is reallocated for the new image.

## Image Manipulation Functions
- The program supports various image manipulation functions such as rotation, cropping, and applying filters.

## Saving Functionality
- The save function reads the filename from stdin and saves the image in the specified format - ASCII or binary.

## Exiting the Program
- The exit function stops the program execution, releasing the allocated memory for storing the image if it exists.

## Error Handling
- If an unsupported command is entered, the program displays the "Invalid command" error message and waits for a new command.