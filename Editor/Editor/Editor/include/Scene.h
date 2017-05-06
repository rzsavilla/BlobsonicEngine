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


	void checkForHovering(Vector2f mousepos);
	void deselect();
	void processClickEvent(Vector2f mousepos);

private:

	vector<pair<RectangleShape,Clickable>> m_vRectFloorTiles; //<! floor tile rects
	vector<Sprite> m_vSpriteFloorTiles; //<! floor tile sprite
	Texture m_vTextureStoneFloorTiles; //<! floor tile Texture

	bool m_bSelected = false;
	RectangleShape m_sfSelectedRect;
	Sprite m_sfSelectedSprite;
	Texture m_sfSelectedTexture;

	void loadTextures(); //<! Loads in the required textures to the scene


	//grid varibles
	float m_fGridSize; //<! size of each grid length
	float m_fXDimensions; //<! number of grids in  x
	float m_fYDimensions; //<! number of grids in  z (y)




};

#endif