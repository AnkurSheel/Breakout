//  *******************************************************************************************************************
//  Physics version:  1.0   Ankur Sheel  date: 2013/06/06
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************

#ifndef Physics_hxx
#define Physics_hxx

#include "PhysicsDefines.h"

namespace Physics
{
	class IRigidBody;
	struct stRigidBodyDef;
}

namespace Physics
{
	typedef std::pair<int, int> CollisionPair;
	typedef std::set<CollisionPair> CollisionPairs;

	class IPhysics
	{
	public:
		virtual ~IPhysics() {}
		virtual void VInitialize(const Base::cString & FileName) = 0;
		virtual void VUpdate(const float DeltaTime) = 0;
		virtual IRigidBody * const VAddRigidBody(const int ID, shared_ptr<const stRigidBodyDef> pDef) = 0;
		virtual void VRemoveRigidBody(const int ID) = 0;
		virtual const CollisionPairs & VGetCollisionPairs() const = 0;
		virtual const CollisionPairs & VGetTriggerPairs() const = 0;
		virtual void VOnRigidBodyAdded(const int ID) = 0;
		PHYSICS_API static IPhysics * GetInstance();
		PHYSICS_API static void Destroy();
	};
}
#endif //Physics_hxx