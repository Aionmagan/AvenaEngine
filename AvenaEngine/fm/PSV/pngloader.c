#include "../pngloader.h" 

#include <stdio.h>
#include <stdlib.h>
#include <png.h>
#include <vitaGL.h>

#define CLEANUP(x) { ret = (x); goto cleanup; }


int load_png_texture(char* filename, tex_t* tex) 
{
	int ret = 0;
	FILE * file = 0;
	uint8_t * data = 0;
	png_structp parser = 0;
	png_infop info = 0;
	png_bytep * row_pointers = 0;

	png_uint_32 w, h;
	int bit_depth;
	int color_type;
    
    int rowbytes;
    GLenum texture_format;


	if(!tex || !filename) {
		CLEANUP(1);
	}

	file = fopen(filename, "rb");
	if(!file) {
		CLEANUP(2);
	}

	parser = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
	if(!parser) {
		CLEANUP(3);
	}

	info = png_create_info_struct(parser);
	if(!info) {
		CLEANUP(4);
	}

	if(setjmp(png_jmpbuf(parser))) {
		CLEANUP(5);
	}

	png_init_io(parser, file);
	png_read_info(parser, info);
	png_get_IHDR(parser, info, &w, &h, &bit_depth, &color_type, 0, 0, 0);

	if((w & (w-1)) || (h & (h-1)) || w < 8 || h < 8) {
		CLEANUP(6);
	}

	if(png_get_valid(parser, info, PNG_INFO_tRNS) || (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) || color_type == PNG_COLOR_TYPE_PALETTE) {
		png_set_expand(parser);
	}
	if(bit_depth == 16) {
		png_set_strip_16(parser);
	}
	if(color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
		png_set_gray_to_rgb(parser);
	}
	png_read_update_info(parser, info);

    rowbytes = png_get_rowbytes(parser, info);
	rowbytes += 3 - ((rowbytes-1) % 4); // align to 4 bytes

	data = (uint8_t*)malloc(rowbytes * h * sizeof(png_byte) + 15);
	if(!data) {
		CLEANUP(7);
	}

	row_pointers = (png_bytep *)malloc(h * sizeof(png_bytep));
	if(!row_pointers) {
		CLEANUP(8);
  }

	// set the individual row_pointers to point at the correct offsets of data
	for(png_uint_32 i = 0; i < h; ++i) {
		row_pointers[h - 1 - i] = data + (h-1-i) * rowbytes;
	}

	png_read_image(parser, row_pointers);

	// Generate the OpenGL texture object
	int texture_id;
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
    texture_format = (color_type & PNG_COLOR_MASK_ALPHA) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_2D, 0, texture_format, w, h, 0, texture_format, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	tex->tid = texture_id;
	tex->w = w;
	tex->h = h;
	//tex->format = texture_format;
	//tex->min_filter = tex->mag_filter = GL_NEAREST;


cleanup:
	if(parser) {
		png_destroy_read_struct(&parser, info ? &info : 0, 0);
	}

	if(row_pointers) {
		free(row_pointers);
	}

	if(ret && data) {
		free(data);
	}

	if(file) {
		fclose(file);
	}

	return ret;
}


#if 0
#include <stdio.h>
#include <png.h>
#include <malloc.h>
#include <ctype.h>

/*ERROR MESSAGE*/
#define FILE_ERROR(x) printf("%s file not found\n", x)
#define NOT_PNG printf("not png format file\n");
#define ERROR_INPUT printf("please choose a .png file\n");

#define PNG_ERROR printf("UNKNOWN ERROR");
/*ERROR MESSAGE*/

#define CLEANUP(x) { ret = (x); goto cleanup; }

typedef char uint8_t;

char* header        = NULL; 
png_structp png_ptr = NULL; 
png_infop info_ptr  = NULL; 
//png_infop end_ptr   = NULL; 
	
png_uint_32 w, h, i; 
int color_type; 
int bit_depth;
int rowbytes;
uint8_t* data = NULL; 
png_bytep* row_pointers = NULL;

int load_png_texture(char* s, tex_t* texture)
{
	FILE* fp = NULL; 
	
	if ((fp = fopen(s, "rb")) == NULL)
	{	
		FILE_ERROR(s);
		return -1;
	}
	
	header = malloc(sizeof(char) * 9);
	fread(header, 1, 8, fp); 
	
	/*that way we don't have 
	  to tell png that we read the header*/
	rewind(fp);
	
	/*if (png_sig_cmp(header, 0, 8))
	{
		return NOT_PNG; 
	}*/
	
	//ust* myust; 
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	info_ptr = png_create_info_struct(png_ptr);
	//end_ptr = png_create_info_struct(png_ptr);
	
	if (!png_ptr)
		return PNG_ERROR;
		
	if (!info_ptr)
	{
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		return PNG_ERROR; 
	}	
	
	/*if (!end_ptr)
	{
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		return PNG_ERROR; 
	}*/
	
	png_init_io(png_ptr, fp);
	png_read_info(png_ptr, info_ptr);
	png_get_IHDR(png_ptr, info_ptr, &w, &h, &bit_depth, &color_type, NULL, NULL, NULL);
	
	//png_read_update_info(png_ptr, info_ptr);
	
	if(png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS) || 
	  (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) || 
	   color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_expand(png_ptr);
	

    if(bit_depth == 16)
      png_set_strip_16(png_ptr);

    if(color_type == PNG_COLOR_TYPE_PALETTE)
      png_set_palette_to_rgb(png_ptr);

    // PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
    if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
      png_set_expand_gray_1_2_4_to_8(png_ptr);

    if(png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
      png_set_tRNS_to_alpha(png_ptr);

    // These color_type don't have an alpha channel then fill it with 0xff.
    if(color_type == PNG_COLOR_TYPE_RGB ||
       color_type == PNG_COLOR_TYPE_GRAY ||
       color_type == PNG_COLOR_TYPE_PALETTE)
      	png_set_filler(png_ptr, 0xFF, PNG_FILLER_AFTER);

    if(color_type == PNG_COLOR_TYPE_GRAY ||
       color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
      	png_set_gray_to_rgb(png_ptr);
      	
	png_read_update_info(png_ptr, info_ptr);
	//png_bytep row_pointers[h*h];
	rowbytes = png_get_rowbytes(png_ptr, info_ptr);
	rowbytes += 3 - ((rowbytes-1) % 4);
	data = (uint8_t*)malloc(rowbytes * h * sizeof(png_byte) + 15);
	row_pointers = (png_bytep *)malloc(h * sizeof(png_bytep));

	for(i = 0; i < h; ++i) 
		row_pointers[h - 1 - i] = data + i * rowbytes;
	
	
	png_read_image(png_ptr, row_pointers);
	
	texture->texture = (char*)malloc(sizeof(data)); 
	for(i = 0; i < h*w*4; ++i)
	{
		texture->texture[i] = (char)data[i]&0xff; 
	}
	texture->h = h; 
	texture->w = w; 
	//printf(" 0x%x ", row_pointers[i]);
	
	//fflush(fp); 
	fclose(fp); 
	
	png_destroy_read_struct(&png_ptr, info_ptr ? &info_ptr : 0, 0);
	//free(fp);
	free(row_pointers);
	free(data);  
	
	return 0;//printf("so far so good\n");
}
#endif

