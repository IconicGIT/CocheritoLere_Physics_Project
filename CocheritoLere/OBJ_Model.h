#pragma once

#include "OBJ_Loader.h"

class Model
{
public:
	Model();
	~Model() {}


	void RenderModel();

	objl::Loader model;
	float x, y, z;
	float rot_x, rot_y, rot_z;
	float colR;
	float colG;
	float colB;
	float alpha;
	float scale;
	bool wireframe;

private:
	
};