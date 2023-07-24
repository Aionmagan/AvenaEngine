#ifndef __MD2_H__
#define __MD2_H__

#include "vec3.h" 

#define ANIMSTATE0 0
#define ANIMSTATE1 1
#define ANIMSTATE2 2
#define ANIMSTATE3 3
#define ANIMSTATE4 4
#define ANIMSTATE5 5
#define ANIMSTATE6 6
#define ANIMSTATE7 7
#define ANIMSTATE8 8
#define ANIMSTATE9 9

typedef struct
{
	int start;
	int end; 
	int fps; 
}anim_state_t; 

/*MD2 stuff should update to my standards later*/ 

typedef struct 
{
	int ident;       //identifies as MD2 file "IDP2"
	int version;     //should be equals to 8
	int skinwidth;   //width of texture
	int skinheight;  //height of texture
	int framesize;   //number of 'bytes' per frame
	int numSkins;    //number of textures
	int numXYZ;      //number of points
	int numST;       //number of texture coords
	int numTris;     //number of trianges
	int numGLcmds;   //number of openGL commands
	int numFrames;   //total number of frames
	int offsetSkins; //offset to skin names (64 bytes each)
	int offsetST;    //offset to texture s - t values
	int offsetTris;  //offset to triangles mesh 
	int offsetFrames;//offset of frame data (poitns)
	int offsetGLcmds; //type of openGL commands to use
	int offsetEnd;   //end of file
}modelHeader_t;

enum texTypes_t
{
	PSX, BMP, TGA, PNG
};

typedef struct
{
	enum texTypes_t textureType; /*the type of image file this texture is*/ 
	
	int width; /*width fo texture*/
	int height; /*height of texture*/ 
	long int scaleWidth; /*scaled width for PCX images*/ 
	long int scaleHeight; /*scaled height for PCX images*/ 
	unsigned int texID; /*the texture object id of this texture*/ 
	unsigned char* data; /*the texture data*/ 
	unsigned char* palette; /*palette for texture (if it exist)*/
}texture_t; 

typedef struct
{
	float s; /*s coordinate*/
	float t; /*t coordinate*/
}texCoord_t; 

typedef struct
{
	short s; /*s index*/
	short t; /*t index*/
}stIndex_t; 

typedef struct
{
	unsigned char v[3];         // the point info
	unsigned char normalIndex;  //not used
}framePoint_t; 

typedef struct
{
	float scale[3];      //scaling for frame vertices
	float translate[3]; //translation for frame vertices
	char name[16];       //name of model
	framePoint_t fp[1];  //beginning for frame vertex list
}frame_t;

typedef struct
{
	unsigned short meshIndex[3]; //vertex indices
	unsigned short stIndex[3];   //texture-coordinate indices
}meshIndex_t;

typedef struct
{
	int numFrames;            // number of frames
	int numPoints;            //number of vertices
	int numTriangles;         //number of triangles
	int numST;                //number of texture coordinates 
	int frameSize;            //size of each frame in bytes
	int texWidth, texHeight;  //texture width, height
	int currentFrame;         //current frame number in animation
	int nextFrame;            //nex frame number in animation
	float interpol;           //percent throught current frame
	meshIndex_t* triIndex;         //triangle list
	texCoord_t* st;           //texture coordinate list
	vector3_t* pointList;      //vertex list
	texture_t modelTex;      //texture data
}modelData_t; 

modelData_t* LoadMD2Model(char* filename, char* textureName);

#endif//__MD2_H__
