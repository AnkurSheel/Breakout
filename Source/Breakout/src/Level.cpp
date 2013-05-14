// *****************************************************************************
//  Level   version:  1.0   Ankur Sheel  date: 2013/05/14
// *****************************************************************************
//  purpose:	
// *****************************************************************************
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
#include "BaseBrick.h"
#include "transform2dComponent.h"

using namespace Base;
using namespace Utilities;
using namespace std;
using namespace GameBase;

cLevel cLevel::Level;

// *****************************************************************************
cLevel::cLevel()
	: m_pParamLoader(NULL)
{
}

// *****************************************************************************
cLevel::~cLevel()
{
	SafeDelete(&m_pParamLoader);
}

// *****************************************************************************
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

	vector<float> vPaddleSpawnPoint;
	m_pParamLoader->VGetParameterValueAsFloatList("-PaddleSpawnPoint", vPaddleSpawnPoint);
	if(!vPaddleSpawnPoint.empty() && vPaddleSpawnPoint.size() == 2)
	{
		m_PaddleSpawnPoint = cVector2(vPaddleSpawnPoint[0], vPaddleSpawnPoint[1]);
	}

	vector<float> vBrickArea;
	m_pParamLoader->VGetParameterValueAsFloatList("-BrickMapSize", vBrickArea);
	if(!vBrickArea.empty() && vBrickArea.size() == 2)
	{
		m_BrickMapSize = cVector2(vBrickArea[0], vBrickArea[1]);
	}
	GenerateMap();
	return true;
}

// *****************************************************************************
void cLevel::GenerateMap()
{
	const cEntityDef * const pEntityDef = cConfig::GetEntityDef(cBaseBrick::m_Name);
	cVector2 BrickScale;
	BrickScale.x = cGameOptions::GameOptions().iWidth / m_BrickMapSize.x;
	BrickScale.y = cGameOptions::GameOptions().iHeight * 0.3f / m_BrickMapSize.y;

	cBaseBrick * pEntity = NULL; 
	cVector2 curPos;

	for(int i = 0; i < m_BrickMapSize.y; i++)
	{
		curPos.y = i * BrickScale.x + 20;
		for(int j = 0; j < m_BrickMapSize.x; j++)
		{
			curPos.y = j * BrickScale.y + 20;
			pEntity = dynamic_cast<cBaseBrick *>(IEntityManager::GetInstance()->VRegisterEntity("basebrick"));
			if (pEntity != NULL)
			{
				pEntity->VInitialize();
				cTransform2DComponent * pTransFormComponent = dynamic_cast<cTransform2DComponent *>(pEntity->GetComponent(cTransform2DComponent::GetName().GetHash()));
				if(pTransFormComponent != NULL)
				{
					pTransFormComponent->m_vPosition = curPos;
					pTransFormComponent->m_vSize = BrickScale;
				}
			}
		}
	}
}
