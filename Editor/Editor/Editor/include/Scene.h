#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <SFML\Graphics.hpp>
#include "tinyxml2.h"
#include <utility>
#include "Clickable.h"


using namespace std;
using namespace sf;
using namespace tinyxml2;

class Scene : public Drawable
{
public:

	Scene(); // <! Default Constructor for editor scene
	Scene(string path); //<! Contructor for editor scene with the path to the scene

	void draw(RenderTarget& target, RenderStates states) const; // <! Renders the scene

	bool m_bPlacing = false;

	void processClickEvent(Vector2f mousepos);
	void tempObject(Vector2f pos, Vector2f size);
	void addPickup(Vector2f pos);
	void addObsticle(Vector2f pos);
	void addLight(Vector2f pos);
	void movePlayer(Vector2f pos);
	void moveGoal(Vector2f pos);

	//grid varibles
	float m_fGridSize; //<! size of each grid length
	float m_fXDimensions; //<! number of grids in  x
	float m_fYDimensions; //<! number of grids in  z (y)
	string LevelName; //<! LevelName


	RectangleShape m_SkyboxRect;
	Sprite m_SkyboxSprite;

	Sprite m_Player;
	Sprite m_Goal;

	vector<Sprite>m_vPickupSprites;
	vector<Sprite>m_vObsticleSprites;
	vector<Sprite>m_vLightSprites;

	vector<RectangleShape> m_vRectFloorTiles; //<! floor tile rects
	vector<Sprite> m_vSpriteFloorTiles; //<! floor tile sprite

private:

	
	

	//Textures
	Texture m_vTextureStoneFloorTiles; //<! floor tile Texture
	Texture m_vTextureGrassFloorTiles; //<! floor tile Texture
	Texture m_vTextureBlueFloorTiles; //<! floor tile Texture
	Texture m_vTextureBrownFloorTiles; //<! floor tile Texture
	Texture m_vTextureGreenFloorTiles; //<! floor tile Texture

	Texture m_vTextureWaterSkybox;
	Texture m_vTextureSunnySkybox;

	Texture m_vTexturePickups;
	Texture m_vTextureObsticle;
	Texture m_vTextureLight;

	Texture m_vTexturePlayer;
	Texture m_vTextureFinish;
	
	RectangleShape m_sfTempRect;
	
	void loadTextures(); //<! Loads in the required textures to the scene





};

#endif