#include "sky.h"
#include "../util/util.h"
#include "../object/staticObject.h"
#include "../assets/assetManager.h"
#include "../scene/scene.h"

Sky::Sky(Scene* scene) {
	mesh=new Sphere(16,16);
	StaticObject* skyObject=new StaticObject(mesh);
	Material* mat = new Material("sky_mat");
	mat->diffuse = vec3(0.5f, 0.7f, 0.8f);
	skyObject->bindMaterial(MaterialManager::materials->add(mat));
	skyObject->setPosition(0,0,0);
	skyObject->setSize(4, 4, 4);
	skyNode=new StaticNode(vec3(0,0,0));
	skyNode->setFullStatic(true);
	skyNode->addObject(scene, skyObject);
	skyNode->updateNode();
	skyNode->prepareDrawcall();

	/*
	CubeMap* texture=new CubeMap("texture/sky/sky_ft.bmp","texture/sky/sky_bk.bmp",
			"texture/sky/sky_dn.bmp","texture/sky/sky_up.bmp",
			"texture/sky/sky_rt.bmp","texture/sky/sky_lf.bmp");
	//*/
	///*
	CubeMap* texture = new CubeMap("texture/sky/xpos.bmp", "texture/sky/xneg.bmp",
		"texture/sky/yneg.bmp", "texture/sky/ypos.bmp",
		"texture/sky/zpos.bmp", "texture/sky/zneg.bmp");
	//*/
	AssetManager::assetManager->setSkyTexture(texture);

	state = new RenderState();
	state->cullMode = CULL_FRONT;
	state->lightEffect = false;
	state->skyPass = true;
}

Sky::~Sky() {
	delete mesh; mesh=NULL;
	delete skyNode; skyNode=NULL;
	delete state; state = NULL;
}

void Sky::draw(Render* render,Shader* shader,Camera* camera) {
	state->shader = shader;
	if (!shader->isTexBinded(AssetManager::assetManager->getSkyTexture()->hnd))
		shader->setHandle64("texSky", AssetManager::assetManager->getSkyTexture()->hnd);
	render->draw(camera,skyNode->drawcall,state);
}

