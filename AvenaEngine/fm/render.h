#ifndef __RENDER_H__
#define __RENDER_H__

#include "obj.h" 

void render_init(float a, float n, float f);
void render_quit();

int render_get_light(int i);
void render_set_light(int i, float* ambi, float* diff, float* spec); 
void render_pos_light(int i, float x, float y, float z);
void render_dir_light(int i, float x, float y, float z, float*pos);

void render_ui_draw(obj_t* obj);
void render_tp_draw(obj_t* obj); /*uses render_draw() but with transparency on texture*/  
void render_tp_md2(objmd2_t* obj);
//void render_bb_draw(obj_t* obj);
void render_draw(obj_t* obj); 
void render_draw_mt(objmt_t* obj);
void render_tpmt_draw(objmt_t* obj); 
void render_wire_frame(); 
void render_aabb(aabb_t* box);

void render_camera_lookat(float tx, float ty, float tz, float rx, float ry, float rz, float d);
void render_cameraf(float tx, float ty, float tz, float rx, float ry, float rz);
void render_camerav(vec4_t* pos, vec4_t* rot); 

//void render_fps_camera(float tx, float ty, float tz, float rx, float ry, float rz); 
void render_lerp_md2(objmd2_t* obj);
//void render_md2(objmd2_t* obj, int fn); 
/*texture scroll*/ 
void render_scroll_draw(obj_t* obj, float u, float v);

void render_begin(); 
void render_end();
void render_clear_z(); 
void render_bg_color(int r, int g, int b);

#endif//__RENDER_H__
