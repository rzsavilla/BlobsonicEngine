#include <iostream>
#include <SFML\Graphics.hpp>
#include <tinyxml2.h>
#include "Scene.h"

using namespace std;
using namespace sf;
using namespace tinyxml2;

void OpenLevel(string name); // <! Function that opens the desired level in the editor
void NewLevel();// <! Function that creates the basis of the level
void loadLevel();
void deleteLevel();

int main()
{

	bool bMainValid = true;

	do
	{
		system("cls");
		cout << "Blobsonic - Level Editor" << endl;
		cout << "-" << endl;
		cout << "-" << endl;
		cout << "- Main Menu" << endl;
		cout << "- 1 : New Level" << endl;
		cout << "- 2 : Load Level" << endl;
		cout << "- 3 : Delete Level" << endl;
		cout << "- 4 : Quit" << endl;
		cout << endl << "- : ";

		int iMenuInput;
		cin >> iMenuInput;

		if (iMenuInput != 1 && iMenuInput != 2 && iMenuInput != 3 && iMenuInput != 4) bMainValid = false;
		else
		{
			if (iMenuInput == 1)NewLevel();
			if (iMenuInput == 2)loadLevel();
			if (iMenuInput == 3)deleteLevel();
			if (iMenuInput == 4)bMainValid = true;
		}


	} while (bMainValid == false);

	




	return 0;
}

void OpenLevel(string name)
{
	string path = "../../../Blobsonic/Source/Resources/scenes/" + name + ".xml";

	Scene scene(path);

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



	//window loop
	while (window.isOpen())
	{

		// Event processing
		Event event;
		int iMouseWheel;
		Vector2f sfMousePos;
		Vector2f sfPlacingPos;


		sfPlacingPos = window.mapPixelToCoords(Mouse::getPosition(window), gameView);
		
		if (sf::Event::MouseButtonPressed)
		{
			if (Mouse::isButtonPressed(sf::Mouse::Right))
			{
			}
			if (Mouse::isButtonPressed(sf::Mouse::Left))
			{
			}
		}


		while (window.pollEvent(event))
		{
			// Request for closing the window
			if (event.type == Event::Closed)
			{
				window.close();
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


		//if(Keyboard::Escape == Keyboard)

		window.clear(Color::Black);

		//draw the game 
		window.setView(gameView);

		window.draw(scene);

		//draw the hud
		window.setView(hudView);
		
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
	string sLevelName = "";
	cin >> sLevelName;


	////check if level allready exists
	//XMLDocument tempDoc;
	//XMLError fileTest = tempDoc.LoadFile(("../../../Blobsonic/Source/Resources/scenes/" + sLevelName + ".xml").c_str());
	//
	//if(fileTest == XML_SUCCESS)
	//{
	//	//file allready exists

	//	cout << sLevelName << ".xml - Allready exists , Overighting Level ...." << endl;
	//	system("pause");
	//	tempDoc.SaveFile(("../../../Blobsonic/Source/Resources/scenes/" + sLevelName + ".xml").c_str());
	//	cout << endl;
	//	
	//}


	//grid size
	//take the levels size
	cout << "- " << endl;
	cout << "- " << endl;
	cout << "- Size of Grid units : ";
	float fGrid = 100;
	cin >> fGrid;
	

	//take the levels size
	cout << "- " << endl;
	cout << "- 1 Unit = " << fGrid << " pixels" << endl;
	cout << "- " << endl;
	cout << "- Width of level (units) : ";
	float fXDimension;
	cin >> fXDimension;

	//take the levels size
	cout << "- " << endl;
	cout << "- Depth of level (units) : ";
	float fZDimension;
	cin >> fZDimension;

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
			//Model
			XMLElement * Model = xmlDoc.NewElement("Model");
			pScene->InsertFirstChild(Model);

				//ID
				XMLElement * ID = xmlDoc.NewElement("ID");
				Model->InsertFirstChild(ID);
				ID->SetText("floor");
				Model->InsertEndChild(ID);

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
				Model->InsertFirstChild(Shader);
				Texture->SetText("floor_texture");
				Model->InsertEndChild(Texture);

				//Position
				XMLElement * Position = xmlDoc.NewElement("Position");
				Model->InsertFirstChild(Position);

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


				Model->InsertEndChild(Position);

				//Scale
				XMLElement * Scale = xmlDoc.NewElement("Scale");
				Model->InsertFirstChild(Scale);
				XMLElement * ScaleX = xmlDoc.NewElement("X");
				XMLElement * Scaley = xmlDoc.NewElement("Y");
				XMLElement * ScaleZ = xmlDoc.NewElement("Z");

					//x
					Scale->InsertFirstChild(ScaleX);
					ScaleX->SetText(fGrid );
					Scale->InsertEndChild(ScaleX);

					//y
					Scale->InsertFirstChild(Scaley);
					Scaley->SetText(1.0f);
					Scale->InsertEndChild(Scaley);

					//z
					Scale->InsertFirstChild(ScaleZ);
					ScaleZ->SetText(fGrid );
					Scale->InsertEndChild(ScaleZ);


				Model->InsertEndChild(Scale);

				//Rotation
				XMLElement * Rotation = xmlDoc.NewElement("Rotation");
				Model->InsertFirstChild(Rotation);
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


				Model->InsertEndChild(Rotation);

				//Origin
				XMLElement * Origin = xmlDoc.NewElement("Origin");
				Model->InsertFirstChild(Origin);
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


				Model->InsertEndChild(Origin);


			pScene->InsertEndChild(Model);
		}
	}



	

	//create the default skybox
	for (int i = 0; i < 1; i++)
	{
		//Model
		XMLElement * Model = xmlDoc.NewElement("Model");
		pScene->InsertFirstChild(Model);

		//ID
		XMLElement * ID = xmlDoc.NewElement("ID");
		Model->InsertFirstChild(ID);
		ID->SetText("skybox");
		Model->InsertEndChild(ID);

		//mesh
		XMLElement * Mesh = xmlDoc.NewElement("Mesh");
		Model->InsertFirstChild(Mesh);
		Mesh->SetText("skybox_mesh");
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
		Model->InsertFirstChild(Shader);
		Texture->SetText("skybox_texture");
		Model->InsertEndChild(Texture);

		//Position
		XMLElement * Position = xmlDoc.NewElement("Position");
		Model->InsertFirstChild(Position);
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


		Model->InsertEndChild(Position);

		//Scale
		XMLElement * Scale = xmlDoc.NewElement("Scale");
		Model->InsertFirstChild(Scale);
		XMLElement * ScaleX = xmlDoc.NewElement("X");
		XMLElement * Scaley = xmlDoc.NewElement("Y");
		XMLElement * ScaleZ = xmlDoc.NewElement("Z");

		//x
		Scale->InsertFirstChild(ScaleX);
		ScaleX->SetText(1.0f * fXDimension);
		Scale->InsertEndChild(ScaleX);

		//y
		Scale->InsertFirstChild(Scaley);
		Scaley->SetText(1.0f * max(fXDimension, fZDimension));
		Scale->InsertEndChild(Scaley);

		//z
		Scale->InsertFirstChild(ScaleZ);
		ScaleZ->SetText(1.0f * fZDimension);
		Scale->InsertEndChild(ScaleZ);


		Model->InsertEndChild(Scale);

		//Rotation
		XMLElement * Rotation = xmlDoc.NewElement("Rotation");
		Model->InsertFirstChild(Rotation);
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
		Model->InsertEndChild(Rotation);

		pScene->InsertEndChild(Model);
	}

	

	//Create the camera
	XMLElement * Camera = xmlDoc.NewElement("Camera");
	pScene->InsertFirstChild(Camera);

	for (int i = 0; i < 1; i++)
	{
		//ID
		XMLElement * CID = xmlDoc.NewElement("ID");
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
		FOV->SetText(45.0f);
		Camera->InsertEndChild(FOV);

		//AspectRatio
		XMLElement * AspectRatio = xmlDoc.NewElement("AspectRatio");
		Camera->InsertFirstChild(AspectRatio);
		AspectRatio->SetText(1.3333f);
		Camera->InsertEndChild(AspectRatio);

		//FarPlane
		XMLElement * FarPlane = xmlDoc.NewElement("FarPlane");
		Camera->InsertFirstChild(FarPlane);
		FarPlane->SetText(1000 * max(fXDimension, fZDimension));
		Camera->InsertEndChild(FarPlane);

		//NearPlane
		XMLElement * NearPlane = xmlDoc.NewElement("NearPlane");
		Camera->InsertFirstChild(NearPlane);
		NearPlane->SetText(0.05f);
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

void loadLevel()
{
}

void deleteLevel()
{
}
