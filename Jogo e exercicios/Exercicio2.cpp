#include "test.h"
#include <time.h>


class Lista2 : public Test //você cria a sua classe derivada da classe base Test
{
public:
	Lista2() {

	//	m_world->SetGravity(b2Vec2(0, 10));

		//// chão e bordas /////////////
		CreateBox(b2Vec2(0.0, -50.0), b2Vec2(50.0, 2.0), 1.0, 0.5, 0.5, b2_staticBody);
		CreateBox(b2Vec2(50.0, 0.0), b2Vec2(2.0, 50.0), 1.0, 0.5, 0.5, b2_staticBody);
		CreateBox(b2Vec2(-50.0, 0.0), b2Vec2(2.0, 50.0), 1.0, 0.5, 0.5, b2_staticBody);
		CreateBox(b2Vec2(0.0, 50.0), b2Vec2(50.0, 2.0), 1.0, 0.5, 0.5, b2_staticBody);
		

		//selected = CreateCircle(b2Vec2(-20.0, -45.0), 1.0, 1.0, 0.0, 0.5);// EXERCICIO 2

		//selected = CreateBox(b2Vec2(0.0, -45.0), b2Vec2(1.5, 5.0), 1.0, 0.5, 0.5); // EXERCICIO 1

		//for (int i = 0; i < 4; i++)
		//{
		//	CreateBox(b2Vec2(7 + 7 * i, -45.0), b2Vec2(1.5, 5.0), 1.0, 0.5, 0.5);
		//}

		selected = CreateBox(b2Vec2(0, -45.0), b2Vec2(3, 3.0), 0.5, 0.2, 0.0); // exercicio 3

		CreateBox(b2Vec2(0.0, -30.0), b2Vec2(10.0, 2.0), 1.0, 0.5, 0.5, b2_staticBody);
		CreateBox(b2Vec2(10.0, -20.0), b2Vec2(10.0, 2.0), 1.0, 0.5, 0.5, b2_staticBody);

		applyingForce = false;
		force.SetZero();
		globalPoint.SetZero();

	}

	void Step(Settings& settings) override
	{
	
		Test::Step(settings);

		processInputs();

		force.Normalize();
		force *= 5;

		g_debugDraw.DrawPoint(selected->GetWorldCenter(), 5, b2Color(1.0, 0.0, 0.0));
		g_debugDraw.DrawSegment(selected->GetWorldCenter(), selected->GetWorldCenter() + force, b2Color(1.0, 0.0, 0.0));

		
		b2Vec2 localPoint = b2Vec2(-0.5, 1.0);
		globalPoint = b2Vec2(selected->GetWorldPoint(localPoint));
		g_debugDraw.DrawPoint(globalPoint, 5, b2Color(1.0, 1.0, 0.0));
		//show some text in the main screen
		g_debugDraw.DrawString(5, m_textLine, "Este e' um template para os exercicios!! :)");
		m_textLine += 15;
	}

	static Test* Create()
	{
		return new Lista2;
	}

	void Keyboard(int key) override
	{

		switch (key)
		{
		case GLFW_KEY_1:
			CreateBox(b2Vec2(-35.0, -17.0), b2Vec2(2.0, 2.0), 1.0, 0.5, 0.5); // com o atributo de atrito aumentando a cada caixa criada
	     	break;

		case GLFW_KEY_2:

			CreateCircle(b2Vec2(rand() % 80 - 40, rand() % 45), rand() % 5 + 1, rand() % 3 + 1, rand() % 3 + 1, rand() % 3 + 1);

			break;
		case GLFW_KEY_G:

			m_world->SetGravity(b2Vec2(m_world->GetGravity().x * -1, m_world->GetGravity().y * -1));
			break;

		//case GLFW_KEY_L: // L de loucura sora

		//	m_world->SetGravity(b2Vec2((m_world->GetGravity().x + 1)  * -10, m_world->GetGravity().y * -1));
		//	break;

		//case GLFW_KEY_N: // gravidade normal

		//	m_world->SetGravity(b2Vec2(0.0, 50.0));
		//	break;

		case GLFW_KEY_3:
			CreateLine(b2Vec2(0.0, 0.0), b2Vec2(4.0, -45.0), b2Vec2(-10.0, -40.0), 0.5, 0.5, 0.5);
			break;

		case GLFW_KEY_F: 
			applyingForce = true;
			break;

		case GLFW_KEY_T: //se for testar um exercicio que nao seja o 3 precisa tirar o comentario sora
			do
			{
				if (selected->GetNext() != NULL)
				{
					selected = selected->GetNext();
				}
				else selected = m_world->GetBodyList();
			} while (selected->GetType() != b2_dynamicBody);
			break;
         // Daqui pra baixo é do exercicio 2
		case GLFW_KEY_SPACE:
			selected = CreateCircle(b2Vec2(-20.0, -45.0), 1.0, 1.0, 0.0, 0.5); 
			break;
		case GLFW_KEY_MINUS:
			anguloPraLanca -= 10.0f;
			break;
		case GLFW_KEY_KP_ADD:
			anguloPraLanca += 10.0f;
			break;
		case GLFW_KEY_ENTER:
			force = getVectorComponents(10000, anguloPraLanca);
			selected->ApplyForce(force, globalPoint, true);
			break;
         // daqui pra baixo é do exercicio 3
		case GLFW_KEY_A:
			anguloPraLanca = 180.0f;
			force = getVectorComponents(5000, anguloPraLanca);
			selected->ApplyForce(force, globalPoint, true);
			break;
		case GLFW_KEY_D: // se for testar outro exercicio precisa comentar esse case
			anguloPraLanca = 0.0f;
			force = getVectorComponents(5000, anguloPraLanca);
			selected->ApplyForce(force, globalPoint, true);
			break;
		case GLFW_KEY_W:
			anguloPraLanca = 90.0f;
			force = getVectorComponents(20000, anguloPraLanca);
			selected->ApplyForce(force, globalPoint, true);
			break;
		}
	}

	b2Body* CreateBox(b2Vec2 pos, b2Vec2 dim, float density, float friction, float restitution, b2BodyType = b2_dynamicBody);
	b2Body* CreateCircle(b2Vec2 pos, float radius, float density, float friction, float restitution, b2BodyType = b2_dynamicBody);
	b2Body* CreateLine(b2Vec2 pos, b2Vec2 comeco, b2Vec2 final, float density, float friction, float restitution, b2BodyType = b2_dynamicBody);
	void processInputs();
	b2Vec2 getVectorComponents(float length, float angle);
	float degreesToRadians(float angle);
	float radiansToDegrees(float angle);

protected:
	b2Body *selected;
	bool applyingForce;
	b2Vec2 force;
	b2Vec2 globalPoint;
	float anguloPraLanca = 45.0f;
};

//Aqui fazemos o registro do novo teste 
static int testIndex = RegisterTest("Examples", "Lista2", Lista2::Create);

b2Body* Lista2::CreateBox(b2Vec2 pos, b2Vec2 dim, float density, float friction, float restitution, b2BodyType type)
{
	b2Body* corpinho;

	//Definição dos atributos gerais do corpo rígido
	b2BodyDef boxDef;

	boxDef.position = pos;
	boxDef.type = type;

	//Criação da forma do corpo*
	b2PolygonShape boxShape;

	boxShape.SetAsBox(dim.x, dim.y);

	//Definição da fixture
	b2FixtureDef boxFix;

	boxFix.shape = &boxShape;
	boxFix.density = density;
	boxFix.friction = friction;
	boxFix.restitution = restitution;

	//Criação do corpo rígido pelo mundo e da fixture pelo corpo rígido;
	corpinho = m_world->CreateBody(&boxDef);
	corpinho->CreateFixture(&boxFix);


	return corpinho;
}


b2Body* Lista2::CreateCircle(b2Vec2 pos, float radius, float density, float friction, float restitution, b2BodyType type)
{
	b2Body* circulinho;

	//Definição dos atributos gerais do corpo rígido
	b2BodyDef circleDef;

	circleDef.position = pos;
	circleDef.type = type;

	//Criação da forma do corpo*
	b2CircleShape circleShape;

	circleShape.m_radius = radius;

	//Definição da fixture
	b2FixtureDef circleFix;

	circleFix.shape = &circleShape;
	circleFix.density = density;
	circleFix.friction = friction;
	circleFix.restitution = restitution;

	//Criação do corpo rígido pelo mundo e da fixture pelo corpo rígido;
	circulinho = m_world->CreateBody(&circleDef);
	circulinho->CreateFixture(&circleFix);

	return circulinho;
}

b2Body* Lista2::CreateLine(b2Vec2 pos, b2Vec2 comeco, b2Vec2 final, float density, float friction, float restitution, b2BodyType type)
{
	b2Body* lilinha;

	//Definição dos atributos gerais do corpo rígido
	b2BodyDef lilinhaDef;

	lilinhaDef.position = pos;
	lilinhaDef.type = type;

	//Criação da forma do corpo*
	b2EdgeShape lilinhaShape;

	lilinhaShape.SetTwoSided(comeco, final);
	//Definição da fixture
	b2FixtureDef lilinhaFix;

	lilinhaFix.shape = &lilinhaShape;
	lilinhaFix.density = density;
	lilinhaFix.friction = friction;
	lilinhaFix.restitution = restitution;

	//Criação do corpo rígido pelo mundo e da fixture pelo corpo rígido;
	lilinha = m_world->CreateBody(&lilinhaDef);
	lilinha->CreateFixture(&lilinhaFix);


	return lilinha;
}

b2Vec2 Lista2::getVectorComponents(float length, float angle)
{
	b2Vec2 v;
	v.x = length * cos(degreesToRadians(angle));
	v.y = length * sin(degreesToRadians(angle));
	return v;
}

float Lista2::degreesToRadians(float angle)
{
	return  angle * b2_pi / 180.0;
}

float Lista2::radiansToDegrees(float angle)
{
	return angle * 180 / b2_pi;
}

void Lista2::processInputs()
{
	if (applyingForce)
	{
		force = getVectorComponents(10000, 45);
		//selected->ApplyForceToCenter(force, true);

		
		selected->ApplyForce(force, globalPoint, true);

		applyingForce = false;
	}
}
