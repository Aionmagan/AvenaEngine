#include "../render.h"
#include "../timer.h" 

//#include <SDL2/SDL.h>
//#include <GL/gl.h>
//#include <GL/glu.h>

#include <kos.h>

#include "GL/gl.h"
#include "GL/glu.h"
#include "GL/glut.h"
#include "GL/glkos.h"
#include <math.h>

#define SW 640
#define SH 480

extern uint8 romdisk[];
KOS_INIT_FLAGS(INIT_DEFAULT);
KOS_INIT_ROMDISK(romdisk);

int i; 

/*camera*/ 
float posx, posy, posz; 
float rotx, roty, rotz; 
/*camera*/ 

/*MD2*/
vector3_t* pointList; 
vector3_t* nextPointList; 

float x1, y1, z1; 
float x2, y2, z2; 

//modelData_t* model; 
vector3_t vertex[3];
/*MD2*/

void render_init(float a, float n, float f)
{
	glKosInit();
	
	glClearColor(0.6f, 0.6f, .6f, .6f);
    glClearDepth(1.0);
   
    //glDepthFunc(GL_LEQUAL);				// The Type Of Depth Test To Do
    //glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
    //glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading
    //glEnable(GL_TEXTURE_2D);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(a, ((GLfloat)SW/(GLfloat)SH), n, f);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    glFrontFace(GL_CCW); 
    
    glEnable(GL_CULL_FACE);
    
    
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    
    glEnable(GL_TEXTURE_2D);
  
  /*  
    GLdouble eyex = 0.0f, 
    		 eyey = 0.0f, 
    		 eyez = 0.0f,
             cenx = 0.0f, 
             ceny = 0.0f, 
             cenz = -10.0f, 
             upx  = 0.0f, 
             upy  = 1.0f, 
             upz  = 0.0f; 
             
             
   
    gluLookAt(eyex, eyey, eyez, 
              cenx, ceny, cenz, 
              upx, upy, upz);
    */          
}

void render_quit()
{
	return; 
}

void render_cameraf(float tx, float ty, float tz, float rx, float ry, float rz)
{
    glLoadIdentity(); 
	glRotatef(-rx, 0.0f, 1.0f, 0.0f);
	glRotatef(-ry, 1.0f, 0.0f, 0.0f);
	glRotatef(-rz, 0.0f, 0.0f, 1.0f);  
	glTranslatef(-tx, -ty, -tz);
}

void render_camerav(vec4_t* pos, vec4_t* rot)
{
	render_cameraf(pos->x, pos->y, pos->z, rot->x, rot->y, rot->z);
}

void render_camera_lookat(float tx, float ty, float tz, float rx, float ry, float rz, float d)
{
	glLoadIdentity();
	//glTranslatef(-tx, -ty, -tz-6.0f);
	glTranslatef(0.0f, 0.0f, -d);
	glRotatef(-ry, 1.0f, 0.0f, 0.0f);
	glRotatef(-rx, 0.0f, 1.0f, 0.0f);
	//glTranslatef(tx, ty, tz);
	glTranslatef(-tx, -ty, -tz);
}


void render_begin()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void render_ui_draw(obj_t* obj)
{
	glEnable(GL_BLEND);
	glPushMatrix(); 
	glLoadIdentity(); 
		render_draw(obj);
	glPopMatrix(); 
	glDisable(GL_BLEND);
}

void render_tp_draw(obj_t* obj)
{
	glEnable(GL_BLEND); 
		render_draw(obj);
	glDisable(GL_BLEND);
}

void render_draw(obj_t* obj)
{
	    glPushMatrix();
	    
	    glTranslatef(obj->pos.x, obj->pos.y, obj->pos.z);
	    glScalef(obj->sca.x, obj->sca.y, obj->sca.z); 
	    glRotatef(obj->rot.x, 1.0f, 0.0f, 0.0f);
	    glRotatef(obj->rot.y, 0.0f, 1.0f, 0.0f); 
	    glRotatef(obj->rot.z, 0.0f, 0.0f, 1.0f); 

		glBindTexture(GL_TEXTURE_2D, obj->texture.tid);
		glBegin(GL_TRIANGLES); 
			glColor3f(obj->dens, obj->dens, obj->dens);
			//glColor3f(1.0f, 1.0f, 1.0f);
			
			for(i = 0; i < obj->model->face_count; ++i)
			{
				//glColor3f(r, g, b);
				glTexCoord2f(obj->model->uvs[obj->model->faces[i].ux].u, 
							 obj->model->uvs[obj->model->faces[i].ux].v);
							
				 glVertex3f(obj->model->verts[obj->model->faces[i].vx].x,
							obj->model->verts[obj->model->faces[i].vx].y,
							obj->model->verts[obj->model->faces[i].vx].z);
				
				glTexCoord2f(obj->model->uvs[obj->model->faces[i].uy].u, 
							 obj->model->uvs[obj->model->faces[i].uy].v);
							
				 glVertex3f(obj->model->verts[obj->model->faces[i].vy].x,
							obj->model->verts[obj->model->faces[i].vy].y,
							obj->model->verts[obj->model->faces[i].vy].z);
						   
				glTexCoord2f(obj->model->uvs[obj->model->faces[i].uz].u, 
							 obj->model->uvs[obj->model->faces[i].uz].v);
							
				 glVertex3f(obj->model->verts[obj->model->faces[i].vz].x,
							obj->model->verts[obj->model->faces[i].vz].y,
							obj->model->verts[obj->model->faces[i].vz].z);
			}
		glEnd();
		glPopMatrix();
		
}

/*texture scroll*/ 
void render_scroll_draw(obj_t* obj, float u, float v)
{
	    glPushMatrix();
	    
	    glTranslatef(obj->pos.x, obj->pos.y, obj->pos.z);
	    glScalef(obj->sca.x, obj->sca.y, obj->sca.z); 
	    glRotatef(obj->rot.x, 1.0f, 0.0f, 0.0f);
	    glRotatef(obj->rot.y, 0.0f, 1.0f, 0.0f); 
	    glRotatef(obj->rot.z, 0.0f, 0.0f, 1.0f); 

		glBindTexture(GL_TEXTURE_2D, obj->texture.tid);
		glBegin(GL_TRIANGLES);
			glColor3f(obj->dens, obj->dens, obj->dens);
			for(i = 0; i < obj->model->face_count; ++i)
			{
				//glColor3f(r, g, b);
				glTexCoord2f(obj->model->uvs[obj->model->faces[i].ux].u+u, 
							 obj->model->uvs[obj->model->faces[i].ux].v+v);
							
				 glVertex3f(obj->model->verts[obj->model->faces[i].vx].x,
							obj->model->verts[obj->model->faces[i].vx].y,
							obj->model->verts[obj->model->faces[i].vx].z);
				
				glTexCoord2f(obj->model->uvs[obj->model->faces[i].uy].u+u, 
							 obj->model->uvs[obj->model->faces[i].uy].v+v);
							
				 glVertex3f(obj->model->verts[obj->model->faces[i].vy].x,
							obj->model->verts[obj->model->faces[i].vy].y,
							obj->model->verts[obj->model->faces[i].vy].z);
						   
				glTexCoord2f(obj->model->uvs[obj->model->faces[i].uz].u+u, 
							 obj->model->uvs[obj->model->faces[i].uz].v+v);
							
				 glVertex3f(obj->model->verts[obj->model->faces[i].vz].x,
							obj->model->verts[obj->model->faces[i].vz].y,
							obj->model->verts[obj->model->faces[i].vz].z);
			}
		glEnd();
		glPopMatrix();
}


void render_lerp_md2(objmd2_t* obj)
{
	//model = obj->model; 
	//vector3_t vertex[3];
	
	//if (fabs(obj->pos.x - posx) > 5.0f || fabs(obj->pos.z - posz) > 12.0f)
		//return; 
	
		//printf("camera to point distance = %f\n",(obj->pos.z - posz));
	
	if (obj->last_anim_select != obj->anim_select)
	{
		obj->last_anim_select = obj->anim_select; 
		obj->current_frame = obj->anim_state[obj->anim_select].start; 
		obj->next_frame = obj->current_frame + 1; 
	}

	if (obj->lerp >= 1.0)
	{
		//model->interpol = 0.0f; 
		obj->lerp = 0.0f; 
		//model->currentFrame++; 
		obj->current_frame++; 
		obj->next_frame++; 
		
		if (obj->current_frame >= obj->anim_state[obj->anim_select].end)
			obj->current_frame = obj->anim_state[obj->anim_select].start;  
		
		if (obj->next_frame >= obj->anim_state[obj->anim_select].end)
			obj->next_frame = obj->anim_state[obj->anim_select].start;   
		//printf("");
		//if (model->currentFrame >= model->numFrames-2)
			//model->currentFrame = 0; 
			//printf("numFrames = %d\n", model->numFrames);
		//obj->next_frame = obj->current_frame+1; 
		//model->nextFrame = model->currentFrame+1; 
		
		//if (model->nextFrame >= model->numFrames-2)
			//model->nextFrame = 0; 
	}
	
	pointList = &obj->model->pointList[obj->model->numPoints * obj->current_frame];
	nextPointList = &obj->model->pointList[obj->model->numPoints * obj->next_frame];
	//printf("pointList[0].point[0] = %f\n",pointList[0].point[0]);
	glPushMatrix();
	glTranslatef(obj->pos.x, obj->pos.y, obj->pos.z);
	glScalef(obj->sca.x, obj->sca.y, obj->sca.z); 
	glRotatef(obj->rot.x, 1.0f, 0.0f, 0.0f);
	glRotatef(obj->rot.y, 0.0f, 1.0f, 0.0f); 
	glRotatef(obj->rot.z, 0.0f, 0.0f, 1.0f); 
	
	glBindTexture(GL_TEXTURE_2D, obj->model->modelTex.texID);
	glBegin(GL_TRIANGLES);
	
		for(i = 0; i < obj->model->numTriangles; ++i)
		{
#if 0
			x1 = pointList[model->triIndex[i].meshIndex[0]].point[0];
			y1 = pointList[model->triIndex[i].meshIndex[0]].point[1];
			z1 = pointList[model->triIndex[i].meshIndex[0]].point[2];
			
			x2 = nextPointList[model->triIndex[i].meshIndex[0]].point[0];
			y2 = nextPointList[model->triIndex[i].meshIndex[0]].point[1];
			z2 = nextPointList[model->triIndex[i].meshIndex[0]].point[2];
			
			vertex[0].point[0] = x1+obj->lerp * (x2 - x1);
			vertex[0].point[1] = y1+obj->lerp * (y2 - y1); 
			vertex[0].point[2] = z1+obj->lerp * (z2 - z1);
			
			
			
			x1 = pointList[model->triIndex[i].meshIndex[2]].point[0];
			y1 = pointList[model->triIndex[i].meshIndex[2]].point[1];
			z1 = pointList[model->triIndex[i].meshIndex[2]].point[2];
			
			x2 = nextPointList[model->triIndex[i].meshIndex[2]].point[0];
			y2 = nextPointList[model->triIndex[i].meshIndex[2]].point[1];
			z2 = nextPointList[model->triIndex[i].meshIndex[2]].point[2];
			
			vertex[2].point[0] = x1+obj->lerp * (x2 - x1);
			vertex[2].point[1] = y1+obj->lerp * (y2 - y1);
			vertex[2].point[2] = z1+obj->lerp * (z2 - z1);
			
			
								 
			x1 = pointList[model->triIndex[i].meshIndex[1]].point[0];
			y1 = pointList[model->triIndex[i].meshIndex[1]].point[1];
			z1 = pointList[model->triIndex[i].meshIndex[1]].point[2];
			
			x2 = nextPointList[model->triIndex[i].meshIndex[1]].point[0];
			y2 = nextPointList[model->triIndex[i].meshIndex[1]].point[1];
			z2 = nextPointList[model->triIndex[i].meshIndex[1]].point[2];
			
			vertex[1].point[0] = x1+obj->lerp * (x2 - x1);
			vertex[1].point[1] = y1+obj->lerp * (y2 - y1);
			vertex[1].point[2] = z1+obj->lerp * (z2 - z1);
			
			
#else
			vertex[0].point[0] = pointList[obj->model->triIndex[i].meshIndex[0]].point[0] + obj->lerp * 
			                    (nextPointList[obj->model->triIndex[i].meshIndex[0]].point[0] - 
			                     pointList[obj->model->triIndex[i].meshIndex[0]].point[0]);
			                     
			vertex[0].point[1] = pointList[obj->model->triIndex[i].meshIndex[0]].point[1] + obj->lerp * 
								(nextPointList[obj->model->triIndex[i].meshIndex[0]].point[1] - 
								 pointList[obj->model->triIndex[i].meshIndex[0]].point[1]); 
								 
			vertex[0].point[2] = pointList[obj->model->triIndex[i].meshIndex[0]].point[2] + obj->lerp * 
								(nextPointList[obj->model->triIndex[i].meshIndex[0]].point[2] - 
								 pointList[obj->model->triIndex[i].meshIndex[0]].point[2]);
								 
								 
		   vertex[2].point[0] = pointList[obj->model->triIndex[i].meshIndex[2]].point[0] + obj->lerp * 
			                    (nextPointList[obj->model->triIndex[i].meshIndex[2]].point[0] - 
			                     pointList[obj->model->triIndex[i].meshIndex[2]].point[0]);
			                     
			vertex[2].point[1] = pointList[obj->model->triIndex[i].meshIndex[2]].point[1] + obj->lerp * 
								(nextPointList[obj->model->triIndex[i].meshIndex[2]].point[1] - 
								 pointList[obj->model->triIndex[i].meshIndex[2]].point[1]); 
								 
			vertex[2].point[2] = pointList[obj->model->triIndex[i].meshIndex[2]].point[2] + obj->lerp * 
								(nextPointList[obj->model->triIndex[i].meshIndex[2]].point[2] - 
								 pointList[obj->model->triIndex[i].meshIndex[2]].point[2]);
								 
								 
			vertex[1].point[0] = pointList[obj->model->triIndex[i].meshIndex[1]].point[0] + obj->lerp * 
			                    (nextPointList[obj->model->triIndex[i].meshIndex[1]].point[0] - 
			                     pointList[obj->model->triIndex[i].meshIndex[1]].point[0]);
			                     
			vertex[1].point[1] = pointList[obj->model->triIndex[i].meshIndex[1]].point[1] + obj->lerp * 
								(nextPointList[obj->model->triIndex[i].meshIndex[1]].point[1] - 
								 pointList[obj->model->triIndex[i].meshIndex[1]].point[1]); 
								 
			vertex[1].point[2] = pointList[obj->model->triIndex[i].meshIndex[1]].point[2] + obj->lerp * 
								(nextPointList[obj->model->triIndex[i].meshIndex[1]].point[2] - 
								 pointList[obj->model->triIndex[i].meshIndex[1]].point[2]);
#endif		 
								 
			glTexCoord2f(obj->model->st[obj->model->triIndex[i].stIndex[0]].s,
						 obj->model->st[obj->model->triIndex[i].stIndex[0]].t);
			
			glVertex3fv(vertex[0].point);
			//glVertex3f(vertex[0].point[0], vertex[0].point[1], vertex[0].point[2]);
					   
			glTexCoord2f(obj->model->st[obj->model->triIndex[i].stIndex[2]].s,
						 obj->model->st[obj->model->triIndex[i].stIndex[2]].t);

			glVertex3fv(vertex[2].point);
			//glVertex3f(vertex[2].point[0], vertex[2].point[1], vertex[2].point[2]);
			
			glTexCoord2f(obj->model->st[obj->model->triIndex[i].stIndex[1]].s,
						 obj->model->st[obj->model->triIndex[i].stIndex[1]].t);
			
			glVertex3fv(vertex[1].point);
			//glVertex3f(vertex[2].point[0], vertex[2].point[1], vertex[2].point[2]);
		}
		glEnd();
		glPopMatrix();
		
	obj->lerp += obj->anim_state[obj->anim_select].fps * time_delta_time();
}

void render_end()
{
	//printf("pvr_mem = %lu\n",pvr_mem_available());
	glKosSwapBuffers();
}

void render_clear_z()
{
	
	//glDepthMask(0);
	glClear(GL_DEPTH_BUFFER_BIT); 
	//glClearDepth(1.0);
	//glDepthMask(1);
	//glEnable(GL_DEPTH_TEST);
}
/*
void render_id_texture(tex_t* texture)
{
	int tid; 
	glGenTextures(1, &tid);
	glBindTexture(GL_TEXTURE_2D, tid);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->w, texture->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	texture->tid = tid; 
}
*/
void render_bg_color(int r, int g, int b)
{
	//scale from 0.0f to 1.0f
	glClearColor(r/255.0f, g/255.0f, b/255.0f, 1.0f);
}
