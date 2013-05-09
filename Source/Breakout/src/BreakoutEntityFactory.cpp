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
#include "GameDirectories.h"
#include "ResCache.hxx"
#include "ResourceManager.hxx"

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
	cBaseEntity * pEntity = dynamic_cast<cBaseEntity *>(m_RegisteredEntities.Create(Type.GetHash()));
	if(pEntity != NULL)
	{
		IResource * pResource = IResource::CreateResource(cGameDirectories::GetDefDirectory() + "Entities.xml");
		shared_ptr<IResHandle> pXMLFile = IResourceManager::GetInstance()->VGetResourceCache()->GetHandle(*pResource);
		shared_ptr<IXMLNode> pRoot;
		SafeDelete(&pResource);
		if(pXMLFile != NULL)
		{
			pRoot = shared_ptr<IXMLNode>(IXMLNode::Parse(pXMLFile->GetBuffer(), pXMLFile->GetSize()));
		}

		if (pRoot == NULL)
		{
			Log_Write(ILogger::LT_ERROR, 1, cGameDirectories::GetDefDirectory() + "Entities.xml");
			return NULL;
		}

		shared_ptr<IXMLNode> pNode(pRoot->VGetChild(Type.GetString()));
		Log_Write(ILogger::LT_COMMENT, 1, "Element Name : " + pNode->VGetName() );

		IXMLNode::XMLNodeList List;
		pNode->VGetChildren(List);
		IXMLNode::XMLNodeList::iterator Iter;
		for (Iter = List.begin(); Iter != List.end(); Iter++)
		{
			pNode = (*Iter);
			Log_Write(ILogger::LT_COMMENT, 1, "Element Name : " + pNode->VGetName() );
			IBaseComponent * pComponent = m_RegisteredComponents.Create(cHashedString::CalculateHash(pNode->VGetName().GetInLowerCase()));
			if(pComponent != NULL)
			{
				pComponent->VInitialize(pNode.get());
				pEntity->AddComponent(pComponent);
			}
		}

		pEntity->VInitialize();
	}
	return pEntity;
}