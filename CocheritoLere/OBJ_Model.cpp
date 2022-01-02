#include "OBJ_Model.h"
#include <gl/GL.h>
#include <gl/GLU.h>


Model::Model()
{
	x = y = z = 0;
	rot_x = rot_y = rot_z = 0;
	colR = 1;
	colG = 1;
	colB = 1;
	alpha = 1;
	scale = 1;
	wireframe = false;
}

void Model::RenderModel()
{

	
	for (int i = 0; i < model.LoadedMeshes.size(); i++)
	{
		
		objl::Mesh currMesh = model.LoadedMeshes.at(i);
	
		for (int j = 0; j < currMesh.Indices.size(); j += 3)
		{
			int currIndex = currMesh.Indices[j];

			objl::Vertex v1 = currMesh.Vertices[currIndex];
			objl::Vertex v2 = currMesh.Vertices[currIndex + 1];
			objl::Vertex v3 = currMesh.Vertices[currIndex + 2];

			glDisable(GL_CULL_FACE);
			if (wireframe)
			{
				glBegin(GL_LINE_STRIP);

			}
			else
			{
				glBegin(GL_TRIANGLES);
			}

			glColor4f(colR, colG, colB, alpha);

			glNormal3f(v1.Normal.X, v1.Normal.Y, v1.Normal.Z);
			glVertex3f(
				x + METERS_TO_UNITS(v1.Position.X) * scale,
				y + METERS_TO_UNITS(v1.Position.Y) * scale,
				z + METERS_TO_UNITS(v1.Position.Z) * scale
				);
			
			glNormal3f(v2.Normal.X, v2.Normal.Y, v2.Normal.Z);
			glVertex3f(
				x + METERS_TO_UNITS(v2.Position.X) * scale,
				y + METERS_TO_UNITS(v2.Position.Y) * scale,
				z + METERS_TO_UNITS(v2.Position.Z) * scale
			);
			
			glNormal3f(v3.Normal.X, v3.Normal.Y, v3.Normal.Z);
			glVertex3f(
				x + METERS_TO_UNITS(v3.Position.X) * scale ,
				y + METERS_TO_UNITS(v3.Position.Y) * scale ,
				z + METERS_TO_UNITS(v3.Position.Z) * scale 
			);
			
			glEnd();
		}
	}
}

