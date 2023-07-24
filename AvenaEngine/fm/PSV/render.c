#include "../render.h"

#include <vitaGL.h>
#include <math.h>

#define SW 640
#define SH 480

static int i; 

/*camera*/
static float posx, posy, posz; 
static float rotx, roty, rotz; 
/*camera*/

void render_init(float a, float n, float f)
{
    vglInit(0x800000);
	
	vglWaitVblankStart(GL_TRUE);
	
    //glViewport(0, 0, SW, SH);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(a, ((GLfloat)SW/(GLfloat)SH), n, f);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glClearColor(0.6f, 0.6f, .6f, .6f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    glEnable(GL_TEXTURE_2D);
    
    GLdouble eyex = 0.0f, 
    		 eyey = 9.0f, 
    		 eyez = 11.8f,
             cenx = 0.0f, 
             ceny = 4.0f, 
             cenz = 0.0f, 
             upx  = 0.0f, 
             upy  = 1.0f, 
             upz  = 0.0f; 
             
             
   
    gluLookAt(eyex, eyey, eyez, 
              cenx, ceny, cenz, 
              upx, upy, upz);
              
}

void render_quit()
{
	vglEnd(); 
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

void render_begin()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void render_ui_draw(obj_t* obj)
{
	glPushMatrix(); 
	glLoadIdentity(); 
		render_draw(obj);
	glPopMatrix(); 
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
			
			for(i = 0; i < obj->model->face_count; ++i)
			{
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

void render_end()
{
	vglSwapBuffers(GL_FALSE); 
}

void render_clear_z()
{
	glClear(GL_DEPTH_BUFFER_BIT); 
}

void render_bg_color(int r, int g, int b)
{
	glClearColor(r/255.0f, g/255.0f, b/255.0f, 1.0f);
}
