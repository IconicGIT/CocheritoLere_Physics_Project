#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include <gl/GL.h>
#include <gl/GLU.h>

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));
	

	cube = App->modelLoader->LoadModel("Assets/Models/full_train.obj");
	pyramid = App->modelLoader->LoadModel("Assets/Models/pyramid.obj");
	tracks = App->modelLoader->LoadModel("Assets/Models/tracks.obj");
	train = App->modelLoader->LoadModel("Assets/Models/full_train.obj");
	mod_car = App->modelLoader->LoadModel("Assets/Models/car_1.obj");
	
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();


	
	//glBegin(GL_TRIANGLES);
	//
	//
	//glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	//
	//glVertex3f(0.0f, 0.0f, 0.0f);
	//glVertex3f(1.0f, 0.0f, 0.0f);
	//glVertex3f(1.0f, 1.0f, 0.0f);
	//glVertex3f(0.0f, 1.0f, 0.0f);
	//
	//
	//
	//
	//
	//glEnd();
	
	btVector3 playerPosition = App->player->GetPosition();
		
	App->modelLoader->RenderModel(mod_car,playerPosition.getX() , playerPosition.getY(), playerPosition.getZ(), 1.0f, 1.0f, .20f, 1.0f);
	
	App->modelLoader->RenderModel(cube, 0, 0, 0, 0.0f, 0.0f, 1.0f, 1.0f);
	//App->modelLoader->RenderModel(pyramid, 5, 0, 0, 0.0f, 0.0f, 1.0f, 1.0f);
	App->modelLoader->RenderModel(train, 0, 0, 0, 0.0f, 0.0f, 1.0f, 1.0f, 10.f, true);
	//App->modelLoader->RenderModel(tracks, 0, 0, 0, 0.0f, 0.0f, 1.0f, 1.0f, 10.f);


	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

