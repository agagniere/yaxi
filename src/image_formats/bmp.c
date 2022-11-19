#include "image_formats/bmp.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

enum compression
{
	BI_RGB            = 0,
	BI_BITFIELDS      = 3,
	BI_ALPHABITFIELDS = 6
};

typedef uint32_t compression_t;

struct file_header
{
	char     signature[2];
	uint32_t file_size;
	uint32_t reserved;
	uint32_t offset;
} __attribute__((packed));

struct info_header
{
	uint32_t      header_size;
	int32_t       width;
	int32_t       height;
	uint16_t      color_planes;
	uint16_t      bits_per_pixel;
	compression_t compression;
	uint32_t      image_size;
	int32_t       horizontal_resolution;
	int32_t       vertical_resolution;
	uint32_t      palette_size;
	uint32_t      important_colors;
};

const unsigned bytes_per_pixel   = 4;
const size_t   total_header_size = sizeof(struct file_header) + sizeof(struct info_header);

static struct file_header file_header(unsigned stride, unsigned height)
{
	return (struct file_header){.signature = "BM",
	                            .file_size = total_header_size + (stride * height),
	                            .offset    = total_header_size};
}

/* Height can be negative to signify a top-down order of rows */
static struct info_header info_header(unsigned width, int height)
{
	return (struct info_header){.header_size    = sizeof(struct info_header),
	                            .width          = width,
	                            .height         = height,
	                            .color_planes   = 1,
	                            .bits_per_pixel = (bytes_per_pixel << 3),
	                            .compression    = BI_RGB};
}

void write_rgb_bitmap_to_file(const unsigned char* image, unsigned width, unsigned height, FILE* image_file)
{
	unsigned           stride     = width * bytes_per_pixel;
	struct file_header fileheader = file_header(stride, height);
	struct info_header infos      = info_header(width, -height);

	fwrite(&fileheader, sizeof(fileheader), 1, image_file);
	fwrite(&infos, sizeof(infos), 1, image_file);
	fwrite(image, stride, height, image_file);
}

bool write_rgb_bitmap(const unsigned char* image, unsigned width, unsigned height, const char* image_file_name)
{
	FILE* image_file = fopen(image_file_name, "wb");

	if (image_file == NULL)
		return false;
	write_rgb_bitmap_to_file(image, width, height, image_file);
	return fclose(image_file) == 0;
}
