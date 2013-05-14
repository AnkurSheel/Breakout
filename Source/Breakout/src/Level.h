// *****************************************************************************
//  Level   version:  1.0   Ankur Sheel  date: 2013/05/14
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef Level_h__
#define Level_h__

#include "vector2.h"

namespace Utilities
{
	class IParamLoader;
}

class cLevel
	: public Base::cNonCopyable
{
public:
	bool Initialize(const Base::cString & LevelName);
	Base::cVector2 GetPaddleSpawnPoint() const { return m_PaddleSpawnPoint; }
	Base::cVector2 GetBrickMapSize() const { return m_BrickMapSize; }

public:
	static cLevel Level;

private:
	cLevel();
	~cLevel();
	void GenerateMap();

private:
	Base::cString				m_Background;
	Utilities::IParamLoader *	m_pParamLoader;
	Base::cVector2				m_PaddleSpawnPoint;
	Base::cVector2				m_BrickMapSize;
};
#endif // Level_h__