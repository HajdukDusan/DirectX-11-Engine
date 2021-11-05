#ifndef _ASSETMANAGER_H_
#define _ASSETMANAGER_H_

#pragma once
#include <vector>
#include "Asset.h"

using namespace std;

class AssetManager
{
public:
	AssetManager();
	~AssetManager();

	vector<Asset*> m_Assets;
};

#endif

