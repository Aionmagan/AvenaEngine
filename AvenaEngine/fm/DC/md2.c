#include"../md2.h"
#include"../pngloader.h"
#include<stdio.h>
#include<stdlib.h>
#include"../obj.h"

modelData_t* LoadMD2Model(char* filename, char* textureName)
{
	FILE* filePtr = NULL;               /*file pointer*/ 
	char s[40]={"/rd/"};
	int fileLen; 			     		/*length of model file*/
	char* buffer = NULL; 				/*file buffer*/
	
	modelData_t* model = NULL;          /*the model*/
	modelHeader_t* modelHeader = NULL;  /*model header*/
	texture_t* md2Texture = NULL;       /*model texture*/
	
	stIndex_t* stPtr = NULL;            /*texture indices*/
	frame_t* frame = NULL;              /*frame data*/
	vector3_t* pointListPtr = NULL;      /*index variable*/
	meshIndex_t* triIndex = NULL;            /*index variable*/
	meshIndex_t* bufIndexPtr = NULL;         /*index variable*/
	int i, j;                    		/*index variables*/
	
	tex_t texture;
	
	strcat(s, filename); 
	printf("md2 file = %s\n", s);
	/*open the model file*/
	filePtr = fopen(s, "rb");
	if (filePtr == NULL)
		return NULL; 
	
	/*find length of file*/
	fseek(filePtr, 0, SEEK_END);
	fileLen = ftell(filePtr); 
	fseek(filePtr, 0, SEEK_SET); 
printf("malloc in line 36\n");
	/*read entire file into buffer*/
	buffer = (char*)malloc(sizeof(char)*fileLen+1); 
	fread(buffer, sizeof(char), fileLen, filePtr); 
	
	/*extract model file header from buffer*/
	modelHeader = (modelHeader_t*)buffer; 
printf("malloc in line 42\n");
	/*allocate memory for model data*/
	model = (modelData_t*)malloc(sizeof(modelData_t)); 
	if (model == NULL)
		return NULL; 

	printf("numXYZ = %d | numFrames = %d\n", modelHeader->numXYZ, 
	                                         modelHeader->numFrames);
printf("malloc in line 50\n");
	/*allocate memory for all vertices used in model , including animations*/
	model->pointList = (vector3_t*)malloc(sizeof(vector3_t)*modelHeader->numXYZ*modelHeader->numFrames); 
	
	/*store vital model data*/
	model->numPoints = modelHeader->numXYZ; 
	model->numFrames = modelHeader->numFrames; 
	model->frameSize = modelHeader->framesize; 
	
	/*loop number of frames in model file*/
	for(j = 0; j < modelHeader->numFrames; ++j)
	{
		/*offset to the points in this frame*/
		frame = (frame_t*)&buffer[modelHeader->offsetFrames + modelHeader->framesize * j]; 
		
		/*calculate the point positions based on frame details*/
		pointListPtr = (vector3_t*)&model->pointList[modelHeader->numXYZ * j];
		
		for(i = 0; i < modelHeader->numXYZ; ++i)
		{
			pointListPtr[i].point[0] = frame->scale[0] * 
			                           frame->fp[i].v[0]+
			                           frame->translate[0]; 

			pointListPtr[i].point[1] = frame->scale[1] * 
			                           frame->fp[i].v[1]+
			                           frame->translate[1]; 

			pointListPtr[i].point[2] = frame->scale[2] * 
			                           frame->fp[i].v[2]+
			                           frame->translate[2]; 			                    			
		} 
	}
	
	//printf("png = %s\n", textureName);
	/*load the model texture*/
	md2Texture = &model->modelTex;
	load_png_texture(textureName, &texture);
	model->modelTex.texID = texture.tid; 
	model->modelTex.width = texture.w; 
	model->modelTex.height = texture.h; 
	/*
	if (md2Texture != NULL)
		model->modelTex = md2Texture; 
	else 
		return NULL; 
	*/

printf("malloc in line 93\n");
	/*allocate memory for the model texture coordinates*/
	model->st = (texCoord_t*)malloc(sizeof(texCoord_t)*modelHeader->numST);
	
	/*store number of texture coordiantes*/
	model->numST = modelHeader->numST; 
	
	/*set texture pointer to texture coordinate offset*/
	stPtr = (stIndex_t*)&buffer[modelHeader->offsetST];
	
	/*calculate and store the texture coordinates for the model*/
	for(i = 0; i < modelHeader->numST; ++i)
	{
		model->st[i].s = (float)stPtr[i].s /(float)md2Texture->width; 
		model->st[i].t = (float)stPtr[i].t /(float)md2Texture->height; 
	}
printf("malloc in line 109\n");	
	/*allocate the list of triangle indices*/
	triIndex = (meshIndex_t*)malloc(sizeof(meshIndex_t)*modelHeader->numTris); 
	 
	/*set total number of triangles*/
	model->numTriangles = modelHeader->numTris;
	model->triIndex = triIndex; 
	
	/*point to triangle indices in buffer*/
	bufIndexPtr = (meshIndex_t*)&buffer[modelHeader->offsetTris];
	
	/*create a mesh (triangle) list*/
	//for(j = 0; j < model->numFrames; ++j)
	{
		/*for all triangles in each frame*/
		for(i = 0; i < modelHeader->numTris; ++i)
		{
			triIndex[i].meshIndex[0] = bufIndexPtr[i].meshIndex[0];
			triIndex[i].meshIndex[1] = bufIndexPtr[i].meshIndex[1];
			triIndex[i].meshIndex[2] = bufIndexPtr[i].meshIndex[2];
			triIndex[i].stIndex[0]   = bufIndexPtr[i].stIndex[0];
			triIndex[i].stIndex[1]   = bufIndexPtr[i].stIndex[1];
			triIndex[i].stIndex[2]   = bufIndexPtr[i].stIndex[2];	
		}
	}
	
	/*close file and free memory*/
	//fflush(filePtr); 
	//fclose(filePtr); 
	//free(buffer); 
	
	/*initialize animation veriables*/
	model->currentFrame = 0; 
	model->nextFrame = 1; 
	model->interpol = 0.0f; 
	
	return model; 
}

