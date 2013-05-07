// *****************************************************************************
//  BreakOutEntityFactory   version:  1.0   Ankur Sheel  date: 2013/05/06
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#include "StdAfx.h"
#include "BreakOutEntityFactory.h"
#include "Paddle.h"
#include "XMLNode.hxx"
#include "EntityManager.hxx"
#include "BaseComponent.hxx"

using namespace GameBase;
using namespace Base;
using namespace Utilities;

// *****************************************************************************
cBreakOutEntityFactory::cBreakOutEntityFactory()
{
	if(m_pInstance == NULL)
		m_pInstance = this;
}

// *****************************************************************************
cBreakOutEntityFactory::~cBreakOutEntityFactory()
{
}

// *****************************************************************************
void cBreakOutEntityFactory::RegisterEntities()
{
	m_RegisteredEntities.Register<cPaddle>(cPaddle::m_Name.GetHash());
}

// *****************************************************************************
IBaseEntity * cBreakOutEntityFactory::VCreateEntity(const cHashedString & Type)
{
	IBaseEntity * pEntity = m_RegisteredEntities.Create(Type.GetHash());
	if(pEntity != NULL)
	{
		const shared_ptr<IXMLNode> pRoot = IXMLNode::Load("Paddle.xml");
		Log_Write(ILogger::LT_COMMENT, 1, "Element Name : " + pRoot->VGetName() );
		Log_Write(ILogger::LT_COMMENT, 1, "Element Type : " + pRoot->VGetNodeAttribute("type"));

		IXMLNode::XMLNodeList List;
		pRoot->VGetChildren(List);
		IXMLNode::XMLNodeList::iterator Iter;
		for (Iter = List.begin(); Iter != List.end(); Iter++)
		{
			IXMLNode * pNode = (*Iter).get();
			Log_Write(ILogger::LT_COMMENT, 1, "Element Name : " + pNode->VGetName() );
			IBaseComponent * pComponent = m_RegisteredComponents.Create(cHashedString::CalculateHash(pNode->VGetName().GetInLowerCase()));
			if(pComponent != NULL)
			{
				pComponent->VInitialize(pNode);
				IEntityManager::GetInstance()->VAddComponent(pEntity, pComponent);
			}
			//       if (pComponent)
			//       {
			//           pActor->AddComponent(pComponent);
			//           pComponent->SetOwner(pActor);
			//       }
			//       else
			//       {
			//           // If an error occurs, we kill the actor and bail.  We could keep going, but the actor is will only be 
			//           // partially complete so it's not worth it.  Note that the pActor instance will be destroyed because it
			//           // will fall out of scope with nothing else pointing to it.
			//           return StrongActorPtr();
			//       }
		}

		pEntity->VInitialize();
	}
	return pEntity;
}