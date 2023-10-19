#include "../render.h"
#include "../timer.h"

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#define SW 640
#define SH 480
/*renderer*/
SDL_Window *window;
SDL_Surface *wsurface;  
SDL_Surface *grid; 
//SDL_Event event;
SDL_GLContext context;  
int i; 
int wire_frame = 0;
/*renderer*/

/*camera*/
//float posx, posy, posz; 
//float rotx, roty, rotz; 
/*camera*/

void render_init(float a, float n, float f)
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO);
	
	window = SDL_CreateWindow("Avena Engine", SDL_WINDOWPOS_CENTERED, 
										  SDL_WINDOWPOS_CENTERED, 
										  SW, SH, SDL_WINDOW_OPENGL);
	//SDL_SetWindowFullscreen(window, 1); 
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    
    context = SDL_GL_CreateContext(window);
    
    glViewport(0, 0, SW, SH);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(a, ((GLfloat)SW/(GLfloat)SH), n, f);
    //glOrtho(-3.0f, 3.0f, -3.0f, 3.0f, n, f);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glClearColor(0.6f, 0.6f, .6f, .6f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    //glBlendFunc  (GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA);
    //glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glAlphaFunc(GL_NOTEQUAL, 0.0f);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE);
  	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glEnable(GL_TEXTURE_2D);
 
 /*   
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
   */           
}

void render_quit()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void render_cameraf(float tx, float ty, float tz, float rx, float ry, float rz)
{
    glLoadIdentity(); 
    //glTranslatef(-tx, -ty, -tz);
	glRotatef(-ry, 1.0f, 0.0f, 0.0f);
	glRotatef(-rz, 0.0f, 0.0f, 1.0f);  
	glRotatef(-rx, 0.0f, 1.0f, 0.0f);
	
	glTranslatef(-tx, -ty, -tz);
	
	//roty = ry; 
	//rotx = rx; 
/*	
	glLoadIdentity(); 
    glTranslatef(-tx, -ty, -tz);
	glRotatef(-rx, 0.0f, 1.0f, 0.0f);
	glRotatef(-ry, 1.0f, 0.0f, 0.0f);
	
	//glRotatef(rx, 0.0f, 1.0f, 0.0f);
	//glRotatef(ry, 1.0f, 0.0f, 0.0f);
	//glRotatef(-rz, 0.0f, 0.0f, 1.0f);  
	glTranslatef(tx, ty, tz);
*/
}

void render_camerav(vec4_t* pos, vec4_t* rot)
{
	render_cameraf(pos->x, pos->y, pos->z, rot->x, rot->y, rot->z);
}

/*void render_camera_lookat(float tx, float ty, float tz, float rx, float lax, float lay, float laz)
{
	glLoadIdentity(); 
	glTranslatef(-tx, -ty, -tz);
    glTranslatef(0, 0, 0);
    //glTranslatef(-lax, -lay, -lax);
	glRotatef(rx, 0.0f, 1.0f, 0.0f);
	//glRotatef(-ry, 1.0f, 0.0f, 0.0f);
	//glRotatef(-rz, 0.0f, 0.0f, 1.0f);  
	glTranslatef(lax, lay, lax);
}*/

void render_camera_lookat(float tx, float ty, float tz, float rx, float ry, float rz, float d)
{
	glLoadIdentity();
	//glTranslatef(-tx, -ty, -tz-6.0f);
	glTranslatef(0.0f, 0.0f, -d);
	glRotatef(-rx, 0.0f, 1.0f, 0.0f);
	//glTranslatef(tx, ty, tz);
	glTranslatef(-tx, -ty, -tz);
}


int render_get_light(int i)
{
	switch(i)
	{
		case 0:
			return GL_LIGHT0; 
		case 1:
			return GL_LIGHT1; 
		case 2: 
			return GL_LIGHT2; 
		default:
			printf("WARNING: this light %d is unsupported in this platform\n will return light 0", i);
			return GL_LIGHT0; 
	}
}

void render_set_light(int i, float* ambi, float* diff, float* spec) 
{
        /*i is assumed to have been collected from render_get_light() first*/ 
        glLightfv(GL_LIGHT0+i, GL_AMBIENT, ambi);
        glLightfv(GL_LIGHT0+i, GL_DIFFUSE, diff);
        glLightfv(GL_LIGHT0+i, GL_SPECULAR, spec);
}

void render_pos_light(int i, float x, float y, float z)
{
	glPushMatrix();
	glLoadIdentity();
	static float lp[4];
	lp[0] = x; 
	lp[1] = y; 
	lp[2] = z;
	lp[3] = 1.0f;  
	//printf("lp = {%f, %f, %f}", lp[0] = x, lp[1] = y, lp[2] = z);
	glLightfv(GL_LIGHT0+i, GL_POSITION, lp);
	glPopMatrix();
}

void render_dir_light(int i, float x, float y, float z, float* pos)
{
	glPushMatrix();
	glLoadIdentity();
	
	static float lp[4]={0};
	static float ld[4]; 
	ld[0] = x; 
	ld[1] = y; 
	ld[2] = z;
	ld[3] = 1.0f;  
	
	if (pos != NULL)
	{
		lp[0] = pos[0]; 
		lp[1] = pos[1]; 
		lp[2] = pos[2];
		lp[3] = 0.0f; 
	}	
	
	printf("lp = {%f, %f, %f}", lp[0] = x, lp[1] = y, lp[2] = z);
	glLightfv(GL_LIGHT0+i, GL_POSITION, lp);
	glLightfv(GL_LIGHT0+i, GL_SPOT_DIRECTION, ld);
	
	glPopMatrix();
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

void render_tpmt_draw(objmt_t* obj)
{
	glEnable(GL_ALPHA_TEST);
	//glEnable(GL_BLEND);
		render_draw_mt(obj);	
	//glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
}

void render_tp_md2(objmd2_t* obj)
{
	glEnable(GL_BLEND);
		render_lerp_md2(obj);	
	glDisable(GL_BLEND);
}

void render_wire_frame()
{
	wire_frame ^= 1; 
}

void render_draw(obj_t* obj)
{
	    glPushMatrix();
	    
	    glTranslatef(obj->pos.x, obj->pos.y, obj->pos.z);
	    glScalef(obj->sca.x, obj->sca.y, obj->sca.z); 
	    glRotatef(obj->rot.x, 1.0f, 0.0f, 0.0f);
	    glRotatef(obj->rot.y, 0.0f, 1.0f, 0.0f); 
	    glRotatef(obj->rot.z, 0.0f, 0.0f, 1.0f); 
	   //glRotatef(-roty, 0.0f, 0.0f, 0.0f); 
	   //glRotatef(-rotx, 0.0f, 1.0f, 0.0f); 

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
		
#if defined(__DEBUG__)
		if (obj->box.is_active)
		{ 
			glDisable(GL_TEXTURE_2D);

			glLineWidth(4);
			glBegin(GL_LINES);
				
				glColor3f(0.0f, 1.0f, 0.0f);
				
				if(obj->box.hit)
					glColor3f(1.0f, 0.0f, 0.0f); 
				
				//top square
				glVertex3f(obj->box.max.x, obj->box.max.y, obj->box.max.z);
				glVertex3f(obj->box.min.x, obj->box.max.y, obj->box.max.z);
				
				glVertex3f(obj->box.min.x, obj->box.max.y, obj->box.max.z);
				glVertex3f(obj->box.min.x, obj->box.max.y, obj->box.min.z);
				
				glVertex3f(obj->box.min.x, obj->box.max.y, obj->box.min.z);
				glVertex3f(obj->box.max.x, obj->box.max.y, obj->box.min.z);
				
				glVertex3f(obj->box.max.x, obj->box.max.y, obj->box.min.z);
				glVertex3f(obj->box.max.x, obj->box.min.y, obj->box.min.z);
				
				glVertex3f(obj->box.max.x, obj->box.max.y, obj->box.max.z);
				glVertex3f(obj->box.max.x, obj->box.min.y, obj->box.max.z);
				
				glVertex3f(obj->box.max.x, obj->box.max.y, obj->box.max.z);
				glVertex3f(obj->box.max.x, obj->box.max.y, obj->box.min.z);
				//top square 
				
				//bottom square
				glVertex3f(obj->box.min.x, obj->box.min.y, obj->box.min.z);
				glVertex3f(obj->box.max.x, obj->box.min.y, obj->box.min.z);

				glVertex3f(obj->box.max.x, obj->box.min.y, obj->box.min.z);
				glVertex3f(obj->box.max.x, obj->box.min.y, obj->box.max.z);

				glVertex3f(obj->box.max.x, obj->box.min.y, obj->box.max.z);
				glVertex3f(obj->box.min.x, obj->box.min.y, obj->box.max.z);
				
				glVertex3f(obj->box.min.x, obj->box.min.y, obj->box.max.z);
				glVertex3f(obj->box.min.x, obj->box.max.y, obj->box.max.z);
				
				glVertex3f(obj->box.min.x, obj->box.min.y, obj->box.min.z);
				glVertex3f(obj->box.min.x, obj->box.max.y, obj->box.min.z);
				
				glVertex3f(obj->box.min.x, obj->box.min.y, obj->box.min.z);
				glVertex3f(obj->box.min.x, obj->box.min.y, obj->box.max.z);
				//bottom square
				
			glEnd();
			glEnable(GL_TEXTURE_2D);
		}else 
		{
			glPushMatrix();
			glTranslatef(obj->pos.x, obj->pos.y, obj->pos.z);
	    	glScalef(obj->sca.x, obj->sca.y, obj->sca.z); 
	    	glRotatef(obj->rot.x, 1.0f, 0.0f, 0.0f);
	    	glRotatef(obj->rot.y, 0.0f, 1.0f, 0.0f); 
	    	glRotatef(obj->rot.z, 0.0f, 0.0f, 1.0f); 
			glDisable(GL_TEXTURE_2D);

			glLineWidth(2);
			glBegin(GL_LINES);
				
			glColor3f(0.0f, 0.5f, 1.0f);				
			
			//if(obj->box.hit)
				//glColor3f(1.0f, 0.0f, 0.0f); 
				
			for(i = 0; i < obj->model->face_count; ++i)
			{
				 glVertex3f(obj->model->verts[obj->model->faces[i].vx].x,
							obj->model->verts[obj->model->faces[i].vx].y,
							obj->model->verts[obj->model->faces[i].vx].z);
							
				 glVertex3f(obj->model->verts[obj->model->faces[i].vy].x,
							obj->model->verts[obj->model->faces[i].vy].y,
							obj->model->verts[obj->model->faces[i].vy].z);
							
				 glVertex3f(obj->model->verts[obj->model->faces[i].vy].x,
				 		    obj->model->verts[obj->model->faces[i].vy].y,
						    obj->model->verts[obj->model->faces[i].vy].z);
							
				 glVertex3f(obj->model->verts[obj->model->faces[i].vz].x,
							obj->model->verts[obj->model->faces[i].vz].y,
							obj->model->verts[obj->model->faces[i].vz].z);
							
                 glVertex3f(obj->model->verts[obj->model->faces[i].vz].x,
							obj->model->verts[obj->model->faces[i].vz].y,
							obj->model->verts[obj->model->faces[i].vz].z);
						
				 glVertex3f(obj->model->verts[obj->model->faces[i].vx].x,
							obj->model->verts[obj->model->faces[i].vx].y,
							obj->model->verts[obj->model->faces[i].vx].z);
			}
				
			glEnd();
			glEnable(GL_TEXTURE_2D);
			glPopMatrix();
		}
#endif 
}

void render_draw_mt(objmt_t* obj)
{
	if (!wire_frame)
	{
	    glPushMatrix();
 
	    glTranslatef(obj->pos.x, obj->pos.y, obj->pos.z);
	    glScalef(obj->sca.x, obj->sca.y, obj->sca.z); 
	    glRotatef(obj->rot.x, 1.0f, 0.0f, 0.0f);
	    glRotatef(obj->rot.y, 0.0f, 1.0f, 0.0f); 
	    glRotatef(obj->rot.z, 0.0f, 0.0f, 1.0f); 
	   //glRotatef(-roty, 0.0f, 0.0f, 0.0f); 
	   //glRotatef(-rotx, 0.0f, 1.0f, 0.0f); 
		for(int m = 0; m < obj->model->mesh_parts; ++m)
		{
			glMaterialfv(GL_FRONT, GL_DIFFUSE, obj->model->mats[m].diff);
			glMaterialfv(GL_FRONT, GL_SPECULAR, obj->model->mats[m].spec);
			//glMaterialfv(GL_FRONT, GL_AMBIENT, obj->model->mats[m].ambi);
			glMaterialfv(GL_FRONT, GL_EMISSION, obj->model->mats[m].emit);
			//glMaterialfv(GL_FRONT, GL_AMBIENT, obj->model->mats[m].ambi);
			
			glBindTexture(GL_TEXTURE_2D, obj->texture[m].tid);
			//printf("pos {%f, %f, %f}\n", obj->sca.x, obj->sca.y, obj->sca.z);
			glBegin(GL_TRIANGLES); 
			glColor3f(obj->dens, obj->dens, obj->dens);

			//for(int m = 0; m < obj->model->mesh_parts; ++m)
			//{
				//glBindTexture(GL_TEXTURE_2D, obj->texture[0].tid);
				for(i = 0; i < obj->model->face_count[m]; ++i)
				{				
					//printf("vertex {%f, %f, %f}\n", obj->model->verts[m][obj->model->faces[m][i].vx].x, obj->model->verts[m][obj->model->faces[m][i].vx].y,obj->model->verts[m][obj->model->faces[m][i].vx].z);
					glTexCoord2f(obj->model->uvs[obj->model->faces[m][i].ux].u, 
								 obj->model->uvs[obj->model->faces[m][i].ux].v);
								 
					 glNormal3f(obj->model->norms[obj->model->faces[m][i].nx].x,
								obj->model->norms[obj->model->faces[m][i].nx].y,
								obj->model->norms[obj->model->faces[m][i].nx].z);
								
					 glVertex3f(obj->model->verts[obj->model->faces[m][i].vx].x,
								obj->model->verts[obj->model->faces[m][i].vx].y,
								obj->model->verts[obj->model->faces[m][i].vx].z);
					
					glTexCoord2f(obj->model->uvs[obj->model->faces[m][i].uy].u, 
								 obj->model->uvs[obj->model->faces[m][i].uy].v);
								
					glNormal3f(obj->model->norms[obj->model->faces[m][i].ny].x,
							   obj->model->norms[obj->model->faces[m][i].ny].y,
							   obj->model->norms[obj->model->faces[m][i].ny].z);			
								
					 glVertex3f(obj->model->verts[obj->model->faces[m][i].vy].x,
								obj->model->verts[obj->model->faces[m][i].vy].y,
								obj->model->verts[obj->model->faces[m][i].vy].z);
							   
					glTexCoord2f(obj->model->uvs[obj->model->faces[m][i].uz].u, 
								 obj->model->uvs[obj->model->faces[m][i].uz].v);
								 
					glNormal3f(obj->model->norms[obj->model->faces[m][i].nz].x,
								obj->model->norms[obj->model->faces[m][i].nz].y,
								obj->model->norms[obj->model->faces[m][i].nz].z);
								
					 glVertex3f(obj->model->verts[obj->model->faces[m][i].vz].x,
								obj->model->verts[obj->model->faces[m][i].vz].y,
								obj->model->verts[obj->model->faces[m][i].vz].z);
								
										
				}
			
		glEnd();
		}
		glPopMatrix();
	}
#if 0//defined(__DEBUG__)
	    if (obj->wire) 
		{
			glPushMatrix();
			glTranslatef(obj->pos.x, obj->pos.y, obj->pos.z);
	    	glScalef(obj->sca.x, obj->sca.y, obj->sca.z); 
	    	glRotatef(obj->rot.x, 1.0f, 0.0f, 0.0f);
	    	glRotatef(obj->rot.y, 0.0f, 1.0f, 0.0f); 
	    	glRotatef(obj->rot.z, 0.0f, 0.0f, 1.0f); 
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_LIGHTING);

			glLineWidth(4);
			glBegin(GL_LINES);
				
			glColor3f(0.0f, 0.0f, 0.0f);				
			
			if (wire_frame)
				glColor3f(0.6f, 0.6f, 0.6f);								
			//if(obj->box.hit)
				//glColor3f(1.0f, 0.0f, 0.0f); 
			for(int m = 0; m < obj->model->mesh_parts; ++i)
			{	
				for(i = 0; i < obj->model->face_count[m]; ++i)
				{
					 glVertex3f(obj->model->verts[obj->model->faces[i].vx].x,
								obj->model->verts[obj->model->faces[i].vx].y,
								obj->model->verts[obj->model->faces[i].vx].z);
								
					 glVertex3f(obj->model->verts[obj->model->faces[i].vy].x,
								obj->model->verts[obj->model->faces[i].vy].y,
								obj->model->verts[obj->model->faces[i].vy].z);
								
					 glVertex3f(obj->model->verts[obj->model->faces[i].vy].x,
					 		    obj->model->verts[obj->model->faces[i].vy].y,
								obj->model->verts[obj->model->faces[i].vy].z);
								
					 glVertex3f(obj->model->verts[obj->model->faces[i].vz].x,
								obj->model->verts[obj->model->faces[i].vz].y,
								obj->model->verts[obj->model->faces[i].vz].z);
								
		             glVertex3f(obj->model->verts[obj->model->faces[i].vz].x,
								obj->model->verts[obj->model->faces[i].vz].y,
								obj->model->verts[obj->model->faces[i].vz].z);
							
					 glVertex3f(obj->model->verts[obj->model->faces[i].vx].x,
								obj->model->verts[obj->model->faces[i].vx].y,
								obj->model->verts[obj->model->faces[i].vx].z);
				}
			}
			
			glEnd();
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_LIGHTING);
			glPopMatrix();
		}
#endif 
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
/*
void render_bb_draw(obj_t* obj)
{
	glEnable(GL_BLEND);
		glPushMatrix();
	    //glLoadIdentity(); 
	    glTranslatef(obj->pos.x, obj->pos.y, obj->pos.z);
	    glScalef(obj->sca.x, obj->sca.y, obj->sca.z); 
	    glRotatef(0, 1.0f, 0.0f, 0.0f);
	    glRotatef(0, 0.0f, 1.0f, 0.0f); 
	    glRotatef(0, 0.0f, 0.0f, 1.0f); 
	   //glRotatef(-roty, 0.0f, 0.0f, 0.0f); 
	   //glRotatef(-rotx, 0.0f, 1.0f, 0.0f); 

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
	glDisable(GL_BLEND);
}
*/
void render_lerp_md2(objmd2_t* obj)
{
	vector3_t* pointList; 
	vector3_t* nextPointList; 
	int i; 
	float x1, y1, z1; 
	float x2, y2, z2; 
	modelData_t* model = obj->model; 
	
	vector3_t vertex[3];
	
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
	
	pointList = &model->pointList[model->numPoints * obj->current_frame];
	nextPointList = &model->pointList[model->numPoints * obj->next_frame];
	//printf("pointList[0].point[0] = %f\n",pointList[0].point[0]);
	glPushMatrix();
	glTranslatef(obj->pos.x, obj->pos.y, obj->pos.z);
	glScalef(obj->sca.x, obj->sca.y, obj->sca.z); 
	glRotatef(obj->rot.x, 1.0f, 0.0f, 0.0f);
	glRotatef(obj->rot.y, 0.0f, 1.0f, 0.0f); 
	glRotatef(obj->rot.z, 0.0f, 0.0f, 1.0f); 
	
	glBindTexture(GL_TEXTURE_2D, model->modelTex.texID);
	glBegin(GL_TRIANGLES);
	
		for(i = 0; i < model->numTriangles; ++i)
		{
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
			
			glTexCoord2f(model->st[model->triIndex[i].stIndex[0]].s,
						 model->st[model->triIndex[i].stIndex[0]].t);
			
			glVertex3fv(vertex[0].point);

					   
			glTexCoord2f(model->st[model->triIndex[i].stIndex[2]].s,
						 model->st[model->triIndex[i].stIndex[2]].t);

			glVertex3fv(vertex[2].point);
			
			
			glTexCoord2f(model->st[model->triIndex[i].stIndex[1]].s,
						 model->st[model->triIndex[i].stIndex[1]].t);
			
			glVertex3fv(vertex[1].point);
		}
		glEnd();
		glPopMatrix();
		
	obj->lerp += obj->anim_state[obj->anim_select].fps * time_delta_time();
	
#if defined(__DEBUG__)
		if (obj->box.is_active)
		{ 
			glDisable(GL_TEXTURE_2D);

			glLineWidth(4);
			glBegin(GL_LINES);
				
				glColor3f(0.0f, 1.0f, 0.0f);
				
				if(obj->box.hit)
					glColor3f(1.0f, 0.0f, 0.0f); 
				
				//top square
				glVertex3f(obj->box.max.x, obj->box.max.y, obj->box.max.z);
				glVertex3f(obj->box.min.x, obj->box.max.y, obj->box.max.z);
				
				glVertex3f(obj->box.min.x, obj->box.max.y, obj->box.max.z);
				glVertex3f(obj->box.min.x, obj->box.max.y, obj->box.min.z);
				
				glVertex3f(obj->box.min.x, obj->box.max.y, obj->box.min.z);
				glVertex3f(obj->box.max.x, obj->box.max.y, obj->box.min.z);
				
				glVertex3f(obj->box.max.x, obj->box.max.y, obj->box.min.z);
				glVertex3f(obj->box.max.x, obj->box.min.y, obj->box.min.z);
				
				glVertex3f(obj->box.max.x, obj->box.max.y, obj->box.max.z);
				glVertex3f(obj->box.max.x, obj->box.min.y, obj->box.max.z);
				
				glVertex3f(obj->box.max.x, obj->box.max.y, obj->box.max.z);
				glVertex3f(obj->box.max.x, obj->box.max.y, obj->box.min.z);
				//top square 
				
				//bottom square
				glVertex3f(obj->box.min.x, obj->box.min.y, obj->box.min.z);
				glVertex3f(obj->box.max.x, obj->box.min.y, obj->box.min.z);

				glVertex3f(obj->box.max.x, obj->box.min.y, obj->box.min.z);
				glVertex3f(obj->box.max.x, obj->box.min.y, obj->box.max.z);

				glVertex3f(obj->box.max.x, obj->box.min.y, obj->box.max.z);
				glVertex3f(obj->box.min.x, obj->box.min.y, obj->box.max.z);
				
				glVertex3f(obj->box.min.x, obj->box.min.y, obj->box.max.z);
				glVertex3f(obj->box.min.x, obj->box.max.y, obj->box.max.z);
				
				glVertex3f(obj->box.min.x, obj->box.min.y, obj->box.min.z);
				glVertex3f(obj->box.min.x, obj->box.max.y, obj->box.min.z);
				
				glVertex3f(obj->box.min.x, obj->box.min.y, obj->box.min.z);
				glVertex3f(obj->box.min.x, obj->box.min.y, obj->box.max.z);
				//bottom square
				
			glEnd();
			glEnable(GL_TEXTURE_2D);
			glColor3f(1.0f, 1.0f, 1.0f);
		}
#endif 
}

void render_aabb(aabb_t* box)
{
		if (box->is_active)
		{ 
			glDisable(GL_TEXTURE_2D);

			glLineWidth(4);
			glBegin(GL_LINES);
				
				glColor3f(0.0f, 1.0f, 0.0f);
				
				if(box->hit)
					glColor3f(1.0f, 0.0f, 0.0f); 
				
				//top square
				glVertex3f(box->max.x, box->max.y, box->max.z);
				glVertex3f(box->min.x, box->max.y, box->max.z);
				
				glVertex3f(box->min.x, box->max.y, box->max.z);
				glVertex3f(box->min.x, box->max.y, box->min.z);
				
				glVertex3f(box->min.x, box->max.y, box->min.z);
				glVertex3f(box->max.x, box->max.y, box->min.z);
				
				glVertex3f(box->max.x, box->max.y, box->min.z);
				glVertex3f(box->max.x, box->min.y, box->min.z);
				
				glVertex3f(box->max.x, box->max.y, box->max.z);
				glVertex3f(box->max.x, box->min.y, box->max.z);
				
				glVertex3f(box->max.x, box->max.y, box->max.z);
				glVertex3f(box->max.x, box->max.y, box->min.z);
				//top square 
				
				//bottom square
				glVertex3f(box->min.x, box->min.y, box->min.z);
				glVertex3f(box->max.x, box->min.y, box->min.z);

				glVertex3f(box->max.x, box->min.y, box->min.z);
				glVertex3f(box->max.x, box->min.y, box->max.z);

				glVertex3f(box->max.x, box->min.y, box->max.z);
				glVertex3f(box->min.x, box->min.y, box->max.z);
				
				glVertex3f(box->min.x, box->min.y, box->max.z);
				glVertex3f(box->min.x, box->max.y, box->max.z);
				
				glVertex3f(box->min.x, box->min.y, box->min.z);
				glVertex3f(box->min.x, box->max.y, box->min.z);
				
				glVertex3f(box->min.x, box->min.y, box->min.z);
				glVertex3f(box->min.x, box->min.y, box->max.z);
				//bottom square
				
			glEnd();
			glEnable(GL_TEXTURE_2D);
		}
}

void render_end()
{
	SDL_GL_SwapWindow(window); 
}

void render_clear_z()
{
	glClear(GL_DEPTH_BUFFER_BIT); 
}

void render_bg_color(int r, int g, int b)
{
	glClearColor(r/255.0f, g/255.0f, b/255.0f, 1.0f);
}
