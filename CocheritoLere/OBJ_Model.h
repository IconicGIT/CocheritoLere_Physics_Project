#pragma once

#include "OBJ_Loader.h"
#include "p2List.h"

class Model
{
public:
	Model() {}
	~Model() {}

public:

	int LoadModel(std::string path)
	{
		int id = -1;


		if (path.empty())
		{
			LOG("Could not load model.");
			return -1;
		}
		
		objl::Loader currentModel;
		bool loaded = currentModel.LoadFile(path);
		if (loaded)
		{
			id = 0;
			models.add(currentModel);
			while (id < models.count() - 1)
			{
				id++;
			}
		}
		else
		{
			LOG("Could not load model.");
			return -1;
		}
		


		return id;
	}

	void RenderModel(int modelID, float x, float y, float z, float colR, float colG, float colB, float alpha, float scale = 1.0f);


	

private:
	p2List<objl::Loader> models;
};