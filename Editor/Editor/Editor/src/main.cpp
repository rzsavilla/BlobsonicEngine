#include <iostream>
#include <SFML\Graphics.hpp>
#include <tinyxml2.h>
#include "Button.h"
#include "Scene.h"

using namespace std;
using namespace sf;
using namespace tinyxml2;

void OpenLevel(string name); // <! Function that opens the desired level in the editor
void NewLevel();// <! Function that creates the basis of the level
void SaveLevel(Scene scenToSave);
bool bMainValid = true;
int iFloor;
int iSkybox;
float fGrid = 100;
float fXDimension;
float fZDimension;
string sLevelName = "";

int main()
{

	

	do
	{
		system("cls");
		cout << "Blobsonic - Level Editor" << endl;
		cout << "-" << endl;
		cout << "-" << endl;
		cout << "- Main Menu" << endl;
		cout << "- 1 : New Level" << endl;
		cout << "- 2 : Quit" << endl;
		cout << endl << "- : ";

		int iMenuInput;
		cin >> iMenuInput;

		if (iMenuInput != 1 && iMenuInput != 2 ) bMainValid = false;
		else
		{
			if (iMenuInput == 1)NewLevel();
			if (iMenuInput == 2)bMainValid = true;
		}


	} while (bMainValid == false);




	return 0;
}

void OpenLevel(string name)
{
	string path = "../../../Blobsonic/Source/Resources/scenes/" + name + ".xml";

	Scene scene(path);

	bool bplacing = false;
	string sPlacing = "";

	//create an sfml window
	RenderWindow window(VideoMode(1280, 720), "Editor - " + name + ".xml");
	window.setFramerateLimit(60);

	//create a view to fill the windowfor game render
	View gameView;
	gameView.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	gameView.setCenter(sf::Vector2f(1280 / 2, 720 / 2));
	gameView.setSize(sf::Vector2f(1280, 720));

	//create a view to fill the windowfor game render
	View hudView;
	hudView.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	hudView.setCenter(sf::Vector2f(1280 / 2, 720 / 2));
	hudView.setSize(sf::Vector2f(1280, 720));

	//create Buttons for the editor---------------------------------
	Button PickupsButton
	("Pickup",
		Vector2f(0, 0),
		Vector2f(300 ,88.5f),
		Vector2f(1,1),
		"Button_Green"
	);
	Button LightButton
	("Light",
		Vector2f(0, 90),
		Vector2f(300, 88.5f),
		Vector2f(1, 1),
		"Button_Green"
	);
	Button ObsticleButton
	("Obstical",
		Vector2f(0, 180),
		Vector2f(300, 88.5f),
		Vector2f(1, 1),
		"Button_Green"
	);
	Button PlayerButton
	("Start Position",
		Vector2f(0, 270),
		Vector2f(300, 88.5f),
		Vector2f(1, 1),
		"Button_Green"
	);
	Button EndButton
	("Finish Position",
		Vector2f(0, 360),
		Vector2f(300, 88.5f),
		Vector2f(1, 1),
		"Button_Green"
	);

	Button SaveButton
	("Save & Quit",
		Vector2f(0, 630),
		Vector2f(300, 88.5f),
		Vector2f(1, 1),
		"Button_Green"
	);


	Clock inputClock;
	Time inputTime;

	//window loop
	while (window.isOpen())
	{

		// Event processing
		Event event;
		int iMouseWheel;
		Vector2f sfMousePos;
		Vector2f sfPlacingPos;


		sfPlacingPos = window.mapPixelToCoords(Mouse::getPosition(window), gameView);
		sfMousePos = window.mapPixelToCoords(Mouse::getPosition(window), hudView);

		while (window.pollEvent(event))
		{


			if (bplacing)
			{
				//show the temp object
				if (sPlacing == "Pickup")scene.tempObject(sfPlacingPos, Vector2f(100, 100));
				if (sPlacing == "Obsticle")scene.tempObject(sfPlacingPos, Vector2f(100, 100));
				if (sPlacing == "Light")scene.tempObject(sfPlacingPos, Vector2f(500, 500));
				if (sPlacing == "Player")scene.tempObject(sfPlacingPos, Vector2f(25, 25));
				if (sPlacing == "Finish")scene.tempObject(sfPlacingPos, Vector2f(100, 100));
			
			}

			//move camera
			float fMoveSpeed = 10;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
			{
				fMoveSpeed *= 3;
			}
			//key presses
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
			{
				gameView.move(Vector2f(0.0f, -fMoveSpeed));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			{
				gameView.move(Vector2f(0.0f, fMoveSpeed));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			{
				gameView.move(Vector2f(-fMoveSpeed, 0.0f));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			{
				gameView.move(Vector2f(fMoveSpeed, 0.0f));
			}

			if (event.type == Event::MouseWheelMoved)
			{
				iMouseWheel = event.mouseWheel.delta;
				if (iMouseWheel > 0)
				{
					//zoom in
					gameView.zoom(0.9);
				}
				if (iMouseWheel < 0)
				{
					//zoom out
					gameView.zoom(1.1);
				}
			}
		}


		if (sf::Event::MouseButtonPressed)
		{

			if (Mouse::isButtonPressed(sf::Mouse::Right))
			{
				bplacing = false;
				scene.m_bPlacing = false;
			}
			if (Mouse::isButtonPressed(sf::Mouse::Left))
			{

				if (bplacing)
				{
					inputTime = inputClock.getElapsedTime();
					if (inputTime.asSeconds() > 1.0f)
					{
						//place the object
						if (sPlacing == "Pickup")
						{
							scene.addPickup(sfPlacingPos);
							scene.m_bPlacing = false;
							bplacing = false;
						}
						if (sPlacing == "Obsticle")
						{
							scene.addObsticle(sfPlacingPos);
							scene.m_bPlacing = false;
							bplacing = false;
						}
						if (sPlacing == "Light")
						{
							scene.addLight(sfPlacingPos);
							scene.m_bPlacing = false;
							bplacing = false;
						}
						if (sPlacing == "Player")
						{
							scene.movePlayer(sfPlacingPos);
							scene.m_bPlacing = false;
							bplacing = false;
						}
						if (sPlacing == "Finish")
						{
							scene.moveGoal(sfPlacingPos);
							scene.m_bPlacing = false;
							bplacing = false;
						}
						
					}
					
				}
				if (!bplacing)
				{
					//check buttons

					if (PickupsButton.m_bClicked(sfMousePos))
					{
						sPlacing = "Pickup";
						scene.m_bPlacing = true;
						bplacing = true;
						inputClock.restart();

					}
					else if (ObsticleButton.m_bClicked(sfMousePos))
					{
						sPlacing = "Obsticle";
						scene.m_bPlacing = true;
						bplacing = true;
						inputClock.restart();

					}
					else if (LightButton.m_bClicked(sfMousePos))
					{
						sPlacing = "Light";
						scene.m_bPlacing = true;
						bplacing = true;
						inputClock.restart();

					}
					else if (PlayerButton.m_bClicked(sfMousePos))
					{
						sPlacing = "Player";
						scene.m_bPlacing = true;
						bplacing = true;
						inputClock.restart();

					}
					else if (EndButton.m_bClicked(sfMousePos))
					{
						sPlacing = "Finish";
						scene.m_bPlacing = true;
						bplacing = true;
						inputClock.restart();

					}

					else if (SaveButton.m_bClicked(sfMousePos))
					{
						//save and close
						window.close();
						SaveLevel(scene);
						bMainValid = false;
						return;
					}

					else
					{
						scene.processClickEvent(sfPlacingPos);
					}

				}
				
			}
		}


	

		//if(Keyboard::Escape == Keyboard)

		window.clear(Color::Black);

		//draw the game 
		window.setView(gameView);

		window.draw(scene);

		//draw the hud
		window.setView(hudView);
		if (!bplacing)
		{
			window.draw(PickupsButton);
			window.draw(LightButton);
			window.draw(PlayerButton);
			window.draw(ObsticleButton);
			window.draw(EndButton);
			window.draw(SaveButton);
		}

		
		window.display();


	}




}

void NewLevel()
{
	system("cls");
	cout << "Blobsonic - Level Editor" << endl;
	cout << "-" << endl;
	cout << "-" << endl;
	cout << "- Create new level" << endl;
	cout << "- " << endl;
	
	//take the levels name
	cout << "- Name of level : ";
	
	cin >> sLevelName;


	//grid size
	//take the levels size
	cout << "- " << endl;
	cout << "- " << endl;
	cout << "- Size of Grid units : ";
	
	cin >> fGrid;
	

	//take the levels size
	cout << "- " << endl;
	cout << "- 1 Unit = " << fGrid << " pixels" << endl;
	cout << "- " << endl;
	cout << "- Width of level (units) : ";
	
	cin >> fXDimension;

	//take the levels size
	cout << "- " << endl;
	cout << "- Depth of level (units) : ";
	
	cin >> fZDimension;

	//Skybox type
	cout << "- " << endl;
	cout << "- Skybox type : " << endl;
	cout << "- 1) Water" << endl;
	cout << "- 2) Sunny" << endl;
	
	cin >> iSkybox;

	//Floor type
	cout << "- " << endl;
	cout << "- Floor type : " << endl;
	cout << "- 1) Rock" << endl;
	cout << "- 2) Grass" << endl;
	cout << "- 3) Blue" << endl;
	cout << "- 4) Brown" << endl;
	cout << "- 5) Green" << endl;
	
	cin >> iFloor;

	//take these parameters and create a blank level with them

	//create the document
	XMLDocument xmlDoc;

	//add ResourceFile
	XMLNode * ResourceFile = xmlDoc.NewElement("ResourceFile");
	XMLElement * Location = xmlDoc.NewElement("Location");
	ResourceFile->InsertFirstChild(Location);
	Location->SetText("Source\\Resources\\Scenes\\Resources.xml");
	ResourceFile->InsertEndChild(Location);
	xmlDoc.InsertEndChild(ResourceFile);

	XMLNode * pScene = xmlDoc.NewElement("Scene");
	xmlDoc.InsertFirstChild(pScene);


	//saving the name of the level
	XMLElement * pName = xmlDoc.NewElement("LevelName");
	pName->SetText(sLevelName.c_str());
	pScene->InsertEndChild(pName);

	//saving the name of the level
	XMLElement * Type = xmlDoc.NewElement("Type");
	Type->SetText("Game");
	pScene->InsertEndChild(Type);

	//saving the name of the level
	XMLElement * SceneID = xmlDoc.NewElement("ID");
	SceneID->SetText("game_scene");
	pScene->InsertEndChild(SceneID);

	//saving the size of the level
	XMLElement * pLevelSize = xmlDoc.NewElement("GridSize");
	pLevelSize->SetText(fGrid);
	pScene->InsertEndChild(pLevelSize);

	//saving the size of the level
	XMLElement * pLevelDimensions = xmlDoc.NewElement("Dimensions");
	pScene->InsertFirstChild(pLevelDimensions);
		XMLElement * xCol = xmlDoc.NewElement("X");
		pLevelDimensions->InsertFirstChild(xCol);
		xCol->SetText(fXDimension);
		pLevelDimensions->InsertEndChild(xCol);

		XMLElement * zCol = xmlDoc.NewElement("Z");
		pLevelDimensions->InsertFirstChild(zCol);
		zCol->SetText(fZDimension);
		pLevelDimensions->InsertEndChild(zCol);

	pScene->InsertEndChild(pLevelDimensions);

	//create the default floor
	for (int x = 0; x < fXDimension; x++)
	{
		for (int z = 0; z < fZDimension; z++)
		{

			//Entity
			XMLElement * Entity = xmlDoc.NewElement("Entity");
			pScene->InsertFirstChild(Entity);

			//ID
			XMLElement * ID = xmlDoc.NewElement("Name");
			Entity->InsertFirstChild(ID);
			ID->SetText("floor");
			Entity->InsertEndChild(ID);

			//Transformable
			XMLElement * Transformable = xmlDoc.NewElement("Transformable");
			Entity->InsertFirstChild(Transformable);

			//Position
			XMLElement * Position = xmlDoc.NewElement("Position");
			Transformable->InsertFirstChild(Position);

			XMLElement * posx = xmlDoc.NewElement("X");
			XMLElement * posy = xmlDoc.NewElement("Y");
			XMLElement * posz = xmlDoc.NewElement("Z");

			//x
			Position->InsertFirstChild(posx);
			posx->SetText(fGrid * x);
			Position->InsertEndChild(posx);

			//y
			Position->InsertFirstChild(posy);
			posy->SetText(0);
			Position->InsertEndChild(posy);

			//z
			Position->InsertFirstChild(posz);
			posz->SetText(fGrid * z);
			Position->InsertEndChild(posz);


			Transformable->InsertEndChild(Position);

			//Scale
			XMLElement * Scale = xmlDoc.NewElement("Scale");
			Transformable->InsertFirstChild(Scale);
			XMLElement * ScaleX = xmlDoc.NewElement("X");
			XMLElement * Scaley = xmlDoc.NewElement("Y");
			XMLElement * ScaleZ = xmlDoc.NewElement("Z");

			//x
			Scale->InsertFirstChild(ScaleX);
			ScaleX->SetText(fGrid);
			Scale->InsertEndChild(ScaleX);

			//y
			Scale->InsertFirstChild(Scaley);
			Scaley->SetText(1.0f);
			Scale->InsertEndChild(Scaley);

			//z
			Scale->InsertFirstChild(ScaleZ);
			ScaleZ->SetText(fGrid);
			Scale->InsertEndChild(ScaleZ);


			Transformable->InsertEndChild(Scale);

			//Rotation
			XMLElement * Rotation = xmlDoc.NewElement("Rotation");
			Transformable->InsertFirstChild(Rotation);
			XMLElement * RotationX = xmlDoc.NewElement("X");
			XMLElement * Rotationy = xmlDoc.NewElement("Y");
			XMLElement * RotationZ = xmlDoc.NewElement("Z");

			//x
			Rotation->InsertFirstChild(RotationX);
			RotationX->SetText(0);
			Rotation->InsertEndChild(RotationX);

			//y
			Rotation->InsertFirstChild(Rotationy);
			Rotationy->SetText(0);
			Rotation->InsertEndChild(Rotationy);

			//z
			Rotation->InsertFirstChild(RotationZ);
			RotationZ->SetText(0);
			Rotation->InsertEndChild(RotationZ);


			Transformable->InsertEndChild(Rotation);

			//Origin
			XMLElement * Origin = xmlDoc.NewElement("Origin");
			Transformable->InsertFirstChild(Origin);
			XMLElement * OriginX = xmlDoc.NewElement("X");
			XMLElement * Originy = xmlDoc.NewElement("Y");
			XMLElement * OriginZ = xmlDoc.NewElement("Z");

			//x
			Origin->InsertFirstChild(OriginX);
			OriginX->SetText(0);
			Origin->InsertEndChild(OriginX);

			//y
			Origin->InsertFirstChild(Originy);
			Originy->SetText(0);
			Origin->InsertEndChild(Originy);

			//z
			Origin->InsertFirstChild(OriginZ);
			OriginZ->SetText(0);
			Origin->InsertEndChild(OriginZ);


			Transformable->InsertEndChild(Origin);


			Entity->InsertEndChild(Transformable);


			//Physical
			XMLElement * Physical = xmlDoc.NewElement("Physical");
			Entity->InsertFirstChild(Physical);

			//Mass
			XMLElement * Mass = xmlDoc.NewElement("Mass");
			Physical->InsertFirstChild(Mass);
			Mass->SetText(0.0f);
			Physical->InsertEndChild(Mass);

			//Restitution
			XMLElement * Restitution = xmlDoc.NewElement("Restitution");
			Physical->InsertFirstChild(Restitution);
			Restitution->SetText(0.1f);
			Physical->InsertEndChild(Restitution);

			Entity->InsertEndChild(Physical);

			

			//AABB
			for (int i = 0; i < 1; i++)
			{
				XMLElement * AABB = xmlDoc.NewElement("AABB");
				Entity->InsertFirstChild(AABB);
				//Position
				XMLElement * Position = xmlDoc.NewElement("Position");
				AABB->InsertFirstChild(Position);

				XMLElement * posx = xmlDoc.NewElement("X");
				XMLElement * posy = xmlDoc.NewElement("Y");
				XMLElement * posz = xmlDoc.NewElement("Z");

				//x
				Position->InsertFirstChild(posx);
				posx->SetText(fGrid * x);
				Position->InsertEndChild(posx);

				//y
				Position->InsertFirstChild(posy);
				posy->SetText(0);
				Position->InsertEndChild(posy);

				//z
				Position->InsertFirstChild(posz);
				posz->SetText(fGrid * z);
				Position->InsertEndChild(posz);


				AABB->InsertEndChild(Position);

				//Scale
				XMLElement * Scale = xmlDoc.NewElement("Scale");
				AABB->InsertFirstChild(Scale);
				XMLElement * ScaleX = xmlDoc.NewElement("X");
				XMLElement * Scaley = xmlDoc.NewElement("Y");
				XMLElement * ScaleZ = xmlDoc.NewElement("Z");

				//x
				Scale->InsertFirstChild(ScaleX);
				ScaleX->SetText(fGrid);
				Scale->InsertEndChild(ScaleX);

				//y
				Scale->InsertFirstChild(Scaley);
				Scaley->SetText(1.0f);
				Scale->InsertEndChild(Scaley);

				//z
				Scale->InsertFirstChild(ScaleZ);
				ScaleZ->SetText(fGrid);
				Scale->InsertEndChild(ScaleZ);


				AABB->InsertEndChild(Scale);

				//Origin
				XMLElement * Origin = xmlDoc.NewElement("Origin");
				AABB->InsertFirstChild(Origin);
				XMLElement * OriginX = xmlDoc.NewElement("X");
				XMLElement * Originy = xmlDoc.NewElement("Y");
				XMLElement * OriginZ = xmlDoc.NewElement("Z");

				//x
				Origin->InsertFirstChild(OriginX);
				OriginX->SetText(0);
				Origin->InsertEndChild(OriginX);

				//y
				Origin->InsertFirstChild(Originy);
				Originy->SetText(0);
				Origin->InsertEndChild(Originy);

				//z
				Origin->InsertFirstChild(OriginZ);
				OriginZ->SetText(0);
				Origin->InsertEndChild(OriginZ);


				AABB->InsertEndChild(Origin);
				Entity->InsertEndChild(AABB);
			}

			//OBB
			for (int i = 0; i < 1; i++)
			{
				XMLElement * OBB = xmlDoc.NewElement("OBB");
				Entity->InsertFirstChild(OBB);

				//Position
				XMLElement * Position = xmlDoc.NewElement("Position");
				OBB->InsertFirstChild(Position);

				XMLElement * posx = xmlDoc.NewElement("X");
				XMLElement * posy = xmlDoc.NewElement("Y");
				XMLElement * posz = xmlDoc.NewElement("Z");

				//x
				Position->InsertFirstChild(posx);
				posx->SetText(fGrid * x);
				Position->InsertEndChild(posx);

				//y
				Position->InsertFirstChild(posy);
				posy->SetText(0);
				Position->InsertEndChild(posy);

				//z
				Position->InsertFirstChild(posz);
				posz->SetText(fGrid * z);
				Position->InsertEndChild(posz);


				OBB->InsertEndChild(Position);

				//Scale
				XMLElement * Scale = xmlDoc.NewElement("Scale");
				OBB->InsertFirstChild(Scale);
				XMLElement * ScaleX = xmlDoc.NewElement("X");
				XMLElement * Scaley = xmlDoc.NewElement("Y");
				XMLElement * ScaleZ = xmlDoc.NewElement("Z");

				//x
				Scale->InsertFirstChild(ScaleX);
				ScaleX->SetText(fGrid);
				Scale->InsertEndChild(ScaleX);

				//y
				Scale->InsertFirstChild(Scaley);
				Scaley->SetText(1.0f);
				Scale->InsertEndChild(Scaley);

				//z
				Scale->InsertFirstChild(ScaleZ);
				ScaleZ->SetText(fGrid);
				Scale->InsertEndChild(ScaleZ);


				OBB->InsertEndChild(Scale);

				//Rotation
				XMLElement * Rotation = xmlDoc.NewElement("Rotation");
				OBB->InsertFirstChild(Rotation);
				XMLElement * RotationX = xmlDoc.NewElement("X");
				XMLElement * Rotationy = xmlDoc.NewElement("Y");
				XMLElement * RotationZ = xmlDoc.NewElement("Z");

				//x
				Rotation->InsertFirstChild(RotationX);
				RotationX->SetText(0);
				Rotation->InsertEndChild(RotationX);

				//y
				Rotation->InsertFirstChild(Rotationy);
				Rotationy->SetText(0);
				Rotation->InsertEndChild(Rotationy);

				//z
				Rotation->InsertFirstChild(RotationZ);
				RotationZ->SetText(0);
				Rotation->InsertEndChild(RotationZ);


				OBB->InsertEndChild(Rotation);


				//Origin
				XMLElement * Origin = xmlDoc.NewElement("Origin");
				OBB->InsertFirstChild(Origin);
				XMLElement * OriginX = xmlDoc.NewElement("X");
				XMLElement * Originy = xmlDoc.NewElement("Y");
				XMLElement * OriginZ = xmlDoc.NewElement("Z");

				//x
				Origin->InsertFirstChild(OriginX);
				OriginX->SetText(0);
				Origin->InsertEndChild(OriginX);

				//y
				Origin->InsertFirstChild(Originy);
				Originy->SetText(0);
				Origin->InsertEndChild(Originy);

				//z
				Origin->InsertFirstChild(OriginZ);
				OriginZ->SetText(0);
				Origin->InsertEndChild(OriginZ);


				OBB->InsertEndChild(Origin);
				Entity->InsertEndChild(OBB);
			}

			//Model
			XMLElement * Model = xmlDoc.NewElement("Model");
			Entity->InsertFirstChild(Model);

				//mesh

				XMLElement * Mesh = xmlDoc.NewElement("Mesh");
				Model->InsertFirstChild(Mesh);
				Mesh->SetText("plane_mesh");
				Model->InsertEndChild(Mesh);

				//Material
				XMLElement * Material = xmlDoc.NewElement("Material");
				Model->InsertFirstChild(Material);
				Material->SetText("default_material");
				Model->InsertEndChild(Material);

				//Shader
				XMLElement * Shader = xmlDoc.NewElement("Shader");
				Model->InsertFirstChild(Shader);
				Shader->SetText("phong_shader");
				Model->InsertEndChild(Shader);

				//texture
				XMLElement * Texture = xmlDoc.NewElement("Texture");
				Model->InsertFirstChild(Texture);
				if (iFloor == 1)Texture->SetText("floor_texture");
				if (iFloor == 2)Texture->SetText("floor_grass_texture");
				if (iFloor == 3)Texture->SetText("floor_blue_texture");
				if (iFloor == 4)Texture->SetText("floor_brown_texture");
				if (iFloor == 5)Texture->SetText("floor_green_texture");
				Model->InsertEndChild(Texture);
			Entity->InsertEndChild(Model);

	

			pScene->InsertEndChild(Entity);
		}
	}


	//create the default skybox
	for (int i = 0; i < 1; i++)
	{

		//Entity
		XMLElement * Entity = xmlDoc.NewElement("Entity");
		pScene->InsertFirstChild(Entity);

		//ID
		XMLElement * ID = xmlDoc.NewElement("Name");
		Entity->InsertFirstChild(ID);
		ID->SetText("skybox");
		Entity->InsertEndChild(ID);


		//Transformable
		XMLElement * Transformable = xmlDoc.NewElement("Transformable");
		Entity->InsertFirstChild(Transformable);

		//Position
		XMLElement * Position = xmlDoc.NewElement("Position");
		Transformable->InsertFirstChild(Position);
		XMLElement * posx = xmlDoc.NewElement("X");
		XMLElement * posy = xmlDoc.NewElement("Y");
		XMLElement * posz = xmlDoc.NewElement("Z");

		//x
		Position->InsertFirstChild(posx);
		posx->SetText(0.0f);
		Position->InsertEndChild(posx);

		//y
		Position->InsertFirstChild(posy);
		posy->SetText(0.0f);
		Position->InsertEndChild(posy);

		//z
		Position->InsertFirstChild(posz);
		posz->SetText(0.0f);
		Position->InsertEndChild(posz);


		Transformable->InsertEndChild(Position);

		//Scale
		XMLElement * Scale = xmlDoc.NewElement("Scale");
		Transformable->InsertFirstChild(Scale);
		XMLElement * ScaleX = xmlDoc.NewElement("X");
		XMLElement * Scaley = xmlDoc.NewElement("Y");
		XMLElement * ScaleZ = xmlDoc.NewElement("Z");

		//x
		Scale->InsertFirstChild(ScaleX);
		ScaleX->SetText(fGrid * fXDimension);
		Scale->InsertEndChild(ScaleX);

		//y
		Scale->InsertFirstChild(Scaley);
		Scaley->SetText(fGrid * max(fXDimension, fZDimension));
		Scale->InsertEndChild(Scaley);

		//z
		Scale->InsertFirstChild(ScaleZ);
		ScaleZ->SetText(fGrid * fZDimension);
		Scale->InsertEndChild(ScaleZ);


		Transformable->InsertEndChild(Scale);

		//Rotation
		XMLElement * Rotation = xmlDoc.NewElement("Rotation");
		Transformable->InsertFirstChild(Rotation);
		XMLElement * RotX = xmlDoc.NewElement("X");
		XMLElement * RotY = xmlDoc.NewElement("Y");
		XMLElement * RotZ = xmlDoc.NewElement("Z");

		//x
		Rotation->InsertFirstChild(RotX);
		RotX->SetText(0.0f);
		Rotation->InsertEndChild(RotX);

		//y
		Rotation->InsertFirstChild(RotY);
		RotY->SetText(0.0f);
		Rotation->InsertEndChild(RotY);

		//z
		Rotation->InsertFirstChild(RotZ);
		RotZ->SetText(180.0f);
		Rotation->InsertEndChild(RotZ);
		Transformable->InsertEndChild(Rotation);

		Entity->InsertEndChild(Transformable);

		//Model
		XMLElement * Model = xmlDoc.NewElement("Model");
		Entity->InsertFirstChild(Model);

		

		//mesh
		XMLElement * Mesh = xmlDoc.NewElement("Mesh");
		Model->InsertFirstChild(Mesh);
		if (iSkybox == 1)Mesh->SetText("skybox_water_mesh");
		if (iSkybox == 2)Mesh->SetText("skybox_sunny_mesh");
		Model->InsertEndChild(Mesh);

		//Material
		XMLElement * Material = xmlDoc.NewElement("Material");
		Model->InsertFirstChild(Material);
		Material->SetText("default_material");
		Model->InsertEndChild(Material);

		//Shader
		XMLElement * Shader = xmlDoc.NewElement("Shader");
		Model->InsertFirstChild(Shader);
		Shader->SetText("phong_shader");
		Model->InsertEndChild(Shader);

		//texture
		XMLElement * Texture = xmlDoc.NewElement("Texture");
		Model->InsertFirstChild(Texture);
		if (iSkybox == 1)Texture->SetText("skybox_water_texture");
		if (iSkybox == 2)Texture->SetText("skybox_sunny_texture");
		

		Entity->InsertEndChild(Model);

		pScene->InsertEndChild(Entity);
	}


	//Create the camera
	XMLElement * Camera = xmlDoc.NewElement("Camera");
	pScene->InsertFirstChild(Camera);

	for (int i = 0; i < 1; i++)
	{
		//ID
		XMLElement * CID = xmlDoc.NewElement("Name");
		Camera->InsertFirstChild(CID);
		CID->SetText("cam1");
		Camera->InsertEndChild(CID);

		//Position
		XMLElement * Position = xmlDoc.NewElement("Position");
		Camera->InsertFirstChild(Position);
		XMLElement * posx = xmlDoc.NewElement("X");
		XMLElement * posy = xmlDoc.NewElement("Y");
		XMLElement * posz = xmlDoc.NewElement("Z");

			//x
			Position->InsertFirstChild(posx);
			posx->SetText(fGrid * fXDimension / 2);
			Position->InsertEndChild(posx);

			//y
			Position->InsertFirstChild(posy);
			posy->SetText(fGrid * max(fXDimension, fZDimension) / 2);
			Position->InsertEndChild(posy);

			//z
			Position->InsertFirstChild(posz);
			posz->SetText(fGrid * fZDimension / 2);
			Position->InsertEndChild(posz);

		Camera->InsertEndChild(Position);

		//Orientation
		XMLElement * Orientation = xmlDoc.NewElement("Orientation");
		Camera->InsertFirstChild(Orientation);
		XMLElement * orx = xmlDoc.NewElement("x");
		XMLElement * ory = xmlDoc.NewElement("Y");
		XMLElement * orz = xmlDoc.NewElement("Z");

		//x
		Orientation->InsertFirstChild(orx);
		orx->SetText(0);
		Orientation->InsertEndChild(orx);

		//y
		Orientation->InsertFirstChild(ory);
		ory->SetText(45.0f);
		Orientation->InsertEndChild(ory);

		//z
		Orientation->InsertFirstChild(orz);
		orz->SetText(0);
		Orientation->InsertEndChild(orz);


		Camera->InsertEndChild(Orientation);

		//FOV
		XMLElement * FOV = xmlDoc.NewElement("FOV");
		Camera->InsertFirstChild(FOV);
		FOV->SetText(70.0f);
		Camera->InsertEndChild(FOV);

		//AspectRatio
		XMLElement * AspectRatio = xmlDoc.NewElement("AspectRatio");
		Camera->InsertFirstChild(AspectRatio);
		AspectRatio->SetText(1.3333f);
		Camera->InsertEndChild(AspectRatio);

		//FarPlane
		XMLElement * FarPlane = xmlDoc.NewElement("FarPlane");
		Camera->InsertFirstChild(FarPlane);
		FarPlane->SetText(100000 * fGrid * max(fXDimension, fZDimension));
		Camera->InsertEndChild(FarPlane);

		//NearPlane
		XMLElement * NearPlane = xmlDoc.NewElement("NearPlane");
		Camera->InsertFirstChild(NearPlane);
		NearPlane->SetText(0.1f);
		Camera->InsertEndChild(NearPlane);

		//RotSpeed
		XMLElement * RotSpeed = xmlDoc.NewElement("RotSpeed");
		Camera->InsertFirstChild(RotSpeed);
		RotSpeed->SetText(0.5f);
		Camera->InsertEndChild(RotSpeed);

		//MoveSpeed
		XMLElement * MoveSpeed = xmlDoc.NewElement("MoveSpeed");
		Camera->InsertFirstChild(MoveSpeed);
		MoveSpeed->SetText(0.8f);
		Camera->InsertEndChild(MoveSpeed);

	}
		
	pScene->InsertEndChild(Camera);


	//create default light
	XMLElement * Light = xmlDoc.NewElement("Light");
	pScene->InsertFirstChild(Light);

	for (int i = 0; i < 1; i++)
	{

		//ID
		XMLElement * ID = xmlDoc.NewElement("ID");
		Light->InsertFirstChild(ID);
		ID->SetText("light1");
		Light->InsertEndChild(ID);

		//Type
		XMLElement * Type = xmlDoc.NewElement("Type");
		Light->InsertFirstChild(Type);
		Type->SetText("Directional");
		Light->InsertEndChild(Type);

		
		//Direction
		XMLElement * Direction = xmlDoc.NewElement("Direction");
		Light->InsertFirstChild(Direction);

		XMLElement * dirx = xmlDoc.NewElement("X");
		XMLElement * diry = xmlDoc.NewElement("Y");
		XMLElement * dirz = xmlDoc.NewElement("Z");

			//x
			Direction->InsertFirstChild(dirx);
			dirx->SetText(0.5f);
			Direction->InsertEndChild(dirx);

			//y
			Direction->InsertFirstChild(diry);
			diry->SetText(-0.5f);
			Direction->InsertEndChild(diry);

			//z
			Direction->InsertFirstChild(dirz);
			dirz->SetText(0.5f);
			Direction->InsertEndChild(dirz);

		Light->InsertEndChild(Direction);

		//Ambient
		XMLElement * Ambient = xmlDoc.NewElement("Ambient");
		Light->InsertFirstChild(Ambient);

		XMLElement * ambx = xmlDoc.NewElement("X");
		XMLElement * amby = xmlDoc.NewElement("Y");
		XMLElement * ambz = xmlDoc.NewElement("Z");

			//x
			Ambient->InsertFirstChild(ambx);
			ambx->SetText(1.0f);
			Ambient->InsertEndChild(ambx);

			//y
			Ambient->InsertFirstChild(amby);
			amby->SetText(1.0f);
			Ambient->InsertEndChild(amby);

			//z
			Ambient->InsertFirstChild(ambz);
			ambz->SetText(1.0f);
			Ambient->InsertEndChild(ambz);

		Light->InsertEndChild(Ambient);

		//Diffuse
		XMLElement * Diffuse = xmlDoc.NewElement("Diffuse");
		Light->InsertFirstChild(Diffuse);

		XMLElement * diffx = xmlDoc.NewElement("X");
		XMLElement * diffy = xmlDoc.NewElement("Y");
		XMLElement * diffz = xmlDoc.NewElement("Z");

			//x
			Diffuse->InsertFirstChild(diffx);
			diffx->SetText(0.5f);
			Diffuse->InsertEndChild(diffx);

			//y
			Diffuse->InsertFirstChild(diffy);
			diffy->SetText(0.5f);
			Diffuse->InsertEndChild(diffy);

			//z
			Diffuse->InsertFirstChild(diffz);
			diffz->SetText(0.5f);
			Diffuse->InsertEndChild(diffz);

		Light->InsertEndChild(Diffuse);

		//Specular
		XMLElement * Specular = xmlDoc.NewElement("Specular");
		Light->InsertFirstChild(Specular);

		XMLElement * specx = xmlDoc.NewElement("X");
		XMLElement * specy = xmlDoc.NewElement("Y");
		XMLElement * specz = xmlDoc.NewElement("Z");

			//x
			Specular->InsertFirstChild(specx);
			specx->SetText(0.5f);
			Specular->InsertEndChild(specx);

			//y
			Specular->InsertFirstChild(specy);
			specy->SetText(0.5f);
			Specular->InsertEndChild(specy);

			//z
			Specular->InsertFirstChild(specz);
			specz->SetText(0.5f);
			Specular->InsertEndChild(specz);

		Light->InsertEndChild(Specular);


	}


	pScene->InsertEndChild(Light);

	xmlDoc.InsertEndChild(pScene);


	//save the finished file
	xmlDoc.SaveFile(("../../../Blobsonic/Source/Resources/scenes/" + sLevelName + ".xml").c_str());

	OpenLevel(sLevelName);

}

void SaveLevel(Scene sceneToSave)
{
	//create the document
	XMLDocument xmlDoc;

	//add ResourceFile
	XMLNode * ResourceFile = xmlDoc.NewElement("ResourceFile");
	XMLElement * Location = xmlDoc.NewElement("Location");
	ResourceFile->InsertFirstChild(Location);
	Location->SetText("Source\\Resources\\Scenes\\Resources.xml");
	ResourceFile->InsertEndChild(Location);
	xmlDoc.InsertEndChild(ResourceFile);

	XMLNode * pScene = xmlDoc.NewElement("Scene");
	xmlDoc.InsertFirstChild(pScene);


	//saving the name of the level
	XMLElement * pName = xmlDoc.NewElement("LevelName");
	pName->SetText(sceneToSave.LevelName.c_str());
	pScene->InsertEndChild(pName);

	//saving the name of the level
	XMLElement * SceneID = xmlDoc.NewElement("ID");
	SceneID->SetText("game_scene");
	pScene->InsertEndChild(SceneID);

	//saving the name of the level
	XMLElement * Type = xmlDoc.NewElement("Type");
	Type->SetText("Game");
	pScene->InsertEndChild(Type);


	//saving the size of the level
	XMLElement * pLevelSize = xmlDoc.NewElement("GridSize");
	pLevelSize->SetText(sceneToSave.m_fGridSize);
	pScene->InsertEndChild(pLevelSize);

	//saving the size of the level
	XMLElement * pLevelDimensions = xmlDoc.NewElement("Dimensions");
	pScene->InsertFirstChild(pLevelDimensions);
	XMLElement * xCol = xmlDoc.NewElement("X");
	pLevelDimensions->InsertFirstChild(xCol);
	xCol->SetText(sceneToSave.m_fXDimensions);
	pLevelDimensions->InsertEndChild(xCol);

	XMLElement * zCol = xmlDoc.NewElement("Z");
	pLevelDimensions->InsertFirstChild(zCol);
	zCol->SetText(sceneToSave.m_fXDimensions);
	pLevelDimensions->InsertEndChild(zCol);

	pScene->InsertEndChild(pLevelDimensions);

	//create the default floor
	for (int i = 0; i < sceneToSave.m_vSpriteFloorTiles.size(); i++)
	{

		//Entity
		XMLElement * Entity = xmlDoc.NewElement("Entity");
		pScene->InsertFirstChild(Entity);

		//ID
		XMLElement * ID = xmlDoc.NewElement("Name");
		Entity->InsertFirstChild(ID);
		ID->SetText("floor");
		Entity->InsertEndChild(ID);

		//Transformable
		XMLElement * Transformable = xmlDoc.NewElement("Transformable");
		Entity->InsertFirstChild(Transformable);

		//Position
		XMLElement * Position = xmlDoc.NewElement("Position");
		Transformable->InsertFirstChild(Position);

		XMLElement * posx = xmlDoc.NewElement("X");
		XMLElement * posy = xmlDoc.NewElement("Y");
		XMLElement * posz = xmlDoc.NewElement("Z");

		//x
		Position->InsertFirstChild(posx);
		posx->SetText(sceneToSave.m_vSpriteFloorTiles[i].getPosition().x);
		Position->InsertEndChild(posx);

		//y
		Position->InsertFirstChild(posy);
		posy->SetText(0);
		Position->InsertEndChild(posy);

		//z
		Position->InsertFirstChild(posz);
		posz->SetText(sceneToSave.m_vSpriteFloorTiles[i].getPosition().y);
		Position->InsertEndChild(posz);


		Transformable->InsertEndChild(Position);

		//Scale
		XMLElement * Scale = xmlDoc.NewElement("Scale");
		Transformable->InsertFirstChild(Scale);
		XMLElement * ScaleX = xmlDoc.NewElement("X");
		XMLElement * Scaley = xmlDoc.NewElement("Y");
		XMLElement * ScaleZ = xmlDoc.NewElement("Z");

		//x
		Scale->InsertFirstChild(ScaleX);
		ScaleX->SetText(sceneToSave.m_fGridSize);
		Scale->InsertEndChild(ScaleX);

		//y
		Scale->InsertFirstChild(Scaley);
		Scaley->SetText(1.0f);
		Scale->InsertEndChild(Scaley);

		//z
		Scale->InsertFirstChild(ScaleZ);
		ScaleZ->SetText(sceneToSave.m_fGridSize);
		Scale->InsertEndChild(ScaleZ);


		Transformable->InsertEndChild(Scale);

		//Rotation
		XMLElement * Rotation = xmlDoc.NewElement("Rotation");
		Transformable->InsertFirstChild(Rotation);
		XMLElement * RotationX = xmlDoc.NewElement("X");
		XMLElement * Rotationy = xmlDoc.NewElement("Y");
		XMLElement * RotationZ = xmlDoc.NewElement("Z");

		//x
		Rotation->InsertFirstChild(RotationX);
		RotationX->SetText(0);
		Rotation->InsertEndChild(RotationX);

		//y
		Rotation->InsertFirstChild(Rotationy);
		Rotationy->SetText(0);
		Rotation->InsertEndChild(Rotationy);

		//z
		Rotation->InsertFirstChild(RotationZ);
		RotationZ->SetText(0);
		Rotation->InsertEndChild(RotationZ);


		Transformable->InsertEndChild(Rotation);

		//Origin
		XMLElement * Origin = xmlDoc.NewElement("Origin");
		Transformable->InsertFirstChild(Origin);
		XMLElement * OriginX = xmlDoc.NewElement("X");
		XMLElement * Originy = xmlDoc.NewElement("Y");
		XMLElement * OriginZ = xmlDoc.NewElement("Z");

		//x
		Origin->InsertFirstChild(OriginX);
		OriginX->SetText(0);
		Origin->InsertEndChild(OriginX);

		//y
		Origin->InsertFirstChild(Originy);
		Originy->SetText(0);
		Origin->InsertEndChild(Originy);

		//z
		Origin->InsertFirstChild(OriginZ);
		OriginZ->SetText(0);
		Origin->InsertEndChild(OriginZ);


		Transformable->InsertEndChild(Origin);


		Entity->InsertEndChild(Transformable);


		//Physical
		XMLElement * Physical = xmlDoc.NewElement("Physical");
		Entity->InsertFirstChild(Physical);

		//Mass
		XMLElement * Mass = xmlDoc.NewElement("Mass");
		Physical->InsertFirstChild(Mass);
		Mass->SetText(0.0f);
		Physical->InsertEndChild(Mass);

		//Restitution
		XMLElement * Restitution = xmlDoc.NewElement("Restitution");
		Physical->InsertFirstChild(Restitution);
		Restitution->SetText(0.1f);
		Physical->InsertEndChild(Restitution);

		Entity->InsertEndChild(Physical);

		//Model
		XMLElement * Model = xmlDoc.NewElement("Model");
		Entity->InsertFirstChild(Model);

		//mesh

		XMLElement * Mesh = xmlDoc.NewElement("Mesh");
		Model->InsertFirstChild(Mesh);
		Mesh->SetText("plane_mesh");
		Model->InsertEndChild(Mesh);

		//Material
		XMLElement * Material = xmlDoc.NewElement("Material");
		Model->InsertFirstChild(Material);
		Material->SetText("default_material");
		Model->InsertEndChild(Material);

		//Shader
		XMLElement * Shader = xmlDoc.NewElement("Shader");
		Model->InsertFirstChild(Shader);
		Shader->SetText("phong_shader");
		Model->InsertEndChild(Shader);

		//texture
		XMLElement * Texture = xmlDoc.NewElement("Texture");
		Model->InsertFirstChild(Texture);
		if (iFloor == 1)Texture->SetText("floor_texture");
		if (iFloor == 2)Texture->SetText("floor_grass_texture");
		if (iFloor == 3)Texture->SetText("floor_blue_texture");
		if (iFloor == 4)Texture->SetText("floor_brown_texture");
		if (iFloor == 5)Texture->SetText("floor_green_texture");
		Model->InsertEndChild(Texture);
		Entity->InsertEndChild(Model);



		pScene->InsertEndChild(Entity);
		
	}

	//create the skybox
	for (int i = 0; i < 1; i++)
	{

		//Entity
		XMLElement * Entity = xmlDoc.NewElement("Entity");
		pScene->InsertFirstChild(Entity);

		//ID
		XMLElement * ID = xmlDoc.NewElement("Name");
		Entity->InsertFirstChild(ID);
		ID->SetText("skybox");
		Entity->InsertEndChild(ID);


		//Transformable
		XMLElement * Transformable = xmlDoc.NewElement("Transformable");
		Entity->InsertFirstChild(Transformable);

		//Position
		XMLElement * Position = xmlDoc.NewElement("Position");
		Transformable->InsertFirstChild(Position);
		XMLElement * posx = xmlDoc.NewElement("X");
		XMLElement * posy = xmlDoc.NewElement("Y");
		XMLElement * posz = xmlDoc.NewElement("Z");

		//x
		Position->InsertFirstChild(posx);
		posx->SetText(0.0f);
		Position->InsertEndChild(posx);

		//y
		Position->InsertFirstChild(posy);
		posy->SetText(0.0f);
		Position->InsertEndChild(posy);

		//z
		Position->InsertFirstChild(posz);
		posz->SetText(0.0f);
		Position->InsertEndChild(posz);


		Transformable->InsertEndChild(Position);

		//Scale
		XMLElement * Scale = xmlDoc.NewElement("Scale");
		Transformable->InsertFirstChild(Scale);
		XMLElement * ScaleX = xmlDoc.NewElement("X");
		XMLElement * ScaleY = xmlDoc.NewElement("Y");
		XMLElement * ScaleZ = xmlDoc.NewElement("Z");

		//x
		Scale->InsertFirstChild(ScaleX);
		ScaleX->SetText(sceneToSave.m_fGridSize * sceneToSave.m_fXDimensions);
		Scale->InsertEndChild(ScaleX);

		//y
		Scale->InsertFirstChild(ScaleY);
		ScaleY->SetText(sceneToSave.m_fGridSize * max(sceneToSave.m_fYDimensions, sceneToSave.m_fXDimensions));
		Scale->InsertEndChild(ScaleY);

		//z
		Scale->InsertFirstChild(ScaleZ);
		ScaleZ->SetText(sceneToSave.m_fGridSize * sceneToSave.m_fYDimensions);
		Scale->InsertEndChild(ScaleZ);


		Transformable->InsertEndChild(Scale);

		//Rotation
		XMLElement * Rotation = xmlDoc.NewElement("Rotation");
		Transformable->InsertFirstChild(Rotation);
		XMLElement * RotX = xmlDoc.NewElement("X");
		XMLElement * RotY = xmlDoc.NewElement("Y");
		XMLElement * RotZ = xmlDoc.NewElement("Z");

		//x
		Rotation->InsertFirstChild(RotX);
		RotX->SetText(0.0f);
		Rotation->InsertEndChild(RotX);

		//y
		Rotation->InsertFirstChild(RotY);
		RotY->SetText(0.0f);
		Rotation->InsertEndChild(RotY);

		//z
		Rotation->InsertFirstChild(RotZ);
		RotZ->SetText(0.0f);
		Rotation->InsertEndChild(RotZ);
		Transformable->InsertEndChild(Rotation);

		Entity->InsertEndChild(Transformable);

		//Model
		XMLElement * Model = xmlDoc.NewElement("Model");
		Entity->InsertFirstChild(Model);



		//mesh
		XMLElement * Mesh = xmlDoc.NewElement("Mesh");
		Model->InsertFirstChild(Mesh);
		if (iSkybox == 1)Mesh->SetText("skybox_water_mesh");
		if (iSkybox == 2)Mesh->SetText("skybox_sunny_mesh");
		Model->InsertEndChild(Mesh);

		//Material
		XMLElement * Material = xmlDoc.NewElement("Material");
		Model->InsertFirstChild(Material);
		Material->SetText("default_material");
		Model->InsertEndChild(Material);

		//Shader
		XMLElement * Shader = xmlDoc.NewElement("Shader");
		Model->InsertFirstChild(Shader);
		Shader->SetText("phong_shader");
		Model->InsertEndChild(Shader);

		//texture
		XMLElement * Texture = xmlDoc.NewElement("Texture");
		Model->InsertFirstChild(Texture);
		if (iSkybox == 1)Texture->SetText("skybox_water_texture");
		if (iSkybox == 2)Texture->SetText("skybox_sunny_texture");


		Entity->InsertEndChild(Model);

		pScene->InsertEndChild(Entity);
	}

	//create the pickups
	for (int i = 0; i < sceneToSave.m_vPickupSprites.size(); i++)
	{
		//Entity
		XMLElement * Entity = xmlDoc.NewElement("Entity");
		pScene->InsertFirstChild(Entity);

		//ID
		XMLElement * ID = xmlDoc.NewElement("Name");
		Entity->InsertFirstChild(ID);
		ID->SetText("pickup");
		Entity->InsertEndChild(ID);

		//Transformable
		XMLElement * Transformable = xmlDoc.NewElement("Transformable");
		Entity->InsertFirstChild(Transformable);

		//Position
		XMLElement * Position = xmlDoc.NewElement("Position");
		Transformable->InsertFirstChild(Position);
		XMLElement * posx = xmlDoc.NewElement("X");
		XMLElement * posy = xmlDoc.NewElement("Y");
		XMLElement * posz = xmlDoc.NewElement("Z");

		//x
		Position->InsertFirstChild(posx);
		posx->SetText(sceneToSave.m_vPickupSprites[i].getPosition().x);
		Position->InsertEndChild(posx);

		//y
		Position->InsertFirstChild(posy);
		posy->SetText(600.0f);
		Position->InsertEndChild(posy);

		//z
		Position->InsertFirstChild(posz);
		posz->SetText(sceneToSave.m_vPickupSprites[i].getPosition().y);
		Position->InsertEndChild(posz);


		Transformable->InsertEndChild(Position);

		//Scale
		XMLElement * Scale = xmlDoc.NewElement("Scale");
		Transformable->InsertFirstChild(Scale);
		XMLElement * ScaleX = xmlDoc.NewElement("X");
		XMLElement * ScaleY = xmlDoc.NewElement("Y");
		XMLElement * ScaleZ = xmlDoc.NewElement("Z");

		//x
		Scale->InsertFirstChild(ScaleX);
		ScaleX->SetText(1.0f);
		Scale->InsertEndChild(ScaleX);

		//y
		Scale->InsertFirstChild(ScaleY);
		ScaleY->SetText(1.0f);
		Scale->InsertEndChild(ScaleY);

		//z
		Scale->InsertFirstChild(ScaleZ);
		ScaleY->SetText(1.0f);
		Scale->InsertEndChild(ScaleZ);


		Transformable->InsertEndChild(Scale);

		//Rotation
		XMLElement * Rotation = xmlDoc.NewElement("Rotation");
		Transformable->InsertFirstChild(Rotation);
		XMLElement * RotX = xmlDoc.NewElement("X");
		XMLElement * RotY = xmlDoc.NewElement("Y");
		XMLElement * RotZ = xmlDoc.NewElement("Z");

		//x
		Rotation->InsertFirstChild(RotX);
		RotX->SetText(0.0f);
		Rotation->InsertEndChild(RotX);

		//y
		Rotation->InsertFirstChild(RotY);
		RotY->SetText(0.0f);
		Rotation->InsertEndChild(RotY);

		//z
		Rotation->InsertFirstChild(RotZ);
		RotZ->SetText(0.0f);
		Rotation->InsertEndChild(RotZ);
		Transformable->InsertEndChild(Rotation);

		Entity->InsertEndChild(Transformable);

		//Model
		XMLElement * Model = xmlDoc.NewElement("Model");
		Entity->InsertFirstChild(Model);

		//mesh
		XMLElement * Mesh = xmlDoc.NewElement("Mesh");
		Model->InsertFirstChild(Mesh);
		Mesh->SetText("beeHive_mesh");
		Model->InsertEndChild(Mesh);

		//Material
		XMLElement * Material = xmlDoc.NewElement("Material");
		Model->InsertFirstChild(Material);
		Material->SetText("default_material");
		Model->InsertEndChild(Material);

		//Shader
		XMLElement * Shader = xmlDoc.NewElement("Shader");
		Model->InsertFirstChild(Shader);
		Shader->SetText("phong_shader");
		Model->InsertEndChild(Shader);

		//texture
		XMLElement * Texture = xmlDoc.NewElement("Texture");
		Model->InsertFirstChild(Texture);
		Texture->SetText("beeHive_texture");

		Entity->InsertEndChild(Model);

		//AABB
		for (int i = 0; i < 1; i++)
		{
			XMLElement * AABB = xmlDoc.NewElement("AABB");
			Entity->InsertFirstChild(AABB);
			//Position
			XMLElement * Position = xmlDoc.NewElement("Position");
			AABB->InsertFirstChild(Position);

			XMLElement * posx = xmlDoc.NewElement("X");
			XMLElement * posy = xmlDoc.NewElement("Y");
			XMLElement * posz = xmlDoc.NewElement("Z");

			//x
			Position->InsertFirstChild(posx);
			posx->SetText(sceneToSave.m_vPickupSprites[i].getPosition().x);
			Position->InsertEndChild(posx);

			//y
			Position->InsertFirstChild(posy);
			posy->SetText(600.0f);
			Position->InsertEndChild(posy);

			//z
			Position->InsertFirstChild(posz);
			posz->SetText(sceneToSave.m_vPickupSprites[i].getPosition().y);
			Position->InsertEndChild(posz);


			AABB->InsertEndChild(Position);

			//Scale
			XMLElement * Scale = xmlDoc.NewElement("Scale");
			AABB->InsertFirstChild(Scale);
			XMLElement * ScaleX = xmlDoc.NewElement("X");
			XMLElement * Scaley = xmlDoc.NewElement("Y");
			XMLElement * ScaleZ = xmlDoc.NewElement("Z");

			//x
			Scale->InsertFirstChild(ScaleX);
			ScaleX->SetText(1.0f);
			Scale->InsertEndChild(ScaleX);

			//y
			Scale->InsertFirstChild(Scaley);
			Scaley->SetText(1.0f);
			Scale->InsertEndChild(Scaley);

			//z
			Scale->InsertFirstChild(ScaleZ);
			ScaleZ->SetText(1.0f);
			Scale->InsertEndChild(ScaleZ);


			AABB->InsertEndChild(Scale);

			//Origin
			XMLElement * Origin = xmlDoc.NewElement("Origin");
			AABB->InsertFirstChild(Origin);
			XMLElement * OriginX = xmlDoc.NewElement("X");
			XMLElement * Originy = xmlDoc.NewElement("Y");
			XMLElement * OriginZ = xmlDoc.NewElement("Z");

			//x
			Origin->InsertFirstChild(OriginX);
			OriginX->SetText(0);
			Origin->InsertEndChild(OriginX);

			//y
			Origin->InsertFirstChild(Originy);
			Originy->SetText(0);
			Origin->InsertEndChild(Originy);

			//z
			Origin->InsertFirstChild(OriginZ);
			OriginZ->SetText(0);
			Origin->InsertEndChild(OriginZ);


			AABB->InsertEndChild(Origin);
			Entity->InsertEndChild(AABB);
		}

	}

	//create the world light
	XMLElement * Light = xmlDoc.NewElement("Light");
	pScene->InsertFirstChild(Light);
	for (int i = 0; i < 1; i++)
	{

		//ID
		XMLElement * ID = xmlDoc.NewElement("ID");
		Light->InsertFirstChild(ID);
		ID->SetText("light1");
		Light->InsertEndChild(ID);

		//Type
		XMLElement * Type = xmlDoc.NewElement("Type");
		Light->InsertFirstChild(Type);
		Type->SetText("Directional");
		Light->InsertEndChild(Type);


		//Direction
		XMLElement * Direction = xmlDoc.NewElement("Direction");
		Light->InsertFirstChild(Direction);

		XMLElement * dirx = xmlDoc.NewElement("X");
		XMLElement * diry = xmlDoc.NewElement("Y");
		XMLElement * dirz = xmlDoc.NewElement("Z");

		//x
		Direction->InsertFirstChild(dirx);
		dirx->SetText(0.5f);
		Direction->InsertEndChild(dirx);

		//y
		Direction->InsertFirstChild(diry);
		diry->SetText(-0.5f);
		Direction->InsertEndChild(diry);

		//z
		Direction->InsertFirstChild(dirz);
		dirz->SetText(0.5f);
		Direction->InsertEndChild(dirz);

		Light->InsertEndChild(Direction);

		//Ambient
		XMLElement * Ambient = xmlDoc.NewElement("Ambient");
		Light->InsertFirstChild(Ambient);

		XMLElement * ambx = xmlDoc.NewElement("X");
		XMLElement * amby = xmlDoc.NewElement("Y");
		XMLElement * ambz = xmlDoc.NewElement("Z");

		//x
		Ambient->InsertFirstChild(ambx);
		ambx->SetText(0.4f);
		Ambient->InsertEndChild(ambx);

		//y
		Ambient->InsertFirstChild(amby);
		amby->SetText(0.4f);
		Ambient->InsertEndChild(amby);

		//z
		Ambient->InsertFirstChild(ambz);
		ambz->SetText(0.4f);
		Ambient->InsertEndChild(ambz);

		Light->InsertEndChild(Ambient);

		//Diffuse
		XMLElement * Diffuse = xmlDoc.NewElement("Diffuse");
		Light->InsertFirstChild(Diffuse);

		XMLElement * diffx = xmlDoc.NewElement("X");
		XMLElement * diffy = xmlDoc.NewElement("Y");
		XMLElement * diffz = xmlDoc.NewElement("Z");

		//x
		Diffuse->InsertFirstChild(diffx);
		diffx->SetText(0.4f);
		Diffuse->InsertEndChild(diffx);

		//y
		Diffuse->InsertFirstChild(diffy);
		diffy->SetText(0.4f);
		Diffuse->InsertEndChild(diffy);

		//z
		Diffuse->InsertFirstChild(diffz);
		diffz->SetText(0.4f);
		Diffuse->InsertEndChild(diffz);

		Light->InsertEndChild(Diffuse);

		//Specular
		XMLElement * Specular = xmlDoc.NewElement("Specular");
		Light->InsertFirstChild(Specular);

		XMLElement * specx = xmlDoc.NewElement("X");
		XMLElement * specy = xmlDoc.NewElement("Y");
		XMLElement * specz = xmlDoc.NewElement("Z");

		//x
		Specular->InsertFirstChild(specx);
		specx->SetText(0.5f);
		Specular->InsertEndChild(specx);

		//y
		Specular->InsertFirstChild(specy);
		specy->SetText(0.5f);
		Specular->InsertEndChild(specy);

		//z
		Specular->InsertFirstChild(specz);
		specz->SetText(0.5f);
		Specular->InsertEndChild(specz);

		Light->InsertEndChild(Specular);


	}

	pScene->InsertEndChild(Light);

	//create obsticles
	for (int i = 0; i < sceneToSave.m_vObsticleSprites.size(); i++)
	{
		//Entity
		XMLElement * Entity = xmlDoc.NewElement("Entity");
		pScene->InsertFirstChild(Entity);

		//ID
		XMLElement * ID = xmlDoc.NewElement("Name");
		Entity->InsertFirstChild(ID);
		ID->SetText("Obsticle");
		Entity->InsertEndChild(ID);

		//Transformable
		XMLElement * Transformable = xmlDoc.NewElement("Transformable");
		Entity->InsertFirstChild(Transformable);

		//Position
		XMLElement * Position = xmlDoc.NewElement("Position");
		Transformable->InsertFirstChild(Position);

		XMLElement * posx = xmlDoc.NewElement("X");
		XMLElement * posy = xmlDoc.NewElement("Y");
		XMLElement * posz = xmlDoc.NewElement("Z");

		//x
		Position->InsertFirstChild(posx);
		posx->SetText(sceneToSave.m_vObsticleSprites[i].getPosition().x);
		Position->InsertEndChild(posx);

		//y
		Position->InsertFirstChild(posy);
		posy->SetText(500.0f);
		Position->InsertEndChild(posy);

		//z
		Position->InsertFirstChild(posz);
		posz->SetText(sceneToSave.m_vObsticleSprites[i].getPosition().y);
		Position->InsertEndChild(posz);


		Transformable->InsertEndChild(Position);

		//Scale
		XMLElement * Scale = xmlDoc.NewElement("Scale");
		Transformable->InsertFirstChild(Scale);
		XMLElement * ScaleX = xmlDoc.NewElement("X");
		XMLElement * Scaley = xmlDoc.NewElement("Y");
		XMLElement * ScaleZ = xmlDoc.NewElement("Z");

		//x
		Scale->InsertFirstChild(ScaleX);
		ScaleX->SetText(100.0f);
		Scale->InsertEndChild(ScaleX);

		//y
		Scale->InsertFirstChild(Scaley);
		Scaley->SetText(100.0f);
		Scale->InsertEndChild(Scaley);

		//z
		Scale->InsertFirstChild(ScaleZ);
		ScaleZ->SetText(100.0f);
		Scale->InsertEndChild(ScaleZ);


		Transformable->InsertEndChild(Scale);

		//Rotation
		XMLElement * Rotation = xmlDoc.NewElement("Rotation");
		Transformable->InsertFirstChild(Rotation);
		XMLElement * RotationX = xmlDoc.NewElement("X");
		XMLElement * Rotationy = xmlDoc.NewElement("Y");
		XMLElement * RotationZ = xmlDoc.NewElement("Z");

		//x
		Rotation->InsertFirstChild(RotationX);
		RotationX->SetText(0);
		Rotation->InsertEndChild(RotationX);

		//y
		Rotation->InsertFirstChild(Rotationy);
		Rotationy->SetText(0);
		Rotation->InsertEndChild(Rotationy);

		//z
		Rotation->InsertFirstChild(RotationZ);
		RotationZ->SetText(0);
		Rotation->InsertEndChild(RotationZ);


		Transformable->InsertEndChild(Rotation);

		//Origin
		XMLElement * Origin = xmlDoc.NewElement("Origin");
		Transformable->InsertFirstChild(Origin);
		XMLElement * OriginX = xmlDoc.NewElement("X");
		XMLElement * Originy = xmlDoc.NewElement("Y");
		XMLElement * OriginZ = xmlDoc.NewElement("Z");

		//x
		Origin->InsertFirstChild(OriginX);
		OriginX->SetText(0);
		Origin->InsertEndChild(OriginX);

		//y
		Origin->InsertFirstChild(Originy);
		Originy->SetText(0);
		Origin->InsertEndChild(Originy);

		//z
		Origin->InsertFirstChild(OriginZ);
		OriginZ->SetText(0);
		Origin->InsertEndChild(OriginZ);


		Transformable->InsertEndChild(Origin);


		Entity->InsertEndChild(Transformable);


		//Physical
		XMLElement * Physical = xmlDoc.NewElement("Physical");
		Entity->InsertFirstChild(Physical);

		//Mass
		XMLElement * Mass = xmlDoc.NewElement("Mass");
		Physical->InsertFirstChild(Mass);
		Mass->SetText(0.0f);
		Physical->InsertEndChild(Mass);

		//Restitution
		XMLElement * Restitution = xmlDoc.NewElement("Restitution");
		Physical->InsertFirstChild(Restitution);
		Restitution->SetText(0.1f);
		Physical->InsertEndChild(Restitution);

		Entity->InsertEndChild(Physical);

		//Model
		XMLElement * Model = xmlDoc.NewElement("Model");
		Entity->InsertFirstChild(Model);

		//mesh

		XMLElement * Mesh = xmlDoc.NewElement("Mesh");
		Model->InsertFirstChild(Mesh);
		Mesh->SetText("cube_mesh");
		Model->InsertEndChild(Mesh);

		//Material
		XMLElement * Material = xmlDoc.NewElement("Material");
		Model->InsertFirstChild(Material);
		Material->SetText("default_material");
		Model->InsertEndChild(Material);

		//Shader
		XMLElement * Shader = xmlDoc.NewElement("Shader");
		Model->InsertFirstChild(Shader);
		Shader->SetText("phong_shader");
		Model->InsertEndChild(Shader);

		//texture
		XMLElement * Texture = xmlDoc.NewElement("Texture");
		Model->InsertFirstChild(Texture);
		if (iFloor == 1)Texture->SetText("floor_texture");
		if (iFloor == 2)Texture->SetText("floor_grass_texture");
		if (iFloor == 3)Texture->SetText("floor_blue_texture");
		if (iFloor == 4)Texture->SetText("floor_brown_texture");
		if (iFloor == 5)Texture->SetText("floor_green_texture");
		Model->InsertEndChild(Texture);
		Entity->InsertEndChild(Model);

		//AABB
		for (int i = 0; i < 1; i++)
		{
			XMLElement * AABB = xmlDoc.NewElement("AABB");
			Entity->InsertFirstChild(AABB);
			//Position
			XMLElement * Position = xmlDoc.NewElement("Position");
			AABB->InsertFirstChild(Position);

			XMLElement * posx = xmlDoc.NewElement("X");
			XMLElement * posy = xmlDoc.NewElement("Y");
			XMLElement * posz = xmlDoc.NewElement("Z");

			//x
			Position->InsertFirstChild(posx);
			posx->SetText(sceneToSave.m_vObsticleSprites[i].getPosition().x);
			Position->InsertEndChild(posx);

			//y
			Position->InsertFirstChild(posy);
			posy->SetText(600.0f);
			Position->InsertEndChild(posy);

			//z
			Position->InsertFirstChild(posz);
			posz->SetText(sceneToSave.m_vObsticleSprites[i].getPosition().y);
			Position->InsertEndChild(posz);


			AABB->InsertEndChild(Position);

			//Scale
			XMLElement * Scale = xmlDoc.NewElement("Scale");
			AABB->InsertFirstChild(Scale);
			XMLElement * ScaleX = xmlDoc.NewElement("X");
			XMLElement * Scaley = xmlDoc.NewElement("Y");
			XMLElement * ScaleZ = xmlDoc.NewElement("Z");

			//x
			Scale->InsertFirstChild(ScaleX);
			ScaleX->SetText(1.0f);
			Scale->InsertEndChild(ScaleX);

			//y
			Scale->InsertFirstChild(Scaley);
			Scaley->SetText(1.0f);
			Scale->InsertEndChild(Scaley);

			//z
			Scale->InsertFirstChild(ScaleZ);
			ScaleZ->SetText(1.0f);
			Scale->InsertEndChild(ScaleZ);


			AABB->InsertEndChild(Scale);

			//Origin
			XMLElement * Origin = xmlDoc.NewElement("Origin");
			AABB->InsertFirstChild(Origin);
			XMLElement * OriginX = xmlDoc.NewElement("X");
			XMLElement * Originy = xmlDoc.NewElement("Y");
			XMLElement * OriginZ = xmlDoc.NewElement("Z");

			//x
			Origin->InsertFirstChild(OriginX);
			OriginX->SetText(0);
			Origin->InsertEndChild(OriginX);

			//y
			Origin->InsertFirstChild(Originy);
			Originy->SetText(0);
			Origin->InsertEndChild(Originy);

			//z
			Origin->InsertFirstChild(OriginZ);
			OriginZ->SetText(0);
			Origin->InsertEndChild(OriginZ);


			AABB->InsertEndChild(Origin);
			Entity->InsertEndChild(AABB);
		}

		//OBB
		for (int i = 0; i < 1; i++)
		{
			XMLElement * OBB = xmlDoc.NewElement("OBB");
			Entity->InsertFirstChild(OBB);
			//Position
			XMLElement * Position = xmlDoc.NewElement("Position");
			OBB->InsertFirstChild(Position);

			XMLElement * posx = xmlDoc.NewElement("X");
			XMLElement * posy = xmlDoc.NewElement("Y");
			XMLElement * posz = xmlDoc.NewElement("Z");

			//x
			Position->InsertFirstChild(posx);
			posx->SetText(sceneToSave.m_vObsticleSprites[i].getPosition().x);
			Position->InsertEndChild(posx);

			//y
			Position->InsertFirstChild(posy);
			posy->SetText(600.0f);
			Position->InsertEndChild(posy);

			//z
			Position->InsertFirstChild(posz);
			posz->SetText(sceneToSave.m_vObsticleSprites[i].getPosition().y);
			Position->InsertEndChild(posz);


			OBB->InsertEndChild(Position);

			//Scale
			XMLElement * Scale = xmlDoc.NewElement("Scale");
			OBB->InsertFirstChild(Scale);
			XMLElement * ScaleX = xmlDoc.NewElement("X");
			XMLElement * Scaley = xmlDoc.NewElement("Y");
			XMLElement * ScaleZ = xmlDoc.NewElement("Z");

			//x
			Scale->InsertFirstChild(ScaleX);
			ScaleX->SetText(100.0f);
			Scale->InsertEndChild(ScaleX);

			//y
			Scale->InsertFirstChild(Scaley);
			Scaley->SetText(100.0f);
			Scale->InsertEndChild(Scaley);

			//z
			Scale->InsertFirstChild(ScaleZ);
			ScaleZ->SetText(100.0f);
			Scale->InsertEndChild(ScaleZ);


			OBB->InsertEndChild(Scale);

			//Rotation
			XMLElement * Rotation = xmlDoc.NewElement("Rotation");
			OBB->InsertFirstChild(Rotation);
			XMLElement * RotX = xmlDoc.NewElement("X");
			XMLElement * RotY = xmlDoc.NewElement("Y");
			XMLElement * RotZ = xmlDoc.NewElement("Z");

			//x
			Rotation->InsertFirstChild(RotX);
			RotX->SetText(0.0f);
			Rotation->InsertEndChild(RotX);

			//y
			Rotation->InsertFirstChild(RotY);
			RotY->SetText(0.0f);
			Rotation->InsertEndChild(RotY);

			//z
			Rotation->InsertFirstChild(RotZ);
			RotZ->SetText(0.0f);
			Rotation->InsertEndChild(RotZ);

			Transformable->InsertEndChild(OBB);

			//Origin
			XMLElement * Origin = xmlDoc.NewElement("Origin");
			OBB->InsertFirstChild(Origin);
			XMLElement * OriginX = xmlDoc.NewElement("X");
			XMLElement * Originy = xmlDoc.NewElement("Y");
			XMLElement * OriginZ = xmlDoc.NewElement("Z");

			//x
			Origin->InsertFirstChild(OriginX);
			OriginX->SetText(0);
			Origin->InsertEndChild(OriginX);

			//y
			Origin->InsertFirstChild(Originy);
			Originy->SetText(0);
			Origin->InsertEndChild(Originy);

			//z
			Origin->InsertFirstChild(OriginZ);
			OriginZ->SetText(0);
			Origin->InsertEndChild(OriginZ);


			OBB->InsertEndChild(Origin);
			Entity->InsertEndChild(OBB);
		}

		pScene->InsertEndChild(Entity);
	}


	//create the point lights
	for (int i = 0; i < sceneToSave.m_vLightSprites.size(); i++)
	{
		XMLElement * Light = xmlDoc.NewElement("Light");
		pScene->InsertFirstChild(Light);

		//ID
		XMLElement * ID = xmlDoc.NewElement("ID");
		Light->InsertFirstChild(ID);
		ID->SetText("light");
		Light->InsertEndChild(ID);

		//Type
		XMLElement * Type = xmlDoc.NewElement("Type");
		Light->InsertFirstChild(Type);
		Type->SetText("Point");
		Light->InsertEndChild(Type);


		//Direction
		XMLElement * Position = xmlDoc.NewElement("Position");
		Light->InsertFirstChild(Position);

		XMLElement * dirx = xmlDoc.NewElement("X");
		XMLElement * diry = xmlDoc.NewElement("Y");
		XMLElement * dirz = xmlDoc.NewElement("Z");

		//x
		Position->InsertFirstChild(dirx);
		dirx->SetText(sceneToSave.m_vLightSprites[i].getPosition().x);
		Position->InsertEndChild(dirx);

		//y
		Position->InsertFirstChild(diry);
		diry->SetText(650.0f);
		Position->InsertEndChild(diry);

		//z
		Position->InsertFirstChild(dirz);
		dirz->SetText(sceneToSave.m_vLightSprites[i].getPosition().y);
		Position->InsertEndChild(dirz);

		Light->InsertEndChild(Position);

		//Ambient
		XMLElement * Ambient = xmlDoc.NewElement("Ambient");
		Light->InsertFirstChild(Ambient);

		XMLElement * ambx = xmlDoc.NewElement("X");
		XMLElement * amby = xmlDoc.NewElement("Y");
		XMLElement * ambz = xmlDoc.NewElement("Z");

		//x
		Ambient->InsertFirstChild(ambx);
		ambx->SetText(1.0f);
		Ambient->InsertEndChild(ambx);

		//y
		Ambient->InsertFirstChild(amby);
		amby->SetText(1.0f);
		Ambient->InsertEndChild(amby);

		//z
		Ambient->InsertFirstChild(ambz);
		ambz->SetText(1.0f);
		Ambient->InsertEndChild(ambz);

		Light->InsertEndChild(Ambient);

		//Diffuse
		XMLElement * Diffuse = xmlDoc.NewElement("Diffuse");
		Light->InsertFirstChild(Diffuse);

		XMLElement * diffx = xmlDoc.NewElement("X");
		XMLElement * diffy = xmlDoc.NewElement("Y");
		XMLElement * diffz = xmlDoc.NewElement("Z");

		//x
		Diffuse->InsertFirstChild(diffx);
		diffx->SetText(0.8f);
		Diffuse->InsertEndChild(diffx);

		//y
		Diffuse->InsertFirstChild(diffy);
		diffy->SetText(0.8f);
		Diffuse->InsertEndChild(diffy);

		//z
		Diffuse->InsertFirstChild(diffz);
		diffz->SetText(0.8f);
		Diffuse->InsertEndChild(diffz);

		Light->InsertEndChild(Diffuse);

		//Specular
		XMLElement * Specular = xmlDoc.NewElement("Specular");
		Light->InsertFirstChild(Specular);

		XMLElement * specx = xmlDoc.NewElement("X");
		XMLElement * specy = xmlDoc.NewElement("Y");
		XMLElement * specz = xmlDoc.NewElement("Z");

		//x
		Specular->InsertFirstChild(specx);
		specx->SetText(1.0f);
		Specular->InsertEndChild(specx);

		//y
		Specular->InsertFirstChild(specy);
		specy->SetText(1.0f);
		Specular->InsertEndChild(specy);

		//z
		Specular->InsertFirstChild(specz);
		specz->SetText(1.0f);
		Specular->InsertEndChild(specz);

		Light->InsertEndChild(Specular);

		//Radius
		XMLElement * Radius = xmlDoc.NewElement("Radius");
		Light->InsertFirstChild(Radius);
		Radius->SetText(250.0f);
		Light->InsertEndChild(Radius);

		pScene->InsertEndChild(Light);

	}

	//create the player
	for (int i = 0; i < 1; i++)
	{
		//Entity
		XMLElement * Entity = xmlDoc.NewElement("Entity");
		pScene->InsertFirstChild(Entity);

		//ID
		XMLElement * ID = xmlDoc.NewElement("Name");
		Entity->InsertFirstChild(ID);
		ID->SetText("player");
		Entity->InsertEndChild(ID);

		//Player
		XMLElement * Player = xmlDoc.NewElement("Player");
		Entity->InsertFirstChild(Player);

		XMLElement * MoveSpeed = xmlDoc.NewElement("MoveSpeed");
		Player->InsertFirstChild(MoveSpeed);
		MoveSpeed->SetText(10.0f);
		Player->InsertEndChild(MoveSpeed);

		Entity->InsertEndChild(Player);

		//Transformable
		XMLElement * Transformable = xmlDoc.NewElement("Transformable");
		Entity->InsertFirstChild(Transformable);

		//Position
		XMLElement * Position = xmlDoc.NewElement("Position");
		Transformable->InsertFirstChild(Position);
		XMLElement * posx = xmlDoc.NewElement("X");
		XMLElement * posy = xmlDoc.NewElement("Y");
		XMLElement * posz = xmlDoc.NewElement("Z");

		//x
		Position->InsertFirstChild(posx);
		posx->SetText(sceneToSave.m_Player.getPosition().x);
		Position->InsertEndChild(posx);

		//y
		Position->InsertFirstChild(posy);
		posy->SetText(600.0f);
		Position->InsertEndChild(posy);

		//z
		Position->InsertFirstChild(posz);
		posz->SetText(sceneToSave.m_Player.getPosition().y);
		Position->InsertEndChild(posz);


		Transformable->InsertEndChild(Position);

		//Scale
		XMLElement * Scale = xmlDoc.NewElement("Scale");
		Transformable->InsertFirstChild(Scale);
		XMLElement * ScaleX = xmlDoc.NewElement("X");
		XMLElement * ScaleY = xmlDoc.NewElement("Y");
		XMLElement * ScaleZ = xmlDoc.NewElement("Z");

		//x
		Scale->InsertFirstChild(ScaleX);
		ScaleX->SetText(1.0f);
		Scale->InsertEndChild(ScaleX);

		//y
		Scale->InsertFirstChild(ScaleY);
		ScaleY->SetText(1.0f);
		Scale->InsertEndChild(ScaleY);

		//z
		Scale->InsertFirstChild(ScaleZ);
		ScaleZ->SetText(1.0f);
		Scale->InsertEndChild(ScaleZ);


		Transformable->InsertEndChild(Scale);

		//Rotation
		XMLElement * Rotation = xmlDoc.NewElement("Rotation");
		Transformable->InsertFirstChild(Rotation);
		XMLElement * RotX = xmlDoc.NewElement("X");
		XMLElement * RotY = xmlDoc.NewElement("Y");
		XMLElement * RotZ = xmlDoc.NewElement("Z");

		//x
		Rotation->InsertFirstChild(RotX);
		RotX->SetText(0.0f);
		Rotation->InsertEndChild(RotX);

		//y
		Rotation->InsertFirstChild(RotY);
		RotY->SetText(0.0f);
		Rotation->InsertEndChild(RotY);

		//z
		Rotation->InsertFirstChild(RotZ);
		RotZ->SetText(0.0f);
		Rotation->InsertEndChild(RotZ);
		Transformable->InsertEndChild(Rotation);

		Entity->InsertEndChild(Transformable);

		//Model
		XMLElement * Model = xmlDoc.NewElement("Model");
		Entity->InsertFirstChild(Model);

		//mesh
		XMLElement * Mesh = xmlDoc.NewElement("Mesh");
		Model->InsertFirstChild(Mesh);
		Mesh->SetText("beeModel_mesh");
		Model->InsertEndChild(Mesh);

		//Material
		XMLElement * Material = xmlDoc.NewElement("Material");
		Model->InsertFirstChild(Material);
		Material->SetText("default_material");
		Model->InsertEndChild(Material);

		//Shader
		XMLElement * Shader = xmlDoc.NewElement("Shader");
		Model->InsertFirstChild(Shader);
		Shader->SetText("phong_shader");
		Model->InsertEndChild(Shader);

		//texture
		XMLElement * Texture = xmlDoc.NewElement("Texture");
		Model->InsertFirstChild(Texture);
		Texture->SetText("beeModel_texture");

		Entity->InsertEndChild(Model);

		//Physical
		XMLElement * Physical = xmlDoc.NewElement("Physical");
		Entity->InsertFirstChild(Physical);

		//Mass
		XMLElement * Mass = xmlDoc.NewElement("Mass");
		Physical->InsertFirstChild(Mass);
		Mass->SetText(55.0f);
		Physical->InsertEndChild(Mass);

		//Restitution
		XMLElement * Restitution = xmlDoc.NewElement("Restitution");
		Physical->InsertFirstChild(Restitution);
		Restitution->SetText(0.2f);
		Physical->InsertEndChild(Restitution);

		Entity->InsertEndChild(Physical);

		//AABB
		for (int i = 0; i < 1; i++)
	{
		XMLElement * AABB = xmlDoc.NewElement("AABB");
		Entity->InsertFirstChild(AABB);
		//Position
		XMLElement * Position = xmlDoc.NewElement("Position");
		AABB->InsertFirstChild(Position);

		XMLElement * posx = xmlDoc.NewElement("X");
		XMLElement * posy = xmlDoc.NewElement("Y");
		XMLElement * posz = xmlDoc.NewElement("Z");

		//x
		Position->InsertFirstChild(posx);
		posx->SetText(sceneToSave.m_Player.getPosition().x);
		Position->InsertEndChild(posx);

		//y
		Position->InsertFirstChild(posy);
		posy->SetText(600.0f);
		Position->InsertEndChild(posy);

		//z
		Position->InsertFirstChild(posz);
		posz->SetText(sceneToSave.m_Player.getPosition().y);
		Position->InsertEndChild(posz);


		AABB->InsertEndChild(Position);

		//Scale
		XMLElement * Scale = xmlDoc.NewElement("Scale");
		AABB->InsertFirstChild(Scale);
		XMLElement * ScaleX = xmlDoc.NewElement("X");
		XMLElement * Scaley = xmlDoc.NewElement("Y");
		XMLElement * ScaleZ = xmlDoc.NewElement("Z");

		//x
		Scale->InsertFirstChild(ScaleX);
		ScaleX->SetText(1.0f);
		Scale->InsertEndChild(ScaleX);

		//y
		Scale->InsertFirstChild(Scaley);
		Scaley->SetText(1.0f);
		Scale->InsertEndChild(Scaley);

		//z
		Scale->InsertFirstChild(ScaleZ);
		ScaleZ->SetText(1.0f);
		Scale->InsertEndChild(ScaleZ);


		AABB->InsertEndChild(Scale);

		//Origin
		XMLElement * Origin = xmlDoc.NewElement("Origin");
		AABB->InsertFirstChild(Origin);
		XMLElement * OriginX = xmlDoc.NewElement("X");
		XMLElement * Originy = xmlDoc.NewElement("Y");
		XMLElement * OriginZ = xmlDoc.NewElement("Z");

		//x
		Origin->InsertFirstChild(OriginX);
		OriginX->SetText(0);
		Origin->InsertEndChild(OriginX);

		//y
		Origin->InsertFirstChild(Originy);
		Originy->SetText(0);
		Origin->InsertEndChild(Originy);

		//z
		Origin->InsertFirstChild(OriginZ);
		OriginZ->SetText(0);
		Origin->InsertEndChild(OriginZ);


		AABB->InsertEndChild(Origin);
		Entity->InsertEndChild(AABB);
	}
		//sphere
		for (int i = 0; i < 1; i++)
		{
			XMLElement * Sphere = xmlDoc.NewElement("Sphere");
			Entity->InsertFirstChild(Sphere);

			XMLElement * Center = xmlDoc.NewElement("Center");
			Sphere->InsertFirstChild(Center);
			//Position

			XMLElement * posx = xmlDoc.NewElement("X");
			XMLElement * posy = xmlDoc.NewElement("Y");
			XMLElement * posz = xmlDoc.NewElement("Z");

			//x
			Center->InsertFirstChild(posx);
			posx->SetText(sceneToSave.m_Player.getPosition().x + 12.5);
			Center->InsertEndChild(posx);

			//y
			Center->InsertFirstChild(posy);
			posy->SetText(612.5f);
			Center->InsertEndChild(posy);

			//z
			Center->InsertFirstChild(posz);
			posz->SetText(sceneToSave.m_Player.getPosition().y + 12.5);
			Center->InsertEndChild(posz);

			Entity->InsertEndChild(Center);

			XMLElement * Radius = xmlDoc.NewElement("Radius");
			Sphere->InsertFirstChild(Radius);
			Radius->SetText(25.0f);
			Entity->InsertEndChild(Radius);
			
			Entity->InsertEndChild(Sphere);
		}
		//camera
		for (int i = 0; i < 1; i++)
		{
			//Create the camera
			XMLElement * Camera = xmlDoc.NewElement("Camera");
			Entity->InsertFirstChild(Camera);

			//Orientation
			XMLElement * Orientation = xmlDoc.NewElement("Orientation");
			Camera->InsertFirstChild(Orientation);
			XMLElement * orx = xmlDoc.NewElement("X");
			XMLElement * ory = xmlDoc.NewElement("Y");
			XMLElement * orz = xmlDoc.NewElement("Z");

			//x
			Orientation->InsertFirstChild(orx);
			orx->SetText(0);
			Orientation->InsertEndChild(orx);

			//y
			Orientation->InsertFirstChild(ory);
			ory->SetText(45.0f);
			Orientation->InsertEndChild(ory);

			//z
			Orientation->InsertFirstChild(orz);
			orz->SetText(0);
			Orientation->InsertEndChild(orz);


			Camera->InsertEndChild(Orientation);

			//FOV
			XMLElement * FOV = xmlDoc.NewElement("FOV");
			Camera->InsertFirstChild(FOV);
			FOV->SetText(70.0f);
			Camera->InsertEndChild(FOV);

			//AspectRatio
			XMLElement * AspectRatio = xmlDoc.NewElement("AspectRatio");
			Camera->InsertFirstChild(AspectRatio);
			AspectRatio->SetText(1.3333f);
			Camera->InsertEndChild(AspectRatio);

			//FarPlane
			XMLElement * FarPlane = xmlDoc.NewElement("FarPlane");
			Camera->InsertFirstChild(FarPlane);
			FarPlane->SetText(10000000.0f);
			Camera->InsertEndChild(FarPlane);

			//NearPlane
			XMLElement * NearPlane = xmlDoc.NewElement("NearPlane");
			Camera->InsertFirstChild(NearPlane);
			NearPlane->SetText(0.1f);
			Camera->InsertEndChild(NearPlane);

			//RotSpeed
			XMLElement * RotSpeed = xmlDoc.NewElement("RotSpeed");
			Camera->InsertFirstChild(RotSpeed);
			RotSpeed->SetText(0.5f);
			Camera->InsertEndChild(RotSpeed);

			//MoveSpeed
			XMLElement * MoveSpeed = xmlDoc.NewElement("MoveSpeed");
			Camera->InsertFirstChild(MoveSpeed);
			MoveSpeed->SetText(0.8f);
			Camera->InsertEndChild(MoveSpeed);

			Entity->InsertEndChild(Camera);

		}

		pScene->InsertEndChild(Entity);

	}


	//create the end point
	for (int i = 0; i < 1; i++)
	{
		//Entity
		XMLElement * Entity = xmlDoc.NewElement("Entity");
		pScene->InsertFirstChild(Entity);

		//ID
		XMLElement * ID = xmlDoc.NewElement("Name");
		Entity->InsertFirstChild(ID);
		ID->SetText("Goal");
		Entity->InsertEndChild(ID);

		//Transformable
		XMLElement * Transformable = xmlDoc.NewElement("Transformable");
		Entity->InsertFirstChild(Transformable);

		//Position
		XMLElement * Position = xmlDoc.NewElement("Position");
		Transformable->InsertFirstChild(Position);
		XMLElement * posx = xmlDoc.NewElement("X");
		XMLElement * posy = xmlDoc.NewElement("Y");
		XMLElement * posz = xmlDoc.NewElement("Z");

		//x
		Position->InsertFirstChild(posx);
		posx->SetText(sceneToSave.m_Goal.getPosition().x);
		Position->InsertEndChild(posx);

		//y
		Position->InsertFirstChild(posy);
		posy->SetText(600.0f);
		Position->InsertEndChild(posy);

		//z
		Position->InsertFirstChild(posz);
		posz->SetText(sceneToSave.m_Goal.getPosition().y);
		Position->InsertEndChild(posz);


		Transformable->InsertEndChild(Position);

		//Scale
		XMLElement * Scale = xmlDoc.NewElement("Scale");
		Transformable->InsertFirstChild(Scale);
		XMLElement * ScaleX = xmlDoc.NewElement("X");
		XMLElement * ScaleY = xmlDoc.NewElement("Y");
		XMLElement * ScaleZ = xmlDoc.NewElement("Z");

		//x
		Scale->InsertFirstChild(ScaleX);
		ScaleX->SetText(1.0f);
		Scale->InsertEndChild(ScaleX);

		//y
		Scale->InsertFirstChild(ScaleY);
		ScaleY->SetText(1.0f);
		Scale->InsertEndChild(ScaleY);

		//z
		Scale->InsertFirstChild(ScaleZ);
		ScaleY->SetText(1.0f);
		Scale->InsertEndChild(ScaleZ);


		Transformable->InsertEndChild(Scale);

		//Rotation
		XMLElement * Rotation = xmlDoc.NewElement("Rotation");
		Transformable->InsertFirstChild(Rotation);
		XMLElement * RotX = xmlDoc.NewElement("X");
		XMLElement * RotY = xmlDoc.NewElement("Y");
		XMLElement * RotZ = xmlDoc.NewElement("Z");

		//x
		Rotation->InsertFirstChild(RotX);
		RotX->SetText(0.0f);
		Rotation->InsertEndChild(RotX);

		//y
		Rotation->InsertFirstChild(RotY);
		RotY->SetText(0.0f);
		Rotation->InsertEndChild(RotY);

		//z
		Rotation->InsertFirstChild(RotZ);
		RotZ->SetText(0.0f);
		Rotation->InsertEndChild(RotZ);
		Transformable->InsertEndChild(Rotation);

		Entity->InsertEndChild(Transformable);

		//Model
		XMLElement * Model = xmlDoc.NewElement("Model");
		Entity->InsertFirstChild(Model);

		//mesh
		XMLElement * Mesh = xmlDoc.NewElement("Mesh");
		Model->InsertFirstChild(Mesh);
		Mesh->SetText("beeHive_mesh");
		Model->InsertEndChild(Mesh);

		//Material
		XMLElement * Material = xmlDoc.NewElement("Material");
		Model->InsertFirstChild(Material);
		Material->SetText("default_material");
		Model->InsertEndChild(Material);

		//Shader
		XMLElement * Shader = xmlDoc.NewElement("Shader");
		Model->InsertFirstChild(Shader);
		Shader->SetText("phong_shader");
		Model->InsertEndChild(Shader);

		//texture
		XMLElement * Texture = xmlDoc.NewElement("Texture");
		Model->InsertFirstChild(Texture);
		Texture->SetText("beeHive_texture");

		Entity->InsertEndChild(Model);

		//AABB
		for (int i = 0; i < 1; i++)
		{
			XMLElement * AABB = xmlDoc.NewElement("AABB");
			Entity->InsertFirstChild(AABB);
			//Position
			XMLElement * Position = xmlDoc.NewElement("Position");
			AABB->InsertFirstChild(Position);

			XMLElement * posx = xmlDoc.NewElement("X");
			XMLElement * posy = xmlDoc.NewElement("Y");
			XMLElement * posz = xmlDoc.NewElement("Z");

			//x
			Position->InsertFirstChild(posx);
			posx->SetText(sceneToSave.m_vPickupSprites[i].getPosition().x);
			Position->InsertEndChild(posx);

			//y
			Position->InsertFirstChild(posy);
			posy->SetText(600.0f);
			Position->InsertEndChild(posy);

			//z
			Position->InsertFirstChild(posz);
			posz->SetText(sceneToSave.m_vPickupSprites[i].getPosition().y);
			Position->InsertEndChild(posz);


			AABB->InsertEndChild(Position);

			//Scale
			XMLElement * Scale = xmlDoc.NewElement("Scale");
			AABB->InsertFirstChild(Scale);
			XMLElement * ScaleX = xmlDoc.NewElement("X");
			XMLElement * Scaley = xmlDoc.NewElement("Y");
			XMLElement * ScaleZ = xmlDoc.NewElement("Z");

			//x
			Scale->InsertFirstChild(ScaleX);
			ScaleX->SetText(1.0f);
			Scale->InsertEndChild(ScaleX);

			//y
			Scale->InsertFirstChild(Scaley);
			Scaley->SetText(1.0f);
			Scale->InsertEndChild(Scaley);

			//z
			Scale->InsertFirstChild(ScaleZ);
			ScaleZ->SetText(1.0f);
			Scale->InsertEndChild(ScaleZ);


			AABB->InsertEndChild(Scale);

			//Origin
			XMLElement * Origin = xmlDoc.NewElement("Origin");
			AABB->InsertFirstChild(Origin);
			XMLElement * OriginX = xmlDoc.NewElement("X");
			XMLElement * Originy = xmlDoc.NewElement("Y");
			XMLElement * OriginZ = xmlDoc.NewElement("Z");

			//x
			Origin->InsertFirstChild(OriginX);
			OriginX->SetText(0);
			Origin->InsertEndChild(OriginX);

			//y
			Origin->InsertFirstChild(Originy);
			Originy->SetText(0);
			Origin->InsertEndChild(Originy);

			//z
			Origin->InsertFirstChild(OriginZ);
			OriginZ->SetText(0);
			Origin->InsertEndChild(OriginZ);


			AABB->InsertEndChild(Origin);
			Entity->InsertEndChild(AABB);
		}
	}

	xmlDoc.InsertEndChild(pScene);

	//save the finished file
	xmlDoc.SaveFile(("../../../Blobsonic/Source/Resources/scenes/" + sLevelName + ".xml").c_str());

}

