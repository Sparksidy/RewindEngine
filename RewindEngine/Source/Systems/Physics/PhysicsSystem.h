#include <Systems/Core/ISystem.h>
#include <Utilities/math/vec2.h>
#include <Utilities/math/vec3.h>
#include <Systems/Core/GameObjectManager.h>

class PhysicsSystem : public ISystem
{

public:

	//constructors/destructor
	PhysicsSystem();
	virtual ~PhysicsSystem();

	bool StaticPointToStaticCircle(math::vec2<> Point, math::vec2<> CircleCenter, float Radius);
	bool StaticPointToStaticRect(math::vec2<> Point, math::vec2<> RectCenter, float Width, float Height);
	bool StaticCircleToStaticCircle(math::vec2<> CircleCenter0, float Radius0, math::vec2<> CircleCenter1, float Radius1);
	bool StaticRectToStaticRect(math::vec2<> RectCenter0, float Width0, float Height0, math::vec2<> RectCenter1, float Width1, float Height1);
	bool StaticCircleToStaticRectangle(math::vec2<> CircleCenter, float Radius, math::vec2<> RectCenter, float Width, float Height);

	//ISystem Methods
	bool Initialize();
	void Update(float dt);
	void Unload();

	void ReceiveMessage(Message * msg);

	std::string GetName() const;

	void SetGravity(math::vec2<> const & newGravity);
	math::vec2<> const & GetGravity() const;

	static void RegisterToLua(luabridge::lua_State* L);

private:

	math::vec2<> gravity;
};

