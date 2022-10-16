#include <stdbool.h>
#include <stdio.h>

void TGA_write_argb_image_to_file(const unsigned char* image, unsigned width, unsigned height, FILE* image_file);
bool TGA_write_argb_image(const unsigned char* image, unsigned width, unsigned height, const char* image_file_name);
