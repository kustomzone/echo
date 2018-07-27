#include "box2d_body.h"
#include "box2d_world.h"
#include "engine/core/main/Engine.h"

namespace Echo
{
	Box2DBody::Box2DBody()
		: m_body(nullptr)
		, m_type("Static", { "Static", "Kinematic", "Dynamic" })
		, m_restitution(0.5f)
	{
	}

	Box2DBody::~Box2DBody()
	{

	}

	void Box2DBody::bindMethods()
	{
		CLASS_BIND_METHOD(Box2DBody, getType, DEF_METHOD("getType"));
		CLASS_BIND_METHOD(Box2DBody, setType, DEF_METHOD("setType"));
		CLASS_BIND_METHOD(Box2DBody, getRestitution, DEF_METHOD("getRestitution"));
		CLASS_BIND_METHOD(Box2DBody, setRestitution, DEF_METHOD("setRestitution"));

		CLASS_REGISTER_PROPERTY(Box2DBody, "Type", Variant::Type::StringOption, "getType", "setType");
		CLASS_REGISTER_PROPERTY(Box2DBody, "Restitution", Variant::Type::Real, "getRestitution", "setRestitution");
	}

	// update
	void Box2DBody::update_self()
	{
		if (m_isEnable && !m_body)
		{
			float pixelsPerUnit = Box2DWorld::instance()->getPixelsPerMeter();

			// create fixture
			b2FixtureDef* fixDef = EchoNew(b2FixtureDef);
			fixDef->density = 1.0;
			fixDef->friction = 1.0;
			fixDef->restitution = m_restitution;

			// set fixture shape
			b2PolygonShape* shape = EchoNew(b2PolygonShape);
			shape->SetAsBox(4.f, 0.3f);
			fixDef->shape = shape;

			// create body
			b2BodyDef bodyDef;
			bodyDef.type = b2BodyType(m_type.getIdx());
			bodyDef.position.Set(getWorldPosition().x, getWorldPosition().y);
			bodyDef.userData = this;
			bodyDef.fixedRotation = true;
			bodyDef.position.Set(getWorldPosition().x / pixelsPerUnit, getWorldPosition().y / pixelsPerUnit);
			m_body = Box2DWorld::instance()->getWorld()->CreateBody(&bodyDef);
			m_body->CreateFixture(fixDef);
		}

		if (m_body)
		{
			if (Engine::instance()->getConfig().m_isGame)
			{
				float pixelsPerUnit = Box2DWorld::instance()->getPixelsPerMeter();

				const b2Vec2& pos = m_body->GetPosition();
				this->setWorldPosition(Vector3(pos.x * pixelsPerUnit, pos.y * pixelsPerUnit, getWorldPosition().z));
			}
			else
			{
				float pixelsPerUnit = Box2DWorld::instance()->getPixelsPerMeter();
				m_body->SetTransform( b2Vec2(getWorldPosition().x / pixelsPerUnit, getWorldPosition().y / pixelsPerUnit) , 0.f);
			}
		}
	}
}