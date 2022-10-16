#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

enum data_type
{
	EMPTY,
	COLOR_MAPPED,
	TRUE_COLOR,
	GRAYSCALE
};

typedef uint8_t data_type;

const data_type RUN_LENGTH = 8;
/* to specify a run-length encoded true-color image : TRUE_COLOR | RUN_LENGTH */

struct colormap_spec
{
	uint16_t offset;
	uint16_t colors_count;
	uint8_t  bits_per_entry;
} __attribute__((packed));

struct image_desc
{
	uint8_t attribute_bits_count : 4;
	uint8_t reserved : 1;
	uint8_t origin_is_upper_left : 1;
	uint8_t interleaving : 2;
};

struct image_spec
{
	uint16_t          x_origin;
	uint16_t          y_origin;
	uint16_t          width;
	uint16_t          height;
	uint8_t           bits_per_pixel;
	struct image_desc image_descriptor;
};

struct header
{
	uint8_t              ID_length;
	uint8_t              colormap_type;
	data_type            image_type;
	struct colormap_spec colormap_spec;
	struct image_spec    image_spec;
} __attribute__((packed));

const unsigned bytes_per_pixel = 4;

void TGA_write_argb_image_to_file(const unsigned char* image, unsigned width, unsigned height, FILE* image_file)
{
	struct header header =
	{
		.image_type = TRUE_COLOR,
		.image_spec =
		{
			.width            = width,
			.height           = height,
			.bits_per_pixel   = 32,
			.image_descriptor =
			{
				.attribute_bits_count = 8,
				.origin_is_upper_left = 1
			}
		}
	};

	fwrite(&header, sizeof(header), 1, image_file);
	fwrite(image, width * bytes_per_pixel, height, image_file);
}

bool TGA_write_argb_image(const unsigned char* image, unsigned width, unsigned height, const char* image_file_name)
{
	FILE* image_file = fopen(image_file_name, "wb");

	if (image_file == NULL)
		return false;
	TGA_write_argb_image_to_file(image, width, height, image_file);
	return fclose(image_file) == 0;
}
