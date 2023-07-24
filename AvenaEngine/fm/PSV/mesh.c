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
   
   unsigned int i;

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

   mesh->verts = malloc(16*vert_mem *sizeof(vertex_t));
   mesh->uvs   = malloc(16*uv_mem   *sizeof(uv_t)    );
   mesh->faces = malloc(6*face_mem *sizeof(face_t)  );

   while(1)
   {
      	char line[128];
      	int res = fscanf(file, "%s", line);
      	if (res == EOF) {break;}
      
      	if (strcmp(line, "v") == 0)
      	{
        	 fscanf(file, "%f %f %f\n", &mesh->verts[vert_length].x, 
				            			&mesh->verts[vert_length].y, 
					    				&mesh->verts[vert_length].z);
					    				
			 vert_length++; 
      	}else if(strcmp(line, "vt") == 0)
      	{
        	 fscanf(file, "%f %f\n"  , &mesh->uvs[uv_length].u, 
			                 		   &mesh->uvs[uv_length].v);
			                 		    
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
			
			mesh->faces[face_length].vx = cur_vert[0] - 1;
			mesh->faces[face_length].vy = cur_vert[1] - 1;
			mesh->faces[face_length].vz = cur_vert[2] - 1; 	
			
			mesh->faces[face_length].ux = cur_uv[0] - 1;
			mesh->faces[face_length].uy = cur_uv[1] - 1;
			mesh->faces[face_length].uz = cur_uv[2] - 1; 		

	 		if (match != 9)
			{
        		 printf("please enable 'keep vertex order'");
	   	     	 return -1;
	 		}

         	face_length++;
     	}
   }

   mesh->face_count = face_length;  
	
   fflush(file);
   fclose(file);
   printf("Finished loading model\n");
   return 0; 
}

void delete_mesh(mesh_t* mesh)
{
	free(mesh->verts); 
	free(mesh->uvs); 
	free(mesh->faces);
}
