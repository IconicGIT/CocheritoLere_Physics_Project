#include "OBJ_Model.h"
#include <gl/GL.h>
#include <gl/GLU.h>

void Model::RenderModel(int modelID, float x, float y, float z, float colR, float colG, float colB, float alpha, float scale)
{
	objl::Loader currLoader;

	models.at(modelID, currLoader);


	glBegin(GL_QUADS);

	glLineWidth(5.0f);
	glColor4f(colR, colG, colB, alpha);

	
	for (int i = 0; i < currLoader.LoadedMeshes.size(); i++)
	{
		
		objl::Mesh currMesh = currLoader.LoadedMeshes.at(i);
	
		for (int j = 0; j < currMesh.Vertices.size(); j++)
		{
			float v1 = currMesh.Vertices[j].Position.X;
			float v2 = currMesh.Vertices[j].Position.Y;
			float v3 = currMesh.Vertices[j].Position.Z;

			v1 = METERS_TO_UNITS(v1);
			v2 = METERS_TO_UNITS(v2);
			v3 = METERS_TO_UNITS(v3);

			glVertex3f(x + v1 * scale, y + v2 * scale, z + v3 * scale);
			
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