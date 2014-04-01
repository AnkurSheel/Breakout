//  *******************************************************************************************************************
//  Level   version:  1.0   Ankur Sheel  date: 2013/05/14
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#include "stdafx.h"
#include "Level.h"
#include "XMLNode.hxx"
#include "GameDirectories.h"
#include "ResCache.hxx"
#include "ResourceManager.hxx"
#include "ParamLoaders.hxx"
#include "Config.h"
#include "BaseEntity.h"
#include "EntityManager.hxx"
#include "GameOptions.h"
#include "TransformComponent.h"
#include "PhysicsComponent.h"
#include "BaseEntity.h"

using namespace Base;
using namespace Utilities;
using namespace std;
using namespace GameBase;

cLevel cLevel::Level;

//  *******************************************************************************************************************
cLevel::cLevel()
	: m_pParamLoader(NULL)
	, m_TotalBricks(0)
{
}

//  *******************************************************************************************************************
cLevel::~cLevel()
{
	SafeDelete(&m_pParamLoader);
}

//  *******************************************************************************************************************
bool cLevel::Initialize(const cString & LevelName)
{
	if (LevelName.IsEmpty())
	{
		Log_Write(ILogger::LT_ERROR, 1, "Level Name is empty");
		return false;
	}

	IResource * pResource = IResource::CreateResource(cGameDirectories::GetDesignDirectory() + LevelName + ".lvl");
	shared_ptr<IResHandle> pLevelFile = IResourceManager::GetInstance()->VGetResourceCache()->GetHandle(*pResource);
	shared_ptr<IXMLNode> pRoot;
	SafeDelete(&pResource);
	if(pLevelFile != NULL)
	{
		if(m_pParamLoader == NULL)
		{
			m_pParamLoader = IParamLoader::CreateParamLoader();
			m_pParamLoader->VLoadParametersFromBuffer(pLevelFile->GetBuffer());
		}
	}
	else
	{
		return false;
	}


	m_TotalBricks = 0;

	vector<float> vPaddleSpawnPoint;
	m_pParamLoader->VGetParameterValueAsFloatList("-PaddleSpawnPoint", vPaddleSpawnPoint);
	if(!vPaddleSpawnPoint.empty() && vPaddleSpawnPoint.size() == 2)
	{
		m_PaddleSpawnPoint = cVector3(vPaddleSpawnPoint[0], vPaddleSpawnPoint[1], 0.0f);
	}

	vector<float> vBrickArea;
	m_pParamLoader->VGetParameterValueAsFloatList("-BrickMapSize", vBrickArea);
	if(!vBrickArea.empty() && vBrickArea.size() == 2)
	{
		m_BrickMapSize = cVector3(vBrickArea[0], vBrickArea[1], 0.0f);
	}
	
	AddWalls();
	GenerateMap();

	return true;
}

//  *******************************************************************************************************************
void cLevel::GenerateMap()
{
	float MapHt = m_pParamLoader->VGetParameterValueAsFloat("-MapHtAsScreenFraction", 0.3f);
	
	cVector3 BrickScale;
	BrickScale.x = cGameOptions::GameOptions().iWidth / m_BrickMapSize.y;
	BrickScale.y = cGameOptions::GameOptions().iHeight * MapHt / m_BrickMapSize.x;

	cBaseEntity * pEntity = NULL; 
	cVector3 curPos;

	for(int i = 0; i < m_BrickMapSize.y; i++)
	{
		curPos.x = i * BrickScale.x;
		for(int j = 0; j < m_BrickMapSize.x; j++)
		{
			curPos.y = j * BrickScale.y;
			pEntity = dynamic_cast<cBaseEntity *>(IEntityManager::GetInstance()->VAddEntity("basebrick"));
			if (pEntity != NULL)
			{
				pEntity->VInitialize();
				cTransformComponent * pTransFormComponent = dynamic_cast<cTransformComponent *>(pEntity->GetComponent(cTransformComponent::GetName().GetHash()));
				if(pTransFormComponent != NULL)
				{
					pTransFormComponent->SetPosition(curPos);
					pTransFormComponent->SetSize(BrickScale);
				}
				pEntity->VOnInitialized();
				m_TotalBricks++;
			}
		}
	}
}

//  *******************************************************************************************************************
void cLevel::AddWalls()
{
	cVector3 BrickScale;
	BrickScale.x = 20;
	BrickScale.y = cGameOptions::GameOptions().iHeight;

	// left wall
	cBaseEntity * pEntity = dynamic_cast<cBaseEntity *>(IEntityManager::GetInstance()->VAddEntity("wall"));
	if (pEntity != NULL)
	{
		cTransformComponent * pTransFormComponent = dynamic_cast<cTransformComponent *>(pEntity->GetComponent(cTransformComponent::GetName().GetHash()));
		if(pTransFormComponent != NULL)
		{
			pTransFormComponent->SetPosition(cVector3(-15.0f, 0.0f, 0.0f));
			pTransFormComponent->SetSize(BrickScale);
		}
		pEntity->VOnInitialized();
	}

	// right wall
	pEntity = dynamic_cast<cBaseEntity *>(IEntityManager::GetInstance()->VAddEntity("wall"));
	if (pEntity != NULL)
	{
		pEntity->VInitialize();
		cTransformComponent * pTransFormComponent = dynamic_cast<cTransformComponent *>(pEntity->GetComponent(cTransformComponent::GetName().GetHash()));
		if(pTransFormComponent != NULL)
		{
			pTransFormComponent->SetPosition(cVector3(cGameOptions::GameOptions().iWidth - 5.0f, 0.0f, 0.0f));
			pTransFormComponent->SetSize(BrickScale);
		}
		pEntity->VOnInitialized();
	}

	//bottom wall
	pEntity = dynamic_cast<cBaseEntity *>(IEntityManager::GetInstance()->VAddEntity("wall"));
	if (pEntity != NULL)
	{
		pEntity->VInitialize();
		cTransformComponent * pTransFormComponent = dynamic_cast<cTransformComponent *>(pEntity->GetComponent(cTransformComponent::GetName().GetHash()));
		if(pTransFormComponent != NULL)
		{
			pTransFormComponent->SetPosition(cVector3(7.0f, cGameOptions::GameOptions().iHeight-5.0f, 0.0f));
			pTransFormComponent->SetSize(cVector3(cGameOptions::GameOptions().iWidth-15.0f, 20.0f, 0.0f));
		}

		cPhysicsComponent * pPhysicsComponent = dynamic_cast<cPhysicsComponent *>(pEntity->GetComponent(cPhysicsComponent::GetName().GetHash()));
		if(pTransFormComponent != NULL)
		{
			pPhysicsComponent->SetAsTrigger(true);
		}
		pEntity->VOnInitialized();
	}

	//top wall
	pEntity = dynamic_cast<cBaseEntity *>(IEntityManager::GetInstance()->VAddEntity("wall"));
	if (pEntity != NULL)
	{
		pEntity->VInitialize();
		cTransformComponent * pTransFormComponent = dynamic_cast<cTransformComponent *>(pEntity->GetComponent(cTransformComponent::GetName().GetHash()));
		if(pTransFormComponent != NULL)
		{
			pTransFormComponent->SetPosition(cVector3(7.0f, -15.0f, 0.0f));
			pTransFormComponent->SetSize(cVector3(cGameOptions::GameOptions().iWidth-15.0f, 20.0f, 0.0f));
		}
		pEntity->VOnInitialized();
	}
}
