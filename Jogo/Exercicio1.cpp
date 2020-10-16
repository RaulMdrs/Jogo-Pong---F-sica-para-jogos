#include "test.h"
#include <time.h>

float cacaca = 0.0, atritinho = 0.0;
class Lista1 : public Test //você cria a sua classe derivada da classe base Test
{
public:
	Lista1() {


		//// chão e bordas /////////////
		CreateBox(b2Vec2(0.0, -50.0), b2Vec2(50.0, 2.0), 1.0, 0.5, 0.5, b2_staticBody);
		CreateBox(b2Vec2(50.0, 0.0), b2Vec2(2.0, 50.0), 1.0, 0.5, 0.5, b2_staticBody);
		CreateBox(b2Vec2(-50.0, 0.0), b2Vec2(2.0, 50.0), 1.0, 0.5, 0.5, b2_staticBody);
		CreateBox(b2Vec2(0.0, 50.0), b2Vec2(50.0, 2.0), 1.0, 0.5, 0.5, b2_staticBody);


		/////////////////////// Mexendo com gravidade //// 

		//m_world->SetGravity(b2Vec2(0.0, 100.0));

		
		///// bloquinho de teste

		/*CreateBox(b2Vec2(-10.0, 20.0), b2Vec2(4.0, 4.0), 1.0, 0.5, 0.5);

		CreateBox(b2Vec2(10.0, 20.0), b2Vec2(2.0, 2.0), 1.0, 0.5, 0.5);

		CreateCircle(b2Vec2(30.0, 20.0), 0.5, 1.0, 0.5, 0.5);*/

		///// pilha de caixas
	/*	CreateBox(b2Vec2(10.0, -40.0), b2Vec2(4.0, 4.0), 1.0, 0.5, 0.5);
		CreateBox(b2Vec2(10.0, -30.0), b2Vec2(4.0, 4.0), 1.0, 0.5, 0.5);
		CreateBox(b2Vec2(10.0, -20.0), b2Vec2(4.0, 4.0), 1.0, 0.5, 0.5);
		CreateBox(b2Vec2(10.0, -10.0), b2Vec2(4.0, 4.0), 1.0, 0.5, 0.5);
		CreateBox(b2Vec2(10.0, 0.0), b2Vec2(4.0, 4.0), 1.0, 0.5, 0.5);
		CreateBox(b2Vec2(10.0, 10.0), b2Vec2(4.0, 4.0), 1.0, 0.5, 0.5);*/


		/////// pilha de circulos

		//CreateCircle(b2Vec2(30.0, -45.0), 5.0, 1.0, 0.0, 0.5);
		//CreateCircle(b2Vec2(30.0, -40.0), 4.5, 1.0, 0.0, 0.5);
		//CreateCircle(b2Vec2(30.0, -35.0), 4.0, 1.0, 0.0, 0.5);
		//CreateCircle(b2Vec2(30.0, -30.0), 3.5, 1.0, 0.0, 0.5);
		//CreateCircle(b2Vec2(30.0, -25.0), 3.0, 1.0, 0.0, 0.5);
		//CreateCircle(b2Vec2(30.0, -20.0), 2.5, 1.0, 0.0, 0.5);

		/// gostei de fazer na mão por isso n usei for nem nada do tipo


		// murinho 10x10

		//for (float l = 0; l < 10; l++)
		//{
		//	for (float altura = 0; altura < 10; altura++)
		//	{ 
		//		CreateBox(b2Vec2(l + 1.1, altura + 1 -43), b2Vec2(1.0, 1.0), 1.0, 0.1, 0.1);
		//	}
		//}

		//CreateLine(b2Vec2(0.0, 0.0), b2Vec2(-40.0, -20.0), b2Vec2(40.0, -35.0), 0.5, 0.5, 0.5); // rampinha

		// joguinho

		//CreateBox(b2Vec2(0.0, -40), b2Vec2(4))
	}

	void Step(Settings& settings) override
	{
		//Chama o passo da simulação e o algoritmo de rendering
		Test::Step(settings);

		//show some text in the main screen
		g_debugDraw.DrawString(5, m_textLine, "Este e' um template para os exercicios!! :)");
		m_textLine += 15;
	}

	static Test* Create()
	{
		return new Lista1;
	}

	void Keyboard(int key) override
	{

		switch (key)
		{
		case GLFW_KEY_B:
			//atributos aleatorios
			//CreateBox(b2Vec2(rand() % 80 - 40, rand() % 45), b2Vec2(rand() % 7 + 1, rand() % 7 + 1), rand() % 3 + 1, rand() % 3 + 1, rand() % 3 + 1);


			//CreateBox(b2Vec2(0.0, 0.0), b2Vec2(4.0, 4.0), 1.0, 0.5, cacaca); com atributo de restituição aumentando a cada caixa criada
			//if (cacaca <= 1)
			//{
			//	cacaca += 0.1;
			//}

			CreateBox(b2Vec2(-35.0, -17.0), b2Vec2(2.0, 2.0), 1.0, atritinho, 0.5); // com o atributo de atrito aumentando a cada caixa criada
			if (atritinho <= 1)
			{
				atritinho += 0.1;
			}
			break;

		case GLFW_KEY_C:

			CreateCircle(b2Vec2(rand() % 80 - 40, rand() % 45), rand() % 5 + 1, rand() % 3 + 1, rand() % 3 + 1, rand() % 3 + 1);

			break;
		case GLFW_KEY_G:

			m_world->SetGravity(b2Vec2(m_world->GetGravity().x * -1, m_world->GetGravity().y * -1));
			break;

		case GLFW_KEY_L: // L de loucura sora

			m_world->SetGravity(b2Vec2((m_world->GetGravity().x + 1)  * -10, m_world->GetGravity().y * -1));
			break;

		case GLFW_KEY_N: // gravidade normal

			m_world->SetGravity(b2Vec2(0.0, 50.0));
			break;

		case GLFW_KEY_I: // I de lInha sora
			CreateLine(b2Vec2(0.0, 0.0), b2Vec2(4.0, -45.0), b2Vec2(-10.0, -40.0), 0.5, 0.5, 0.5);
			break;
		}
	}

	b2Body* CreateBox(b2Vec2 pos, b2Vec2 dim, float density, float friction, float restitution, b2BodyType = b2_dynamicBody);
	b2Body* CreateCircle(b2Vec2 pos, float radius, float density, float friction, float restitution, b2BodyType = b2_dynamicBody);
	b2Body* Lista1::CreateLine(b2Vec2 pos, b2Vec2 comeco, b2Vec2 final, float density, float friction, float restitution, b2BodyType = b2_dynamicBody);
};

//Aqui fazemos o registro do novo teste 
static int testIndex = RegisterTest("Examples", "Lista1", Lista1::Create);

b2Body* Lista1::CreateBox(b2Vec2 pos, b2Vec2 dim, float density, float friction, float restitution, b2BodyType type)
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

b2Body* Lista1::CreateCircle(b2Vec2 pos, float radius, float density, float friction, float restitution, b2BodyType type)
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

b2Body* Lista1::CreateLine(b2Vec2 pos, b2Vec2 comeco, b2Vec2 final, float density, float friction, float restitution, b2BodyType type)
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
