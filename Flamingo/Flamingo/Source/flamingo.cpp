#include "flamingo.h"
#define PI 3.14159265358979323846264

using namespace al;

flamingo::flamingo(soundLibrary* SoundLibrary, collision* Collide, input* Input)
{
	m_soundLibrary = SoundLibrary;
	m_input = Input;
	m_multiplier = 3.0f;
	m_moveTime = 0.3f;
	m_hasFood = false;

	/////////BODY//////////
	m_flamingoPosition = vector(740,550);

	////////HEAD/////////
	m_drag = 0;
	m_headOrigin = m_flamingoPosition + vector(-19,-165);
	m_headRotate = 0;

	
	// Textures and sprites
#pragma region Textures and sprites

	///////////BODY////////////
	m_bodyTexture = new texture("Flamingo_player_body.png");
	m_flamingoBody.setTexture(m_bodyTexture);
	m_flamingoBody.setPosition(m_flamingoPosition);
	m_flamingoBody.setOrigin(vector(10, 100));
	m_flamingoBody.setScale(0.5f, 0.5f);

	////////////HEAD///////////
	m_headTexture = new texture("Flamingo_player_head_Animation.png");
	m_flamingoHead.setTexture(m_headTexture);
	m_flamingoHead.setPosition(m_headOrigin);
	m_flamingoHead.setOrigin(vector(120, 70));
	m_flamingoHead.setScale(0.5f, 0.5f);

	m_headAnimation = new animation(&m_flamingoHead, 6, 200, 143, false);
	m_headAnimation->ChangeAnimation(0, 1, 0, 20);

	m_crossTexture = new texture("crosshair.png");	
	m_crosshairSprite.setTexture(m_crossTexture);
	m_crosshairSprite.setPosition(m_headOrigin);
	m_crosshairSprite.setOrigin(vector(25, 25));

	/////////////NECK//////////
	m_neckTexture = new texture("Flamingo_player_neck.png");

	
#pragma endregion

	/////////NECK///////

	int neckPieceCount = 10;
	for (int i = 0; i < neckPieceCount; ++i)
	{
		m_neckPieces.push_back(new neckPiece());
		m_neckPieces[i]->m_sprite.setTexture(m_neckTexture);
		m_neckPieces[i]->m_sprite.setPosition(m_flamingoPosition + vector(-1*i,-17*i));
		m_neckPieces[i]->m_sprite.setOrigin(vector(18, 20));
		m_neckPieces[i]->m_sprite.setScale(0.5f, 0.5f);

		float place = ((float)i + 0.5f)/(float)neckPieceCount;
		m_neckPieces[i]->m_positionMultiplier = vector(place,(sin(float(place * -2 * PI)))/8);
	}


	float HBW = m_flamingoHead.getGlobalBounds().width / 2;
	float HBH = m_flamingoHead.getGlobalBounds().width / 2;
	float HBOX = ((m_flamingoHead.getOrigin().x - 60) * m_flamingoHead.getScale().x) + HBW/2;
	float HBOY = ((m_flamingoHead.getOrigin().y - 80) * m_flamingoHead.getScale().y) + HBH/2;

	m_headHitbox = Collide->createHitBox(m_headPosition, 
		vector(HBW,HBH), 
		vector(HBOX,HBOY),1);

	m_headHitbox->isEnabled = false;
}

flamingo::~flamingo()
{
	std::cout<<"deleted flamingo"<<std::endl;
	delete m_bodyTexture;
}

void flamingo::update(float DeltaTime)
{
	m_bodyToHead = m_flamingoPosition - m_headPosition;
	m_timer += DeltaTime;
	
#pragma region Head

	switch(m_drag)
	{
	case 0: // head in origin
		m_headPosition = m_headOrigin;

			
		if (m_input->isButtonPressed(al::Button::MouseLeft) &&
			m_input->getMousePosition().x > m_flamingoHead.getPosition().x - 50 &&
			m_input->getMousePosition().x < m_flamingoHead.getPosition().x + 50 &&
			m_input->getMousePosition().y > m_flamingoHead.getPosition().y - 50 &&
			m_input->getMousePosition().y < m_flamingoHead.getPosition().y + 50 )
		{
			m_drag = 1;
			m_soundLibrary->m_sounds[1]->play();
			m_headAnimation->ChangeAnimation(1,1,1,15);
		}

		break;

	case 1: // head being dragged
		m_mousePosition.x = m_input->getMousePosition().x;
		m_mousePosition.y = m_input->getMousePosition().y;

		m_headPosition = m_mousePosition;
		m_direction = m_headOrigin - m_headPosition;

		{

			//cant drag head too far away.
			float distance = sqrt(pow(m_direction.x,2) + pow(m_direction.y,2));

			// crosshair goes opposite direction of the head from the origin
			m_crossHair = m_headOrigin + vector(m_direction.x * m_multiplier, m_direction.y * m_multiplier);
			m_crosshairSprite.setPosition(m_crossHair);

			// count angle from headposition and headposition.x
			m_headRotate = 0 ;
		}

		if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)) // head released
		{
			m_timer = 0;
			m_drag = 2;
			m_soundLibrary->m_sounds[0]->play();
			m_headAnimation->ChangeAnimation(2,1,2,15);
			
			m_direction = m_crossHair - m_headPosition;
		}

		break;

	case 2: // head released goes to crosshair
		{
			//m_direction = m_crossHair - m_headPosition;
			//vector Movement((m_direction.x*10)*DeltaTime,(m_direction.y*10)*DeltaTime);
			//m_headPosition += Movement;

			// number is the time head uses to get to crosshair location
			m_headPosition = m_crossHair - m_direction * (1 - m_timer / m_moveTime);
			if (m_timer > m_moveTime)
			{
				m_drag = 3;
				if (!m_hasFood)
					m_headHitbox->isEnabled = true;
			}
		}

		//if(m_headPosition.x < m_crossHair.x+4 && m_headPosition.x > m_crossHair.x-4 &&
		//	m_headPosition.y < m_crossHair.y+4 && m_headPosition.y > m_crossHair.y-4)
		//{
		//	m_drag = 3;
		//	m_headHitbox->isEnabled = true;
		//}

		break;
	case 3: //head goes back to starting point/origin
		m_headHitbox->isEnabled = false;
		{
			m_direction = m_headOrigin - m_headPosition;
			vector Movement((m_direction.x*10)*DeltaTime,(m_direction.y*10)*DeltaTime);
			m_headPosition += Movement;
		}

		if(m_headPosition.x < m_headOrigin.x+1 && m_headPosition.x > m_headOrigin.x-1 &&
			m_headPosition.y < m_headOrigin.y+1 && m_headPosition.y > m_headOrigin.y-1)
		{
			m_drag = 0;
			m_crossHair = m_headOrigin;
			m_direction = vector(0,0);
			m_headAnimation->ChangeAnimation(0, 1, 0, 20);
		}
		break;
	}

#pragma endregion

	//////////NECK///////////////
#pragma region Neck
	{
		float lenght = m_bodyToHead.getLenght();
		float angle = m_bodyToHead.getAngle();
		
		for (int i = 0; i < m_neckPieces.size(); ++i)
		{
			m_neckPieces[i]->m_positionRelative = m_neckPieces[i]->m_positionMultiplier * lenght;
			m_neckPieces[i]->m_positionRelative.rotate(angle);
			m_neckPieces[i]->m_sprite.setPosition(m_neckPieces[i]->m_positionRelative + m_flamingoPosition);
		}
	}
#pragma endregion


	// set sprites to their Positions
	m_flamingoHead.setPosition(m_headPosition);
	m_crosshairSprite.setPosition(m_crossHair);
	m_headHitbox->Position = m_headPosition;

	m_headAnimation->update(DeltaTime);
}

void flamingo::draw(al::viewport* Viewport)
{
	Viewport->draw(&m_flamingoBody);
	for (int i = 0; i < m_neckPieces.size(); ++i)
	Viewport->draw(&m_neckPieces[i]->m_sprite);
	Viewport->draw(&m_flamingoHead);
	Viewport->draw(&m_crosshairSprite);
}