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

using namespace Base;
using namespace Utilities;
using namespace std;

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
	else
	{
		Log_Write(ILogger::LT_ERROR, 1, "Paddle Swpawn Point is required");
		return false;
	}
	return true;
}
