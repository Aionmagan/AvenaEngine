#include "../mesh.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int load_mesh(char* str, mesh_t* mesh)
{
   FILE *file = NULL; 

   char s[40]={"/rd/"}; 
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
   
   //unsigned int i;

   strcat(s, str); 
   if ((file = fopen(s, "r")) == NULL)
   {
   	    printf("file %s not found\n", s);
   		return -1; 
   }
   printf("file = %s\n", s);
   
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

   //printf("reset files\n");

   mesh->verts = malloc(vert_mem *sizeof(vertex_t));
   mesh->uvs   = malloc(uv_mem   *sizeof(uv_t)    );
   mesh->faces = malloc(face_mem *sizeof(face_t)  );
   
   //set_system_ram();
   //print_ram_stats();
   //print_VRAM_stats();

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

/*MULTI OBJECT RENDERING*/

int load_meshmt(char* str, meshmt_t* mesh)
{
   FILE *file = NULL; 
	char s[128]={"/rd/"}; 
	
   unsigned int vert_length = 0;
   unsigned int norm_length = 0;
   unsigned int uv_length   = 0; 
   unsigned int face_length = 0; 
   
   unsigned int vert_mem = {0}; 
   unsigned int norm_mem = {0}; 
   unsigned int uv_mem   = {0}; 
   unsigned int face_mem[9999] = {0};
   
   unsigned int cur_vert[3]; 
   unsigned int cur_uv  [3]; 
   unsigned int cur_norm[3];
   
   unsigned int mesh_select = 0; 
   unsigned int mesh_parts = 1; 
   char         mtl_file_name[128]; 
   int          part_detected = 0; 
   
   unsigned int i;

   strcat(s, str); 
   if ((file = fopen(s, "r")) == NULL)
   {
   	    printf("file %s not found\n", s);
   		return -1; 
   }
   printf("file = %s\n", s);
   
   //repeated code because lazy
   while(1)
   {
   		char line[128];
   		int res = fscanf(file, "%s", line);
   		
   		if (res == EOF) {break;}
   		
   		if (strcmp(line, "mtllib") == 0)
   		{
   			fscanf(file, "%s\n", mtl_file_name);
   		}
   		else if (strcmp(line, "o" ) == 0)
   		{
   			if (part_detected)
				mesh_select++;	
		}
		else if (strcmp(line, "usemtl") == 0)
		{
			fscanf(file, "%s", line);
			strcpy(mesh->tex_names[mesh_select], line); 
		}
   		else if (strcmp(line, "v" ) == 0) {vert_mem++;}
   		else if (strcmp(line, "vt") == 0) {  uv_mem++;}
   		else if (strcmp(line, "vn") == 0) {norm_mem++;}
   		else if (strcmp(line, "f" ) == 0) 
   		{
   			face_mem[mesh_select]++; 
   			part_detected = 1; 
   		}
   }
      //for (int i = 0; i<2181; ++i)
   		//printf("vert/norm/uv/face {%d, %d, %d, %d}\n", vert_mem[i], norm_mem[i], uv_mem[i], face_mem[i]); 
   mesh_parts = mesh_select+1; 
   printf("Mesh in this file = %d | %d\n", mesh_parts, part_detected); 
   
   rewind(file);

   printf("reset files\n");

   /*for (int i = 0; i < mesh_parts; ++i)
   {
   		mesh->faces[i] = malloc(6*face_mem[i]  *sizeof(face_t)  );
   }*/
    
 	mesh->faces = malloc(mesh_parts * sizeof(face_t));   	
 	for(i = 0; i < mesh_parts; ++i)
 		mesh->faces[i] = malloc(face_mem[i] * sizeof(face_t));
 			   	
    mesh->verts = malloc(vert_mem * sizeof(vertex_t));
   	mesh->norms = malloc(norm_mem * sizeof(vertex_t));
   	mesh->uvs   = malloc(uv_mem   * sizeof(uv_t)    );
   	mesh->face_count = malloc(mesh_parts * sizeof(int));
   	mesh->mats  = malloc(mesh_parts * sizeof(mat_t));
   			   
   	//set_system_ram();
    //print_ram_stats();
    //print_VRAM_stats();
    
   	part_detected = 0; 
   	mesh_select = 0; 
#if 1
   while(1)
   {
      	char line[128];
      	int res = fscanf(file, "%s", line);
      	if (res == EOF) {break;}
      
      	if (strcmp(line, "usemtl") == 0)
      	{
      		char buff[128]; 
      		fscanf(file, "%s\n", buff);
      		load_mat(s, buff, &mesh->mats[mesh_select]); 
      	}
      	else if (strcmp(line, "o" ) == 0)
   		{
   			if (part_detected)
   			{
				//part_detected = 0;
			 	//mesh->face_count[mesh_select] = face_length;  
			 	mesh_select++; 
			 	//printf("mesh->face_count = %d\n", mesh->face_count[mesh_select-1]);
			 	//printf("vert_length = %d / uv_length = %d / norm_length = %d\n", vert_length, uv_length, norm_length);
			 	//vert_length = 0; 
			 	//uv_length   = 0; 
			 	//norm_length = 0;
			 	face_length = 0; 		
			}
		}
      	else if (strcmp(line, "v") == 0)
      	{
			 
        	 fscanf(file, "%f %f %f\n", &mesh->verts[vert_length].x, 
				            			&mesh->verts[vert_length].y, 
					    				&mesh->verts[vert_length].z);
					    				
		//	printf("verts {%f, %f, %f}\n", mesh->verts[mesh_select][vert_length].x, 
   		//	                               mesh->verts[mesh_select][vert_length].y, 
   		//	                               mesh->verts[mesh_select][vert_length].z);
					    				
			 vert_length++; 		
			 	
      	}else if(strcmp(line, "vt") == 0)
      	{
        	 fscanf(file, "%f %f\n"  , &mesh->uvs[uv_length].u, 
			                 		   &mesh->uvs[uv_length].v);
			                 		    
	 		 uv_length++; 
      	}else if(strcmp(line, "vn") == 0)
      	{
        	 fscanf(file, "%f %f %f\n", &mesh->norms[norm_length].x, 
				            			&mesh->norms[norm_length].y,
				      	    			&mesh->norms[norm_length].z);
	 		 norm_length++; 
      	}else if(strcmp(line, "f") == 0)
      	{
      		 part_detected = 1; 
      		
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
			
			mesh->faces[mesh_select][face_length].vx = cur_vert[0] - 1;
			mesh->faces[mesh_select][face_length].vy = cur_vert[1] - 1;
			mesh->faces[mesh_select][face_length].vz = cur_vert[2] - 1; 	
			
			mesh->faces[mesh_select][face_length].ux = cur_uv[0] - 1;
			mesh->faces[mesh_select][face_length].uy = cur_uv[1] - 1;
			mesh->faces[mesh_select][face_length].uz = cur_uv[2] - 1; 	
			
			mesh->faces[mesh_select][face_length].nx = cur_norm[0] - 1;
			mesh->faces[mesh_select][face_length].ny = cur_norm[1] - 1;
			mesh->faces[mesh_select][face_length].nz = cur_norm[2] - 1; 	

	 		if (match != 9)
			{
        		 printf("please enable 'keep vertex order'");
	   	     	 return -1;
	 		}

         	//printf("mesh_parts = %d ", mesh_select);
         	//printf("face_length = %d\n", face_length);
         	//printf("cur_vert {%d, %d, %d}\n", cur_vert[0], cur_vert[1], cur_vert[2]);
         	//printf("faces {%d, %d, %d}\n", mesh->faces[mesh_select][face_length].vx+1, 
			//mesh->faces[mesh_select][face_length].vy+1 ,
			//mesh->faces[mesh_select][face_length].vz+1 );
			
         	face_length++;
         	//printf("face_length = %d | face_mem = %d | mesh_select = %d | face2_mem = %d\n", face_length, face_mem[mesh_select], mesh_select, face2_mem);
			mesh->face_count[mesh_select] = face_length;
         	//if (face_mem[mesh_select] == face_length)
         		//printf("Model %d loaded\n", mesh_select+1);
     	}
   }

  /*  	
   	for (int i = 0; i < mesh_parts; ++i)
   	{
   		printf("i = %d\n", i);
   		for(int j = 0; j < mesh->face_count[i]; ++j)
   		{
   		
   		printf("verts {%d, %d, %d}\n", mesh->faces[i][j].vx+1, 
   			                               mesh->faces[i][j].vy+1, 
   			                               mesh->faces[i][j].vz+1);
   			printf("verts {%f, %f, %f}\n", mesh->verts[mesh->faces[i][j].vx].x, 
   			                               mesh->verts[mesh->faces[i][j].vx].y, 
   			                               mesh->verts[mesh->faces[i][j].vx].z);
			printf("verts {%f, %f, %f}\n", mesh->verts[i][mesh->faces[i][j].vx].x, 
   			                               mesh->verts[i][mesh->faces[i][j].vx].y, 
   			                               mesh->verts[i][mesh->faces[i][j].vx].z);
   			                               
   			printf("verts {%f, %f, %f}\n", mesh->verts[i][mesh->faces[i][j].vy].x, 
   			                               mesh->verts[i][mesh->faces[i][j].vy].y, 
   			                               mesh->verts[i][mesh->faces[i][j].vy].z);
   			                               
   			printf("verts {%f, %f, %f}\n", mesh->verts[i][mesh->faces[i][j].vz].x, 
   			                               mesh->verts[i][mesh->faces[i][j].vz].y, 
   			                               mesh->verts[i][mesh->faces[i][j].vz].z);   			                                  			                               

			printf("verts {%f, %f, %f}\n", mesh->verts[i][mesh->faces[i][j].vy].x, 
   			                               mesh->verts[i][mesh->faces[i][j].vy].y, 
   			                               mesh->verts[i][mesh->faces[i][j].vy].z);  
   			                               
			printf("verts {%f, %f, %f}\n", mesh->verts[i][mesh->faces[i][j].vz].x, 
   			                               mesh->verts[i][mesh->faces[i][j].vz].y, 
   			                               mesh->verts[i][mesh->faces[i][j].vz].z);    			                                			                               
   			                               
   			printf("norms {%f, %f, %f}\n", mesh->norms[i][0].x, 
   			                               mesh->norms[i][0].y, 
   			                               mesh->norms[i][0].z);
   			                               
   			printf("uvs {%f, %f, %f}\n", mesh->uvs[i][0].u, 
   			                             mesh->uvs[i][0].v);   	
   			                               		
   		}
   	}*/
   		mesh->mesh_parts = mesh_parts;  
   		printf("Mesh in this file = %d | %d\n", mesh->mesh_parts, part_detected); 
#endif

/*  for (int i = 0; i < mesh_parts; ++i)
   	{
   		printf("ambi {%f, %f, %f, %f}\n", mesh->mats[i].ambi[0], mesh->mats[i].ambi[1], mesh->mats[i].ambi[2], mesh->mats[i].ambi[3]);
   		printf("diff {%f, %f, %f, %f}\n", mesh->mats[i].diff[0], mesh->mats[i].diff[1], mesh->mats[i].diff[2], mesh->mats[i].diff[3]);
   		printf("spec {%f, %f, %f, %f}\n", mesh->mats[i].spec[0], mesh->mats[i].spec[1], mesh->mats[i].spec[2], mesh->mats[i].spec[3]);
   	}
*/
	for (i = 0; i < mesh_parts; ++i)
		printf("mat->texture = %s\n", mesh->mats[i].texfile);
		
   fflush(file);
   fclose(file);
   printf("Finished loading model meshmt\n");
   
   return 0; 
}

int load_mat(char* str, char* substr, mat_t* mat)
{
	FILE* file = NULL;
	char newstr[128]; 
	int len = strlen(str);
	
	strcpy(newstr, str);
	
	newstr[len-3] = 'm';
	newstr[len-2] = 't';
	newstr[len-1] = 'l';
	
	//printf("str = %s| %d\n", newstr, len);
	
	if ((file = fopen(newstr, "r")) == NULL)
   	{
   	    printf("file %s not found\n", newstr);
   		return -1; 
   	}
   
   	while(1)
   	{
   	    char line[128];
      	int res = fscanf(file, "%s", line);
      	if (res == EOF) {break;}
      	//printf("line = %s\n", line);
      	if (strcmp(line, substr) == 0)
      	{
      		//char s[128];
      		
      		strcpy(&mat->texfile, substr);
      		 
      		//mat->texfile[0] = '\0';
      		while(1)
      		{
      			 res = fscanf(file, "%s", line);
      			 if (res == EOF) {break;}
      			 
      			 if (strcmp(line, "Ka")==0)
      			 {
      			 	fscanf(file, "%f %f %f\n", &mat->ambi[0], &mat->ambi[1], &mat->ambi[2]);
      			 	mat->ambi[3] = 1.0f; 
      			 	//printf("%f %f %f\n", mat->ambi[0], mat->ambi[1], mat->ambi[2]);
      			 }else if (strcmp(line, "Kd")==0)
      			 {
      			 	fscanf(file, "%f %f %f\n", &mat->diff[0], &mat->diff[1], &mat->diff[2]);
      			 	//printf("%f %f %f\n", mat->diff[0], mat->diff[1], mat->diff[2]);
      			 	mat->diff[3] = 1.0f; 
      			 }else if (strcmp(line, "Ks")==0)
      			 {
      			 	fscanf(file, "%f %f %f\n", &mat->spec[0], &mat->spec[1], &mat->spec[2]);
      			 	//printf("%f %f %f\n", mat->spec[0], mat->spec[1], mat->spec[2]);
      			 	mat->spec[3] = 1.0f; 
      			 }else if (strcmp(line, "Ke")==0)
      			 {
      			 	fscanf(file, "%f %f %f\n", &mat->emit[0], &mat->emit[1], &mat->emit[2]);
      			 	//printf("%f %f %f\n", mat->emit[0], mat->emit[1], mat->emit[2]);
      			 	mat->spec[3] = 1.0f; 
      			 }else if (strcmp(line, "map_Kd")==0)
      			 {
      			 	fscanf(file, "%s\n", &mat->texfile);
      			 	printf("tex name = %s\n", mat->texfile);
      			 }      			 
      			 else if (strcmp(line, "newmtl")==0)
      			 {
      			 	break;      			 	
      			 }
      		}
      		
      		//strcpy(mat->texfile, s);
      	}
   	}
   	
	fflush(file);
   	fclose(file);
	return 0; 
}

void delete_mesh(mesh_t* mesh)
{
	free(mesh->verts); 
	free(mesh->uvs); 
	free(mesh->faces);
}
