#include "flamingo.h"

using namespace al;

flamingo::flamingo(soundLibrary* SoundLibrary, collision* Collide, input* Input)
{
	m_soundLibrary = SoundLibrary;
	m_input = Input;
	m_multiplier = 3.0f;
	m_throwMultiplier = 1.4f;
	m_moveTime = 0.3f;
	m_hasFood = false;
	m_distance = 0;
	m_maxDistance = 200;

	/////////BODY//////////
	m_flamingoPosition = vector(980,515);

	////////HEAD/////////
	m_headOrigin = m_flamingoPosition + vector(-19,-165);
	m_headRotate = 0;
	m_drag = 0;

	
	// Textures and sprites
#pragma region Textures and sprites

	///////////BODY////////////
	m_bodyTexture = new texture("Flamingo_player_body.png");
	m_flamingoBody.setTexture(m_bodyTexture);
	m_flamingoBody.setPosition(m_flamingoPosition);
	m_flamingoBody.setOrigin(vector(10, 100));
	m_flamingoBody.setScale(0.5f, 0.5f);
	m_flamingoBody.setLayer(100);

	////////////HEAD///////////
	m_headTexture = new texture("Flamingo_player_head_Animation.png");
	m_flamingoHead.setTexture(m_headTexture);
	m_flamingoHead.setPosition(m_headOrigin);
	m_flamingoHead.setOrigin(vector(120, 70));
	m_flamingoHead.setScale(0.5f, 0.5f);
	m_flamingoHead.setLayer(291);

	m_headAnimation = new animation(&m_flamingoHead, 6, 214, 143, false);
	m_headAnimation->ChangeAnimation(0, 1, 0, 20);

	m_crossTexture = new texture("crosshair.png");	
	m_crosshairSprite.setTexture(m_crossTexture);
	m_crosshairSprite.setPosition(m_headOrigin);
	m_crosshairSprite.setOrigin(vector(25, 25));
	m_crosshairSprite.setColor(0,0,0,0);

	////////////ARROW//////////
	m_arrowTexture = new texture("origonArrow.png");
	m_arrowSprite.setTexture(m_arrowTexture);
	m_arrowSprite.setOrigin(vector(m_arrowSprite.getTextureSize().x/2, m_arrowSprite.getTextureSize().y/2));
	m_arrowSprite.setPosition(m_headOrigin);
	m_arrowSprite.setLayer(290);
	m_arrowSprite.setColor(0,0,0,0);
	

#pragma endregion

	/////////NECK///////
	m_neckTexture = new texture("Flamingo_player_neck.png");

	int neckPieceCount = 10;
	for (int i = 0; i < neckPieceCount; ++i)
	{

		m_neckPieces.push_back(new neckPiece());
		m_neckPieces[i]->m_sprite.setTexture(m_neckTexture);
		m_neckPieces[i]->m_sprite.setPosition(m_flamingoPosition);
		m_neckPieces[i]->m_sprite.setOrigin(vector(18, 20));
		m_neckPieces[i]->m_sprite.setScale(0.5f, 0.5f);
		m_neckPieces[i]->m_sprite.setLayer(100);

		float place = ((float)i + 0.5f)/(float)neckPieceCount;
		m_neckPieces[i]->m_positionMultiplier = vector(place,(sin(float(place * -2 * PI)))/8);
	}


	float HBW = m_flamingoHead.getGlobalBounds().width * 0.8f;
	float HBH = m_flamingoHead.getGlobalBounds().width * 0.8f;
	float HBOX = HBW/2 ;
	float HBOY = HBH/2 ;

	m_headHitbox = Collide->createHitBox(m_headPosition, 
		vector(HBW,HBH), 
		vector(HBOX,HBOY),1);

	m_headHitbox->isEnabled = false;
}

flamingo::~flamingo()
{
	std::cout<<"deleted flamingo"<<std::endl;
	delete m_bodyTexture;
	delete m_headTexture;
	delete m_crossTexture;
	delete m_neckTexture;
	delete m_arrowTexture;
	delete m_headAnimation;
}

void flamingo::update(float DeltaTime)
{
	m_timer += DeltaTime;
	//m_headRotate += DeltaTime * 90;
	
#pragma region Head

	switch(m_drag)
	{
	case 0: // head in origin
		m_headPosition = m_headOrigin;
		if (m_input->isButtonPressed(al::Button::MouseLeft) &&
			(m_input->getMousePosition() - m_flamingoHead.getPosition()).getLenght() < 50 )
		{
			m_mouseStartPos = m_input->getMousePosition();
			m_drag = 1;
			//m_soundLibrary->m_sounds[1]->play();
			m_headAnimation->ChangeAnimation(1,1,1,15);
			m_soundLibrary->m_sounds[3]->play();
		}
		break;
	case 1: // head being dragged
		//m_headPosition = m_headOrigin - m_direction;

		{
		

			//cant drag head too far away.
			m_direction = m_mouseStartPos - m_input->getMousePosition();

			m_distance = m_direction.getLenght();
			if (m_distance > m_maxDistance)
			{
				m_direction /= m_distance / m_maxDistance;
				m_distance = m_maxDistance;
			}
			
			m_headPosition = m_headOrigin - m_direction;

			// crosshair goes opposite direction of the head from the origin
			if (!m_hasFood)
			{
				m_crossHair = m_headOrigin + m_direction * m_multiplier;
			}
			else
			{
				m_crossHair = m_headOrigin + m_direction * m_throwMultiplier;
			}
			m_crosshairSprite.setPosition(m_crossHair);
			//rotate head
 			float angle = m_direction.getAngle();
			if (m_distance > 5)
			{
				if(m_direction.x < 0)
				{
					float angle = m_direction.getAngle();
					flip(false);
					m_headRotate = angle;
				}
				else
				{
					float angle = (-m_direction).getAngle();
					flip(true);
					m_headRotate = angle;
				}
			}
			else
			{
				flip(false);
				m_headRotate = 0;
			}

			m_arrowSprite.setColor(
				(m_distance/m_maxDistance) * 255,
				(1-(m_distance/m_maxDistance)) * 255,
				(m_distance/m_maxDistance) * 0 * 255,
				(m_distance/m_maxDistance * 0.0f + 0.8f) * 255);

			m_arrowSprite.setScale((m_distance*2) / m_arrowSprite.getTextureSize().x,m_distance/m_arrowSprite.getTextureSize().y/4);
			m_arrowSprite.setRotation(m_direction.getAngle());

		}
		if(!m_input->isButtonPressed(al::Button::MouseLeft)) // head released
		{
			m_timer = 0;
			m_drag = 2;
			m_soundLibrary->m_sounds[0]->play();
			m_headAnimation->ChangeAnimation(2,1,2,15);
			m_direction = m_crossHair - m_headPosition;
			m_arrowSprite.setColor(0,0,0,0);
		}
		break;
	case 2: // head released goes to crosshair
		m_headPosition = m_crossHair - m_direction * (1 - m_timer / m_moveTime);
		if (m_timer > m_moveTime)
		{
			m_drag = 3;
			if (!m_hasFood)
				m_headHitbox->isEnabled = true;
		}
		break;
	case 3: //head going back to starting point/origin
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
			m_headRotate = 0;
			flip(false);
		}
		break;
	default:
		std::cout<<"Oh maan! Something is really wrong with flaming drag state"<<std::endl;
		break;
	}

#pragma endregion

	//////////NECK///////////////
#pragma region Neck

	m_bodyToHead = m_flamingoPosition - m_headPosition;
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
	m_flamingoHead.setRotation(m_headRotate);
	m_flamingoHead.setPosition(m_headPosition);
	m_crosshairSprite.setPosition(m_crossHair);

	vector offset(-70 * m_flamingoHead.getScale().x,40 * m_flamingoHead.getScale().y);
	offset.rotate(m_headRotate);
	m_headHitbox->Position = m_headPosition + offset;

	m_headAnimation->update(DeltaTime);
}

void flamingo::draw(al::viewport* Viewport)
{
	Viewport->draw(&m_flamingoBody);
	for (int i = 0; i < m_neckPieces.size(); ++i)
		Viewport->draw(&m_neckPieces[i]->m_sprite);
	Viewport->draw(&m_flamingoHead);
	Viewport->draw(&m_crosshairSprite);
	Viewport->draw(&m_arrowSprite);
}


void flamingo::flip(bool HeadFlipped)
{
	if (HeadFlipped)
		m_flamingoHead.setScale(-0.5f,0.5f);
	else
		m_flamingoHead.setScale(0.5f,0.5f);
}