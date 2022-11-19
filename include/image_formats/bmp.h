#pragma once

#include <stdbool.h>
#include <stdio.h>

void write_rgb_bitmap_to_file(const unsigned char* image, unsigned width, unsigned height, FILE* image_file);
bool write_rgb_bitmap(const unsigned char* image, unsigned width, unsigned height, const char* image_file_name);
