#include "test.h"
#include <time.h>
#include <vector>
#include <string>

using namespace std;
b2Body* Player, *bola, *Player2, *trigger;
b2Vec2 force;
int pontPlayer1 = 0, pontPlayer2 = 0;

enum ID
{
	playerID, bolaID, paredeID, EsqID, DirID, triggerID
};

struct userData
{
	int ID;
	bool alive;
	float angle;
	b2Vec2 force;
	float x;
	float y;

};

vector <b2Body*> matadouro;



class MeuOuvidorDeContato : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact) override
	{
		b2Fixture* fa, *fb;
		fa = contact->GetFixtureA();
		fb = contact->GetFixtureB();

		b2Body* bodyA = NULL, *bodyB = NULL;
		if (fa) bodyA = fa->GetBody();
		if (fb) bodyB = fb->GetBody();

		if (bodyA && bodyB) //checar se o corpo ainda existe ????
		{
			//Checa se os objetos possuem userData
			void* bodyUserDataA = bodyA->GetUserData();
			void* bodyUserDataB = bodyB->GetUserData();
			if (bodyUserDataA && bodyUserDataB) //s continua se os 2 tiverem userData -- PORCOS E PASSAROS
			{
				userData* udA = static_cast<userData*>(bodyUserDataA);
				userData* udB = static_cast<userData*>(bodyUserDataB);

				/*if (udA->ID == bolaID && udB->ID == paredeID || udA->ID == paredeID && udB->ID == bolaID || udA->ID == bolaID && udB->ID == playerID)
				{
					force = getVectorComponents(5000, bola->GetAngle());
					bola->ApplyForceToCenter(force, true);
				}*/
				if (udA->ID == bolaID && udB->ID == EsqID || udA->ID == EsqID && udB->ID == bolaID)
				{
					setReset(true);
					pontPlayer2 += 1;
				}

				if (udA->ID == bolaID && udB->ID == DirID || udA->ID == DirID && udB->ID == bolaID)
				{
					setReset(true);
					pontPlayer1 += 1;
				}

				if (udA->ID == bolaID && udB->ID == triggerID || udA->ID == triggerID && udB->ID == bolaID)
				{
					redirectBola = true;			
				}
			}
		}
	}


	void setReset(bool res) 
	{
		resetar = res;
	}
	bool getReset()
	{
		return resetar;
	}
	bool resetar = false, redirectBola = false;
};



class Jogo_Pong : public Test
{
public:
	Jogo_Pong()
	{
		srand(time(0));


		m_world->SetGravity(b2Vec2(0.0, 0.0));

		contactListener.setReset(false);

		Paredes[0] = CreateBox(b2Vec2(0.0, -10), b2Vec2(50.0, 2.0), 1.0, 0.5, 0.0, b2_staticBody);
		userData* ud = new userData;
		ud->ID = paredeID;
		Paredes[0]->SetUserData(ud);


		Paredes[1] = CreateBox(b2Vec2(50.0, 20.0), b2Vec2(2.0, 30.0), 1.0, 0.5, 0.0, b2_staticBody);
		userData* ud2 = new userData;
		ud2->ID = DirID;
		Paredes[1]->SetUserData(ud2);


		Paredes[2] = CreateBox(b2Vec2(-50.0, 20.0), b2Vec2(2.0, 30.0), 1.0, 0.5, 0.0, b2_staticBody);
		userData* ud3 = new userData;
		ud3->ID = EsqID;
		Paredes[2]->SetUserData(ud3);


		Paredes[3] = CreateBox(b2Vec2(0.0, 50.0), b2Vec2(50.0, 2.0), 1.0, 0.5, 0.0, b2_staticBody);
		userData* ud4 = new userData;
		ud4->ID = paredeID;
		Paredes[3]->SetUserData(ud4);


		Player = CreateBox(b2Vec2(-47.0, 20.0), b2Vec2(1.0, 5.0), 0.5, 0.2, 0.0, b2_dynamicBody);
		Player->SetFixedRotation(true);
		userData* ud5 = new userData;
		ud5->ID = playerID;
		Player->SetUserData(ud5);

		Player2 = CreateBox(b2Vec2(47.0, 20.0), b2Vec2(1.0, 5.0), 0.5, 0.2, 0.0, b2_dynamicBody);
		Player2->SetFixedRotation(true);
		userData* ud51 = new userData;
		ud51->ID = playerID;
		Player2->SetUserData(ud5);

		//	Player->SetTransform(b2Vec2(-47.0, Player->GetPosition.y), 0.0f);
		bola = CreateCircle(b2Vec2(0.0, 20.0), 1.0, 1.0, 0.0, 1.0, false, b2_dynamicBody);
		userData* ud6 = new userData;
		ud6->ID = bolaID;
		ud6->force = force;

		bola->SetUserData(ud6);

		CreateTrigger();

		applyingForce = false;
		force.SetZero();
		globalPoint.SetZero();
		m_world->SetContactListener(&contactListener);

	}
	
	
	void Keyboard(int key) override
	{
		switch (key)
		{
		case GLFW_KEY_W:
			Player->SetAwake(false);
			Angle = 90.0f;
			force = getVectorComponents(20000, Angle);
			Player->ApplyForceToCenter(force, true);
			break;

		case GLFW_KEY_S:
			Player->SetAwake(false);
			Angle = 270.0f;
			force = getVectorComponents(20000, Angle);
			Player->ApplyForceToCenter(force, true);
			break;
		case GLFW_KEY_G:
			int sorteioAngle;
			sorteioAngle = rand() % 4;
			bola->SetAwake(false);

			switch (sorteioAngle)
			{
			case 0: Angle = 45.0f;
				break;
			case 1: Angle = 135.0f;
				break;
			case 2: Angle = 225.0f;
				break;
			case 3: Angle = -45.0f;
				break;
			}
			force = getVectorComponents(10000, Angle);
			bola->ApplyForceToCenter(force, true);

			break;

			case GLFW_KEY_I:
			Player2->SetAwake(false);
			Angle = 90.0f;
			force = getVectorComponents(20000, Angle);
			Player2->ApplyForceToCenter(force, true);
			break;

		case GLFW_KEY_K:
			Player2->SetAwake(false);
			Angle = 270.0f;
			force = getVectorComponents(20000, Angle);
			Player2->ApplyForceToCenter(force, true);
			break;
		}

	}
	void Step(Settings& settings) override
	{
		Test::Step(settings);


		if (contactListener.getReset())
		{
			ResetBola(b2Vec2(0.0f, 20.0f), bola->GetAngle());
			contactListener.setReset(false);
		}

		if (contactListener.redirectBola == true)
		{
			m_world->DestroyBody(trigger);
			CreateTrigger();
			RedirectBola();
		}

		processInputs();

		force.Normalize();
		force *= 5;

		g_debugDraw.DrawPoint(Player->GetWorldCenter(), 5, b2Color(1.0, 0.0, 0.0));
		g_debugDraw.DrawSegment(Player->GetWorldCenter(), Player->GetWorldCenter() + force, b2Color(1.0, 0.0, 0.0));

		b2Vec2 localPoint = b2Vec2(-0.5, 1.0);
		globalPoint = b2Vec2(Player->GetWorldPoint(localPoint));
		g_debugDraw.DrawPoint(globalPoint, 5, b2Color(1.0, 1.0, 0.0));
		//const char s = char(pontPlayer1);
		g_debugDraw.DrawString(5, m_textLine, "PLAYER 1 USA 'W' e 'S' ------- PLAYER 2 USA 'I' e 'K' ----------- LANCA A BOLA COM 'G'");
	

	}
	void ResetBola(b2Vec2 pos, float angle)
	{
		bola->SetTransform(pos, angle);
		bola->SetAwake(false);
	}

	void RedirectBola()
	{
		int sorteioAngle;
		sorteioAngle = rand() % 4;
		bola->SetAwake(false);
		
		switch (sorteioAngle)
		{
		case 0: Angle = 45.0f;
			break;
		case 1: Angle = 135.0f;
			break;
		case 2: Angle = 225.0f;
			break;
		case 3: Angle = -45.0f;
			break;
		}
		force = getVectorComponents(10000, Angle);
		bola->ApplyForceToCenter(force, true);

		contactListener.redirectBola = false;
	}
	static Test* Create()
	{
		return new Jogo_Pong;
	}

	void CreateTrigger()
	{
		int x, y;
		x = rand() %  90 - 45;
		y = rand() % 50 - 5;

		trigger = CreateCircle(b2Vec2(float(x), float(y)), 3.0, 1.0, 0.0, 1.0, true, b2_staticBody);
		userData* ud7 = new userData;
		ud7->ID = triggerID;
		
		trigger->SetUserData(ud7);
	}

	b2Body* CreateBox(b2Vec2 pos, b2Vec2 dim, float density, float friction, float restitution, b2BodyType type);
	b2Body* CreateCircle(b2Vec2 pos, float radius, float density, float friction, float restitution, bool isSensor, b2BodyType type);
	void processInputs();
	b2Vec2 getVectorComponents(float length, float angle);
	float degreesToRadians(float angle);
	float radiansToDegrees(float angle);


protected:
	b2Body *Paredes[3];
	bool applyingForce, bolaLancada = false;
	b2Vec2 globalPoint;
	float Angle;

	MeuOuvidorDeContato contactListener;
};

static int testIndex = RegisterTest("Examples", "Jogo Pong", Jogo_Pong::Create);

b2Body* Jogo_Pong::CreateBox(b2Vec2 pos, b2Vec2 dim, float density, float friction, float restitution, b2BodyType type)
{
	b2Body* corpinho;
	b2BodyDef boxDef;
	boxDef.position = pos;
	boxDef.type = type;
	b2PolygonShape boxShape;

	boxShape.SetAsBox(dim.x, dim.y);

	b2FixtureDef boxFix;

	boxFix.shape = &boxShape;
	boxFix.density = density;
	boxFix.friction = friction;
	boxFix.restitution = restitution;

	corpinho = m_world->CreateBody(&boxDef);
	corpinho->CreateFixture(&boxFix);


	return corpinho;
}

b2Body* Jogo_Pong::CreateCircle(b2Vec2 pos, float radius, float density, float friction, float restitution, bool isSensor, b2BodyType type)
{
	b2Body* circulinho;

	b2BodyDef circleDef;

	circleDef.position = pos;
	circleDef.type = type;

	b2CircleShape circleShape;

	circleShape.m_radius = radius;

	b2FixtureDef circleFix;

	circleFix.shape = &circleShape;
	circleFix.density = density;
	circleFix.friction = friction;
	circleFix.restitution = restitution;
	circleFix.isSensor = isSensor;
	circulinho = m_world->CreateBody(&circleDef);
	circulinho->CreateFixture(&circleFix);

	return circulinho;
}

b2Vec2 Jogo_Pong::getVectorComponents(float length, float angle)
{
	b2Vec2 v;
	v.x = length * cos(degreesToRadians(angle));
	v.y = length * sin(degreesToRadians(angle));
	return v;
}

float Jogo_Pong::degreesToRadians(float angle)
{
	return  angle * b2_pi / 180.0;
}

float Jogo_Pong::radiansToDegrees(float angle)
{
	return angle * 180 / b2_pi;
}

void Jogo_Pong::processInputs()
{
	if (applyingForce)
	{
		force = getVectorComponents(10000, 45);
		Player->ApplyForceToCenter(force, true);


		//Player->ApplyForce(force, globalPoint, true);

		applyingForce = false;
	}
}