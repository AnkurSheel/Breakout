// *****************************************************************************
//  Level   version:  1.0   Ankur Sheel  date: 2013/05/14
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef Level_h__
#define Level_h__

#include "vector3.h"

namespace Utilities
{
	class IParamLoader;
}

class cLevel
	: public Base::cNonCopyable
{
public:
	bool Initialize(const Base::cString & LevelName);
	Base::cVector3 GetPaddleSpawnPoint() const { return m_PaddleSpawnPoint; }

public:
	static cLevel Level;

private:
	cLevel();
	~cLevel();
	void GenerateMap();
	void AddWalls();
private:
	Base::cString				m_Background;
	Utilities::IParamLoader *	m_pParamLoader;
	Base::cVector3				m_PaddleSpawnPoint;
	Base::cVector3				m_BrickMapSize;
};
#endif // Level_h__