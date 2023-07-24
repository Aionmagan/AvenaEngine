#include "../mesh.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int load_mesh(char* str, mesh_t* mesh)
{
   FILE *file = NULL; 

   unsigned int vert_length = 0;
   unsigned int norm_length = 0;
   unsigned int uv_length   = 0; 
   unsigned int face_length = 0; 
   
   unsigned int vert_mem = 0; 
   unsigned int norm_mem = 0; 
   unsigned int uv_mem   = 0; 
   unsigned int face_mem = 0; 
   
   unsigned int cur_vert[3]; 
   unsigned int cur_uv  [3]; 
   unsigned int cur_norm[3];
   
   //float* u,
   //     * v; 
        
   //float* vx,
   //     * vy, 
   //     * vz; 
   
   float u[5000],
         v[5000]; 
        
   float vx[5000],
         vy[5000], 
         vz[5000]; 
   
   unsigned int i;
   
   unsigned int colors[]=
   {
	0xff7f0000, 
	0xff7f0000, 
	0xff7f0000, 
	0xff007f00,
	0xff007f00,
	0xff007f00,
	0xff00007f,
	0xff00007f,
	0xff00007f
   };

   if ((file = fopen(str, "r")) == NULL)
   {
   	    printf("file %s not found\n", str);
   		return -1; 
   }
   printf("file = %s\n", str);
   
   //repeated code because lazy
   while(1)
   {
   		char line[128];
   		int res = fscanf(file, "%s", line);
   		
   		if (res == EOF) {break;}
   		
   		     if (strcmp(line, "v" ) == 0) {vert_mem++;}
   		else if (strcmp(line, "vt") == 0) {  uv_mem++;}
   		else if (strcmp(line, "vn") == 0) {norm_mem++;}
   		else if (strcmp(line, "f" ) == 0) {face_mem++;}
   }
   
   rewind(file);

   printf("reset files\n");

   mesh->verts = malloc(6*vert_mem *sizeof(vertex_t));
  // u = malloc(uv_mem*sizeof(float)); 
  // v = malloc(uv_mem*sizeof(float)); 
  // vx = malloc(vert_mem*sizeof(float));
  // vy = malloc(vert_mem*sizeof(float));
  // vz = malloc(vert_mem*sizeof(float));
   //mesh->uvs   = malloc(6*uv_mem   *sizeof(uv_t)    );
   //mesh->faces = malloc(6*face_mem *sizeof(face_t)  );

   while(1)
   {
      	char line[128];
      	int res = fscanf(file, "%s", line);
      	if (res == EOF) {break;}
      
      	if (strcmp(line, "v") == 0)
      	{
        	 fscanf(file, "%f %f %f\n", &vx[vert_length], 
				            			&vy[vert_length], 
					    				&vz[vert_length]);
					    				
			 mesh->verts[vert_length].color = colors[vert_length%9];
					    				
			 vert_length++; 
      	}else if(strcmp(line, "vt") == 0)
      	{
        	 fscanf(file, "%f %f\n"  , &u[uv_length], 
			                 		   &v[uv_length]);
			                 		    
	 		 uv_length++; 
      	}else if(strcmp(line, "vn") == 0)
      	{
        	/* fscanf(file, "%f %f %f\n", &obj->norms[norm_length].x, 
				            			&obj->norms[norm_length].y,
				      	    			&obj->norms[norm_length].z);
	 		 */norm_length++; 
      	}else if(strcmp(line, "f") == 0)
      	{
        	 int match = 0; 
        	 /*short may have to be replaced with unsigned int*/
        	 match = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
		    	          				&cur_vert[0], 
		    	          				&cur_uv  [0], 
		    	          				&cur_norm[0],

            	            			&cur_vert[1], 
		    	          				&cur_uv  [1], 
		    	          				&cur_norm[1],

            	            			&cur_vert[2], 
		    	          				&cur_uv  [2],
		    	          				&cur_norm[2]);		    	          				 	          			
			
		mesh->verts[0+(3*face_length)].u = u[cur_uv[0] - 1];
   		mesh->verts[0+(3*face_length)].v = v[cur_uv[0] - 1];
   		mesh->verts[1+(3*face_length)].u = u[cur_uv[1] - 1];
   		mesh->verts[1+(3*face_length)].v = v[cur_uv[1] - 1];
   		mesh->verts[2+(3*face_length)].u = u[cur_uv[2] - 1];
   		mesh->verts[2+(3*face_length)].v = v[cur_uv[2] - 1];
   		
   		mesh->verts[0+(3*face_length)].vx = vx[cur_vert[0] - 1];
   		mesh->verts[0+(3*face_length)].vy = vy[cur_vert[0] - 1];
   		mesh->verts[0+(3*face_length)].vz = vz[cur_vert[0] - 1];
   		mesh->verts[1+(3*face_length)].vx = vx[cur_vert[1] - 1];
   		mesh->verts[1+(3*face_length)].vy = vy[cur_vert[1] - 1];
   		mesh->verts[1+(3*face_length)].vz = vz[cur_vert[1] - 1];
   		mesh->verts[2+(3*face_length)].vx = vx[cur_vert[2] - 1];
   		mesh->verts[2+(3*face_length)].vy = vy[cur_vert[2] - 1];
   		mesh->verts[2+(3*face_length)].vz = vz[cur_vert[2] - 1];	

	 		if (match != 9)
			{
        		 printf("please enable 'keep vertex order'");
	   	     	 return -1;
	 		}

         	face_length++;
     	}
   }

   mesh->face_count = face_length;//*3;  
	
   fflush(file);
   fclose(file);
   
   //free(u); 
   //free(v); 
   //free(vx); 
   //free(vy); 
   //free(vx); 
   printf("Finished loading model\n");
   return 0; 
}

void delete_mesh(mesh_t* mesh)
{
	free(mesh->verts); 
	free(mesh->uvs); 
	free(mesh->faces);
}
