#include "Scene.h"

Scene::Scene()
{
}

Scene::Scene(string path)
{
	//Load Textures
	loadTextures();


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
				
				else if (strcmp(Value, "Model") == 0)
				{
					RectangleShape tempRect;
					Sprite tempSprite;
					Vector2f tempPosition;
					Vector2f tempSize;
					float tempRotation;

					for (tinyxml2::XMLNode* Model = child2->FirstChild(); Model != NULL; Model = Model->NextSibling())
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
							if (texture == "skybox_texture")tempSprite.setTexture(m_vTextureStoneFloorTiles);
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

					}
					tempRect.setPosition(tempPosition);
					tempRect.setSize(tempSize);
					tempRect.setRotation(tempRotation);
					tempRect.setFillColor(Color::Red);

					tempSprite.setPosition(tempRect.getPosition());
					tempSprite.setScale(tempSize.x / 1024.0f, tempSize.y / 1024.0f);
					//tempSprite.setOrigin(tempSize.x / 2.0f, tempSize.y / 2.0f);
					tempSprite.setRotation(tempRotation);

					Clickable tempClickable;
					tempClickable.m_sfVTopLeftPos = tempPosition;
					tempClickable.m_sfVSize = tempSize;
					pair<RectangleShape, Clickable > floor;
					floor.first = tempRect;
					floor.second = tempClickable;
					m_vRectFloorTiles.push_back(floor);
					m_vSpriteFloorTiles.push_back(tempSprite);
				}
			}

		}


	}
	


}

void Scene::draw(RenderTarget & target, RenderStates states) const
{
	for (int i = 0; i < m_vRectFloorTiles.size(); i++)
	{
		target.draw(m_vRectFloorTiles.at(i));
	}

	for (int i = 0; i < m_vSpriteFloorTiles.size(); i++)
	{
		target.draw(m_vSpriteFloorTiles.at(i));
	}
	
}

void Scene::checkForHovering(Vector2f mousepos)
{
}

void Scene::deselect()
{
	m_bSelected = false;
}

void Scene::processClickEvent(Vector2f mousepos)
{
	//check the floor
	for (int i = 0; i < m_vRectFloorTiles.size(); i++)
	{
		if (m_vRectFloorTiles[i].second.m_bClicked(mousepos))
		{
			m_bSelected = true;
			m_sfSelectedRect = m_vRectFloorTiles[i].first;
			m_sfSelectedRect.setFillColor(Color(0, 255, 0, 125));
			m_sfSelectedSprite = m_vSpriteFloorTiles[i];
			m_sfSelectedRect = m_sfSelectedSprite.getTexture;
		}

	}


}

void Scene::loadTextures()
{
	if (!m_vTextureStoneFloorTiles.loadFromFile("../../../Blobsonic/Source/Resources/textures/floor.jpg"))
	{
		cout << "../../../Blobsonic/Source/Resources/textures/floor.jpg - Failed to load" << endl;
	}
}
