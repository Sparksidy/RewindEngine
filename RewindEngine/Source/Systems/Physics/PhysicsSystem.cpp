#include <precompiled.h>

#include <Engine/Engine.h>
#include <Engine/GameObject.h>
#include <Systems/Physics/PhysicsSystem.h>
#include <Systems/Core/TransformComponent.h>
#include <Systems/Physics/RigidbodyComponent.h>


PhysicsSystem::PhysicsSystem()
{

}

PhysicsSystem::~PhysicsSystem()
{

}

bool PhysicsSystem::Initialize()
{
	math::vec2<> newGravity(0, -1.2);
	gravity = newGravity;
	return true;
}

bool PhysicsSystem::StaticPointToStaticCircle(math::vec2<> Point, math::vec2<> CircleCenter, float Radius)
{
	return (Point.squaredDistance(CircleCenter) <= Radius * Radius) ? true : false;
}

bool PhysicsSystem::StaticPointToStaticRect(math::vec2<> Point, math::vec2<> RectCenter, float Width, float Height)
{
	return ((RectCenter.x - Width / 2 <= Point.x && RectCenter.x + Width / 2 >= Point.x) && (RectCenter.y - Height / 2 <= Point.y && RectCenter.y + Height / 2 >= Point.y)) ? true : false;
}

bool PhysicsSystem::StaticCircleToStaticCircle(math::vec2<> CircleCenter0, float Radius0, math::vec2<> CircleCenter1, float Radius1)
{
	return (CircleCenter0.squaredDistance(CircleCenter1) <= (Radius0 + Radius1) * (Radius0 + Radius1)) ? true : false;
}

bool PhysicsSystem::StaticRectToStaticRect(math::vec2<> RectCenter0, float Width0, float Height0, math::vec2<> RectCenter1, float Width1, float Height1)
{
	return (RectCenter0.x - Width0 / 2 <= RectCenter1.x + Width1 / 2 && RectCenter0.x + Width0 / 2 >= RectCenter1.x - Width1 / 2 && RectCenter0.y - Height0 / 2 <= RectCenter1.y + Height1 / 2 && RectCenter0.y + Height0 / 2 >= RectCenter1.y - Height1 / 2) ? true : false;
}

bool PhysicsSystem::StaticCircleToStaticRectangle(math::vec2<> CircleCenter, float Radius, math::vec2<> RectCenter, float Width, float Height)
{
	math::vec2<> p = CircleCenter;
	if (p.x > RectCenter.x + Width / 2)
		p.x = RectCenter.x + Width / 2;
	else if (p.x < RectCenter.x - Width / 2)
		p.x = RectCenter.x - Width / 2;

	if (p.y > RectCenter.y + Height / 2)
		p.y = RectCenter.y + Height / 2;
	else if (p.y < RectCenter.y - Height / 2)
		p.y = RectCenter.y - Height / 2;

	float squaredDistance;
	squaredDistance = p.squaredDistance(CircleCenter);

	if (squaredDistance <= Radius * Radius)
		return true;
	else
		return false;
}

void PhysicsSystem::Update(float dt)
{
	static GameObjectManager * gameObjectManager = dynamic_cast<GameObjectManager*>(Engine::GetEngineSingleton().GetSystem("GameObjectManager"));

	for (auto gameObject : gameObjectManager->m_gameObjects)
	{
		TransformComponent * transform = (TransformComponent*)gameObject->GetComponent(TRANSFORM_COMPONENT);
		if (!transform)
			continue;
		RigidbodyComponent * rigidbody = (RigidbodyComponent*)gameObject->GetComponent(RIGIDBODY_COMPONENT);
		if (!rigidbody)
			continue;

		math::vec2<> pos = transform->GetTranslation();
		math::vec2<> vel = rigidbody->GetVelocity();

		vel += (gravity + math::vec2<>(0,rigidbody->GetAcceleration())) * dt * rigidbody->GetMass() * (int)rigidbody->m_enableGravity;
		rigidbody->SetAcceleration(rigidbody->GetAcceleration()*0.7);
		rigidbody->SetVelocity(vel);
		transform->SetTranslation(pos + vel * dt * rigidbody->GetMass() * (int)rigidbody->m_enableGravity);

		if (rigidbody->m_hasCollision)
			for (auto curr_gameObject : gameObjectManager->m_gameObjects)
			{
				if (curr_gameObject == gameObject)
					continue;

				TransformComponent * curr_transform = (TransformComponent*)curr_gameObject->GetComponent(TRANSFORM_COMPONENT);
				if (!curr_transform)
					continue;
				RigidbodyComponent * curr_rigidbody = (RigidbodyComponent*)curr_gameObject->GetComponent(RIGIDBODY_COMPONENT);
				if (!curr_rigidbody)
					continue;

				math::vec2<> curr_pos = curr_transform->GetTranslation();
				math::vec2<> curr_vel = curr_rigidbody->GetVelocity();

				if (StaticRectToStaticRect(curr_pos, curr_transform->GetScale().x * curr_rigidbody->GetColliderScale().x, curr_transform->GetScale().y * curr_rigidbody->GetColliderScale().y, pos, transform->GetScale().x * rigidbody->GetColliderScale().x, transform->GetScale().y * rigidbody->GetColliderScale().y))
				{
					rigidbody->SetVelocity(math::vec2<>());
					curr_rigidbody->SetVelocity(math::vec2<>());

					float mass1 = rigidbody->GetMass();
					float mass2 = curr_rigidbody->GetMass();
					
					math::vec2<> rv;
					math::vec2<> normal;

					rv = curr_vel - vel;
					normal = curr_pos - pos;

					float velocityAlongNormal = normal.dotProduct(rv);

					//std::cout << velocityAlongNormal << std::endl;

					if (velocityAlongNormal > 0)
						continue;

					float j = 0.00001*velocityAlongNormal;
					j /= 1 / rigidbody->GetMass() + 1 / curr_rigidbody->GetMass();

					math::vec2<> impulse;
					math::vec2<> impulse1;
					math::vec2<> impulse2;
					impulse = normal * j;

					impulse1 = impulse * (1 / mass1);
					impulse2 = impulse * (1 / mass2);

					rigidbody->SetVelocity(vel + impulse1);
					curr_rigidbody->SetVelocity(curr_vel - impulse2);

					//position correction due to floating point error

					const float percent = 0.2;
					math::vec2<> correction = normal * (0.0001 / (1 / mass1 + 1 / mass2)) * percent;
					math::vec2<> correction1 = correction * (1 / mass1) + pos;
					math::vec2<> correction2 = correction * (1 / mass1) - curr_pos;
					transform->SetTranslation(correction1);
					curr_transform->SetTranslation(correction2);
				}
			}
	}
}

void PhysicsSystem::Unload()
{
}

void PhysicsSystem::ReceiveMessage(Message * msg)
{
}


std::string PhysicsSystem::GetName() const
{
	return "Physics";
}

void PhysicsSystem::SetGravity(math::vec2<> const & newGravity)
{
	gravity = newGravity;
}

math::vec2<> const & PhysicsSystem::GetGravity() const
{
	return gravity;
}

void PhysicsSystem::RegisterToLua(luabridge::lua_State* L)
{
	RigidbodyComponent::RegisterToLua(L);
	
	getGlobalNamespace(L)
		.beginClass<PhysicsSystem>("PhysicsSystem")
			.addFunction("StaticPointToStaticCircle", &PhysicsSystem::StaticPointToStaticCircle)
			.addFunction("StaticPointToStaticRect", &PhysicsSystem::StaticPointToStaticRect)
			.addFunction("StaticCircleToStaticCircle", &PhysicsSystem::StaticCircleToStaticCircle)
			.addFunction("StaticRectToStaticRect", &PhysicsSystem::StaticRectToStaticRect)
			.addFunction("StaticCircleToStaticRectangle", &PhysicsSystem::StaticCircleToStaticRectangle)
		.endClass();

}
