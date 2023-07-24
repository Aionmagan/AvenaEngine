#include "../render.h"

#include <pspgu.h>
#include <pspgum.h>
#include <pspmoduleinfo.h>
#include <pspthreadman.h>
#include <math.h>

#define SW 640
#define SH 480

#define BUFF_WIDTH (512)
#define SCRN_WIDTH (480)
#define SCRN_HEIGHT (272)
#define OFFSET (2048) 

PSP_MODULE_INFO("PSP3D", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER|THREAD_ATTR_VFPU);

//#define BG_COLOR 0xff7f7f7f
int BG_COLOR = 0xff7f7f7f;

static unsigned int __attribute__((aligned(16))) list[262144];
static unsigned int buff = 0; 

int i; 

/*camera*/
ScePspFVector3 cpos;
ScePspFVector3 crot; 
/*camera*/

void render_init(float a, float n, float f)
{
 	void *buff1; 
	void *buff2; 
	void *zbuff; 
	
	/*creating the buffer | without vram.h*/ 
	buff1 = (void *)buff;
	buff += 4 * BUFF_WIDTH * SCRN_HEIGHT;
	
	buff2 = (void *)buff; 
	buff += 4 * BUFF_WIDTH * SCRN_HEIGHT; 
	
	zbuff = (void *)buff;
	buff += 2 * BUFF_WIDTH * SCRN_HEIGHT;  
	
	sceGuInit(); 
	sceGuStart(GU_DIRECT, list); 
	
	sceGuDrawBuffer(GU_PSM_8888, buff1, BUFF_WIDTH);
	sceGuDispBuffer(SCRN_WIDTH, SCRN_HEIGHT, buff2,BUFF_WIDTH); 
	sceGuDepthBuffer(zbuff, BUFF_WIDTH); 
	
	sceGuOffset(OFFSET-(SCRN_WIDTH/2), OFFSET-(SCRN_HEIGHT/2));
	sceGuViewport(OFFSET, OFFSET, SCRN_WIDTH, SCRN_HEIGHT);
	
	sceGuDepthRange(65535, 0);
	
	sceGuScissor(0, 0, SCRN_WIDTH, SCRN_HEIGHT);
	sceGuEnable(GU_SCISSOR_TEST); 
	
	sceGuDepthFunc(GU_GEQUAL);
	sceGuEnable(GU_DEPTH_TEST);
	//sceGuFrontFace(GU_CCW);
	sceGuShadeModel(GU_SMOOTH);
	//sceGuEnable(GU_CULL_FACE);
	sceGuEnable(GU_CLIP_PLANES);
	sceGuEnable(GU_TEXTURE_2D);
	sceGuFinish();
	sceGuSync(GU_SYNC_DONE, GU_SYNC_WHAT_DRAW); 
	
	sceDisplayWaitVblankStart();
	sceGuDisplay(GU_TRUE);
	
	//init perspective heres
	sceGumMatrixMode(GU_PROJECTION);
	sceGumLoadIdentity();
	sceGumPerspective(a, 16.0f/9.0f, n, f);
	
	sceGumMatrixMode(GU_VIEW);
	sceGumLoadIdentity();
	
	sceGumMatrixMode(GU_MODEL);
	sceGumLoadIdentity();               
             
	ScePspFVector3 eye;
	ScePspFVector3 center; 
	ScePspFVector3 up;

	eye.x = 0.0f; 
	eye.y = 9.0f;
	eye.z = 11.4f; 
	
	center.x = 0.0f; 
	center.y = 4.0f; 
	center.z = 0.0; 
	
	up.x = 0.0f; 
	up.y = 1.0f; 
	up.z = 0.0f; 
	
	sceGumLookAt(&eye, &center, &up);

              
}

void render_quit()
{
	sceGuTerm();
	sceKernelExitGame();
}

void render_cameraf(float tx, float ty, float tz, float rx, float ry, float rz)
{	
	crot.x = -ry * (GU_PI/180.0f);
	crot.y = -rx * (GU_PI/180.0f); 
	crot.z = -rz * (GU_PI/180.0f); 
	
	cpos.x = -tx; 
	cpos.y = -ty; 
	cpos.z = -tz; 
	
	sceGumLoadIdentity();	
	sceGumRotateXYZ(&crot);
	sceGumTranslate(&cpos);
}

void render_camerav(vec4_t* pos, vec4_t* rot)
{
	render_cameraf(pos->x, pos->y, pos->z, rot->x, rot->y, rot->z);
}

void render_begin()
{
	sceGuStart(GU_DIRECT, list);
	sceGuClearColor(BG_COLOR);
	sceGuClearDepth(0); 
	
	sceGuClear(GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT);
}

void render_ui_draw(obj_t* obj)
{
	sceGumPushMatrix(); 
	sceGumLoadIdentity();
		render_draw(obj);
	sceGumPopMatrix(); 
}
void render_draw(obj_t* obj)
{
	/*sceGumDrawArray(GU_TRIANGLES, GU_COLOR_8888|
	GU_VERTEX_32BITF|GU_INDEX_16BIT|GU_TRANSFORM_3D, 
	sizeof(verts*unsigned short), (void *));
	*/
	ScePspFVector3 pos;
	ScePspFVector3 rot; 
	ScePspFVector3 sca;
	
	ScePspFVector3 eye;
	ScePspFVector3 center; 
	ScePspFVector3 up;
/*	
	eye.x = 2.0f; 
	eye.y =  2.0f;
	eye.z = 1.0f; 
	
	center.x = 0; 
	center.y = 2; 
	center.z = 0; 
	
	up.x = 1; 
	up.y = 1; 
	up.z = 0; 
*/
	
	/*too lazy to write a function for this part*/
	pos.x = obj->pos.x; 
	pos.y = obj->pos.y; 
	pos.z = obj->pos.z; 
	/*
	rot.x = obj->rot.x * 0.98f * (GU_PI/180.0f); 
	rot.y = obj->rot.y * 0.98f * (GU_PI/180.0f);
	rot.z = obj->rot.z * 0.98f * (GU_PI/180.0f);
*/
	rot.x = obj->rot.x * (GU_PI/180.0f); 
	rot.y = obj->rot.y * (GU_PI/180.0f);
	rot.z = obj->rot.z * (GU_PI/180.0f);

	sca.x = obj->sca.x; 
	sca.y = obj->sca.y;
	sca.z = obj->sca.z;
	
	sceGumPushMatrix();
	//sceGumMatrixMode(GU_MODEL);
	//sceGumLoadIdentity();
		
	sceGumTranslate(&pos);
	sceGumRotateXYZ(&rot);
	sceGumScale(&sca);
	
	//sceGumPushMatrix();
	//sceGumLookAt(&eye, &center, &up);
	//sceGumPopMatrix();
	
	sceGuTexMode(GU_PSM_8888,0,0,0);
	sceGuTexImage(0,obj->texture.w, obj->texture.h, obj->texture.w, obj->texture.texture);
	//sceGuTexImage(0, 128, 128, 64, logo_start);
	sceGuTexFunc(GU_TFX_REPLACE,GU_TCC_RGBA);
	//sceGuTexEnvColor(0xffff00);
	sceGuTexFilter(GU_NEAREST,GU_NEAREST);
	sceGuTexScale(1.0f,1.0f);
	sceGuTexOffset(0.0f,0.0f);
	//sceGuAmbientColor(0xffffffff);

//GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D
	/*sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF|
								  GU_COLOR_8888|
								  GU_VERTEX_32BITF|
								  GU_TRANSFORM_3D|GU_INDEX_16BIT,
								  (3*obj->model->face_size), 
								  obj->model->v_index,
								  obj->model->mesh_data);
	*/							  
	sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF|
								  GU_COLOR_8888|
								  GU_VERTEX_32BITF|
								  GU_TRANSFORM_3D,
								  (3*obj->model->face_count), 
								  0,
								  obj->model->verts);
								 
	sceGumPopMatrix();	
}

/*texture scroll*/ 
void render_scroll_draw(obj_t* obj, float u, float v)
{
	/*sceGumDrawArray(GU_TRIANGLES, GU_COLOR_8888|
	GU_VERTEX_32BITF|GU_INDEX_16BIT|GU_TRANSFORM_3D, 
	sizeof(verts*unsigned short), (void *));
	*/
	ScePspFVector3 pos;
	ScePspFVector3 rot; 
	ScePspFVector3 sca;
	
	ScePspFVector3 eye;
	ScePspFVector3 center; 
	ScePspFVector3 up;
/*	
	eye.x = 2.0f; 
	eye.y =  2.0f;
	eye.z = 1.0f; 
	
	center.x = 0; 
	center.y = 2; 
	center.z = 0; 
	
	up.x = 1; 
	up.y = 1; 
	up.z = 0; 
*/
	
	/*too lazy to write a function for this part*/
	pos.x = obj->pos.x; 
	pos.y = obj->pos.y; 
	pos.z = obj->pos.z; 
	
	rot.x = obj->rot.x * (GU_PI/180.0f); 
	rot.y = obj->rot.y * (GU_PI/180.0f);
	rot.z = obj->rot.z * (GU_PI/180.0f);

	sca.x = obj->sca.x; 
	sca.y = obj->sca.y;
	sca.z = obj->sca.z;
	
	sceGumPushMatrix();
	//sceGumMatrixMode(GU_MODEL);
	//sceGumLoadIdentity();
		
	sceGumTranslate(&pos);
	sceGumRotateXYZ(&rot);
	sceGumScale(&sca);
	
	//sceGumPushMatrix();
	//sceGumLookAt(&eye, &center, &up);
	//sceGumPopMatrix();
	
	sceGuTexMode(GU_PSM_8888,0,0,0);
	sceGuTexImage(0,obj->texture.w, obj->texture.h, obj->texture.w, obj->texture.texture);
	//sceGuTexImage(0, 128, 128, 64, logo_start);
	sceGuTexFunc(GU_TFX_REPLACE,GU_TCC_RGBA);
	//sceGuTexEnvColor(0xffff00);
	sceGuTexFilter(GU_NEAREST,GU_NEAREST);
	sceGuTexScale(1.0f,1.0f);
	sceGuTexOffset(u, v);
	//sceGuAmbientColor(0xffffffff);

//GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D
	/*sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF|
								  GU_COLOR_8888|
								  GU_VERTEX_32BITF|
								  GU_TRANSFORM_3D|GU_INDEX_16BIT,
								  (3*obj->model->face_size), 
								  obj->model->v_index,
								  obj->model->mesh_data);
	*/							  
	sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF|
								  GU_COLOR_8888|
								  GU_VERTEX_32BITF|
								  GU_TRANSFORM_3D,
								  (3*obj->model->face_count), 
								  0,
								  obj->model->verts);
								 
	sceGumPopMatrix();	
}

void render_end()
{
	sceGuFinish();
	sceGuSync(GU_SYNC_DONE, GU_SYNC_WHAT_DRAW);
	sceDisplayWaitVblankStart(); 
	sceGuSwapBuffers(); 
}

void render_clear_z()
{
	sceGuClear(GU_DEPTH_BUFFER_BIT);
}

void render_bg_color(int r, int g, int b)
{
    unsigned int color;
	color = (0xff << 24) |  (b << 16) | (g << 8) | r;
	
	BG_COLOR = color; 
}
