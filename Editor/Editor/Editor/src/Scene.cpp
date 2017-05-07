#include "Scene.h"

Scene::Scene()
{
}

Scene::Scene(string path)
{
	//Load Textures
	loadTextures();

	m_Player.setPosition(0.0f, 0.0f);
	m_Player.setTexture(m_vTexturePlayer);

	m_Player.setPosition(m_fGridSize, 0.0f);
	m_Player.setTexture(m_vTextureFinish);


	//read the scene
	XMLDocument xmlDoc;
	xmlDoc.LoadFile(path.c_str());

	for (tinyxml2::XMLNode* child = xmlDoc.FirstChild(); child != NULL; child = child->NextSibling())
	{
		const char* Value = child->Value();
		if (strcmp(Value, "Scene") == 0)
		{
			for (tinyxml2::XMLNode* child2 = child->FirstChild(); child2 != NULL; child2 = child2->NextSibling())
			{
				Value = child2->Value();
				if (strcmp(Value, "GridSize") == 0)
				{
					m_fGridSize = stof(child2->ToElement()->GetText());
				}
				else if (strcmp(Value, "LevelName") == 0)
				{
					LevelName = child2->ToElement()->GetText();
				}
				else if (strcmp(Value, "Dimensions") == 0)
				{
					for (tinyxml2::XMLNode* Dimensions = child2->FirstChild(); Dimensions != NULL; Dimensions = Dimensions->NextSibling())
					{
						Value = Dimensions->Value();
						if (strcmp(Value, "X") == 0)
						{
							m_fXDimensions = stof(Dimensions->ToElement()->GetText());
						}
						if (strcmp(Value, "Z") == 0)
						{
							m_fYDimensions = stof(Dimensions->ToElement()->GetText());
						}
					}
				}
				else if (strcmp(Value, "Entity") == 0)
				{
					Value = child2->Value();

					RectangleShape tempRect;
					Sprite tempSprite;
					Vector2f tempPosition;
					Vector2f tempSize;
					float tempRotation;
					string type;

					for (tinyxml2::XMLNode* entity = child2->FirstChild(); entity != NULL; entity = entity->NextSibling())
					{

						Value = entity->Value();
						if (strcmp(Value, "Name") == 0)
						{
							type = entity->ToElement()->GetText();
						}
						else if (strcmp(Value, "Transformable") == 0)
						{
						

							for (tinyxml2::XMLNode* Model = entity->FirstChild(); Model != NULL; Model = Model->NextSibling())
							{

								Value = Model->Value();
								if (strcmp(Value, "Position") == 0)
								{
									for (tinyxml2::XMLNode* Position = Model->FirstChild(); Position != NULL; Position = Position->NextSibling())
									{
										Value = Position->Value();
										if (strcmp(Value, "X") == 0)
										{
											tempPosition.x = stof(Position->ToElement()->GetText());
										}
										if (strcmp(Value, "Z") == 0)
										{
											tempPosition.y = stof(Position->ToElement()->GetText());
										}
									}
								}
								else if (strcmp(Value, "Scale") == 0)
								{
									for (tinyxml2::XMLNode* Scale = Model->FirstChild(); Scale != NULL; Scale = Scale->NextSibling())
									{
										Value = Scale->Value();
										if (strcmp(Value, "X") == 0)
										{
											tempSize.x = stof(Scale->ToElement()->GetText());
										}
										if (strcmp(Value, "Z") == 0)
										{
											tempSize.y = stof(Scale->ToElement()->GetText());
										}
									}
								}
								else if (strcmp(Value, "Texture") == 0)
								{
									string texture = Model->ToElement()->GetText();
									if (texture == "floor_texture")tempSprite.setTexture(m_vTextureStoneFloorTiles);
									else if (texture == "floor_grass_texture")tempSprite.setTexture(m_vTextureGrassFloorTiles);
								}
								else if (strcmp(Value, "Rotation") == 0)
								{
									for (tinyxml2::XMLNode* Rotation = Model->FirstChild(); Rotation != NULL; Rotation = Rotation->NextSibling())
									{
										Value = Rotation->Value();
										if (strcmp(Value, "Y") == 0)
										{
											tempRotation = stof(Rotation->ToElement()->GetText());
										}

									}
								}
								else if (strcmp(Value, "Origin") == 0)
								{
									//do nothing
								}

							}
							
							
						}
						else if (strcmp(Value, "Model") == 0)
						{
						
							for (tinyxml2::XMLNode* Model = entity->FirstChild(); Model != NULL; Model = Model->NextSibling())
							{

								Value = Model->Value();
								if (strcmp(Value, "Texture") == 0)
								{
									string texture = Model->ToElement()->GetText();
									if (texture == "floor_texture")tempSprite.setTexture(m_vTextureStoneFloorTiles);
									else if (texture == "floor_grass_texture")tempSprite.setTexture(m_vTextureGrassFloorTiles);
									else if (texture == "skybox_sunny_texture")tempSprite.setTexture(m_vTextureSunnySkybox);
									else if (texture == "skybox_water_texture")tempSprite.setTexture(m_vTextureWaterSkybox);
								}
							

							}

						}
					}
					if (type == "skybox")
					{
						tempRect.setPosition(Vector2f(-1000,-1000));
						tempRect.setSize(tempSize);
						tempRect.setRotation(tempRotation);
						tempRect.setFillColor(Color::Red);

						tempSprite.setPosition(tempRect.getPosition() - tempSize/2.0f);
						tempSprite.setScale(tempSize.x / 1024.0f, tempSize.y / 1024.0f);
						//tempSprite.setOrigin(tempSize.x / 2.0f, tempSize.y / 2.0f);
						tempSprite.setRotation(tempRotation);
						
						m_SkyboxRect  = tempRect;
						m_SkyboxSprite = tempSprite;
					}
					else
					{
						tempRect.setPosition(tempPosition);
						tempRect.setSize(tempSize);
						tempRect.setRotation(tempRotation);
						tempRect.setFillColor(Color::Red);

						tempSprite.setPosition(tempRect.getPosition());
						tempSprite.setScale(tempSize.x / 1024.0f, tempSize.y / 1024.0f);
						//tempSprite.setOrigin(tempSize.x / 2.0f, tempSize.y / 2.0f);
						tempSprite.setRotation(tempRotation);

						m_vRectFloorTiles.push_back(tempRect);
						m_vSpriteFloorTiles.push_back(tempSprite);
					}

					
				
				}
				
			}

		}


	}
	


}

void Scene::draw(RenderTarget & target, RenderStates states) const
{
	//draw sky
	target.draw(m_SkyboxSprite);


	//draw floor
	for (int i = 0; i < m_vSpriteFloorTiles.size(); i++)
	{
		target.draw(m_vSpriteFloorTiles.at(i));
	}
	//obsticles
	for (int i = 0; i < m_vObsticleSprites.size(); i++)
	{
		target.draw(m_vObsticleSprites[i]);
	}
	//pickups
	for (int i = 0; i < m_vPickupSprites.size(); i++)
	{
		target.draw(m_vPickupSprites[i]);
	}


	//start/end
	target.draw(m_Player);
	target.draw(m_Goal);

	//lights
	for (int i = 0; i < m_vLightSprites.size(); i++)
	{
		target.draw(m_vLightSprites[i]);
	}


	//placing
	if (m_bPlacing)
	{
		target.draw(m_sfTempRect);
	}

}





void Scene::processClickEvent(Vector2f mousepos)
{
	if (!m_bPlacing)
	{
	}
}

void Scene::tempObject(Vector2f pos, Vector2f size)
{
	m_sfTempRect.setPosition(pos);
	m_sfTempRect.setSize(size);
	m_sfTempRect.setFillColor(Color(0, 255, 0, 125));

}

void Scene::addPickup(Vector2f pos)
{
	RectangleShape tempRect;
	Sprite tempSprite;

	tempRect.setPosition(pos);
	tempRect.setSize(Vector2f(100, 100));

	tempSprite.setPosition(pos);
	tempSprite.setTexture(m_vTexturePickups);

	m_vPickupSprites.push_back(tempSprite);

}

void Scene::addObsticle(Vector2f pos)
{
	RectangleShape tempRect;
	Sprite tempSprite;

	tempRect.setPosition(pos);
	tempRect.setSize(Vector2f(100, 100));

	tempSprite.setPosition(pos);
	tempSprite.setTexture(m_vTextureObsticle);

	m_vObsticleSprites.push_back(tempSprite);
}

void Scene::addLight(Vector2f pos)
{
	RectangleShape tempRect;
	Sprite tempSprite;

	tempRect.setPosition(pos);
	tempRect.setSize(Vector2f(100, 100));

	tempSprite.setPosition(pos);
	tempSprite.setTexture(m_vTextureLight);

	m_vLightSprites.push_back(tempSprite);
}

void Scene::movePlayer(Vector2f pos)
{
	RectangleShape tempRect;
	Sprite tempSprite;

	tempRect.setPosition(pos);
	tempRect.setSize(Vector2f(25, 25));

	tempSprite.setPosition(pos);
	tempSprite.setTexture(m_vTexturePlayer);

	m_Player = tempSprite;

}

void Scene::moveGoal(Vector2f pos)
{
	RectangleShape tempRect;
	Sprite tempSprite;

	tempRect.setPosition(pos);
	tempRect.setSize(Vector2f(100, 100));

	tempSprite.setPosition(pos);
	tempSprite.setTexture(m_vTextureFinish);

	m_Goal = tempSprite;
}

void Scene::loadTextures()
{
	if (!m_vTextureStoneFloorTiles.loadFromFile("../../../Blobsonic/Source/Resources/textures/floor.jpg"))
	{
		cout << "../../../Blobsonic/Source/Resources/textures/floor.jpg - Failed to load" << endl;
	}
	if (!m_vTextureGrassFloorTiles.loadFromFile("../../../Blobsonic/Source/Resources/textures/floor_grass.bmp"))
	{
		cout << "../../../Blobsonic/Source/Resources/textures/floor_grass.bmp - Failed to load" << endl;
	}
	if (!m_vTexturePickups.loadFromFile("../../../Blobsonic/Source/Resources/textures/pickupForEditor.png"))
	{
		cout << "../../../Blobsonic/Source/Resources/textures/pickupForEditor.png - Failed to load" << endl;
	}
	if (!m_vTextureObsticle.loadFromFile("../../../Blobsonic/Source/Resources/textures/obsicleForEditor.jpg"))
	{
		cout << "../../../Blobsonic/Source/Resources/textures/obsicleForEditor.jpg - Failed to load" << endl;
	}
	if (!m_vTextureLight.loadFromFile("../../../Blobsonic/Source/Resources/textures/lightForEditor.png"))
	{
		cout << "../../../Blobsonic/Source/Resources/textures/lightForEditor.png - Failed to load" << endl;
	}
	if (!m_vTextureWaterSkybox.loadFromFile("../../../Blobsonic/Source/Resources/textures/skybox_water.bmp"))
	{
		cout << "../../../Blobsonic/Source/Resources/textures/skybox_water.bmp - Failed to load" << endl;
	}
	if (!m_vTextureSunnySkybox.loadFromFile("../../../Blobsonic/Source/Resources/textures/skybox_sunny.bmp"))
	{
		cout << "../../../Blobsonic/Source/Resources/textures/skybox_sunny.bmp - Failed to load" << endl;
	}
	if (!m_vTexturePlayer.loadFromFile("../../../Blobsonic/Source/Resources/textures/playerForEditor.png"))
	{
		cout << "../../../Blobsonic/Source/Resources/textures/playerForEditor.png - Failed to load" << endl;
	}
	if (!m_vTextureFinish.loadFromFile("../../../Blobsonic/Source/Resources/textures/finishForEditor.png"))
	{
		cout << "../../../Blobsonic/Source/Resources/textures/finishForEditor.png - Failed to load" << endl;
	}

	
	
}
