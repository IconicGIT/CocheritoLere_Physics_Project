#include "OBJ_Model.h"
#include <gl/GL.h>
#include <gl/GLU.h>

void Model::RenderModel(int modelID, float x, float y, float z, float colR, float colG, float colB, float alpha, float scale)
{
	objl::Loader currLoader;

	models.at(modelID, currLoader);

	//glDisable(GL_CULL_FACE);
	glBegin(GL_TRIANGLES);

	glLineWidth(5.0f);
	glColor4f(colR, colG, colB, alpha);


	
	for (int i = 0; i < currLoader.LoadedMeshes.size(); i++)
	{
		
		objl::Mesh currMesh = currLoader.LoadedMeshes.at(i);
	
		for (int j = 0; j < currMesh.Indices.size(); j += 3)
		{
			int currIndex = currMesh.Indices[j];

			objl::Vertex v1 = currMesh.Vertices[currIndex];
			objl::Vertex v2 = currMesh.Vertices[currIndex + 1];
			objl::Vertex v3 = currMesh.Vertices[currIndex + 2];

			glNormal3f(v1.Normal.X, v1.Normal.Y, v1.Normal.Z);
			glVertex3f(x + METERS_TO_UNITS(v1.Position.X) * scale, y + METERS_TO_UNITS(v1.Position.Y) * scale, z + METERS_TO_UNITS(v1.Position.Z) * scale);
			
			glNormal3f(v2.Normal.X, v2.Normal.Y, v2.Normal.Z);
			glVertex3f(x + METERS_TO_UNITS(v2.Position.X) * scale, y + METERS_TO_UNITS(v2.Position.Y) * scale, z + METERS_TO_UNITS(v2.Position.Z) * scale);
			
			glNormal3f(v3.Normal.X, v3.Normal.Y, v3.Normal.Z);
			glVertex3f(x + METERS_TO_UNITS(v3.Position.X) * scale, y + METERS_TO_UNITS(v3.Position.Y) * scale, z + METERS_TO_UNITS(v3.Position.Z) * scale);

			//v1.Position.X *= UNITS_PER_METER;
			//v2 = METERS_TO_UNITS(v2);
			//v3 = METERS_TO_UNITS(v3);
			//
			//glVertex3f(x + v1 * scale, y + v2 * scale, z + v3 * scale);
			
		}
	}

	//test plane
	//glVertex3f(0.0f, 0.0f, 0.0f);
	//glVertex3f(1.0f, 0.0f, 0.0f);
	//glVertex3f(1.0f, 1.0f, 0.0f);
	//glVertex3f(0.0f, 1.0f, 0.0f);
	//
	glEnd();

}