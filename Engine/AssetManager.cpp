#include "AssetManager.h"

AssetManager::AssetManager()
{

}

AssetManager::~AssetManager()
{
	for (Asset* asset : m_Assets)
	{
		if (asset)
			delete asset;
	}
	m_Assets.clear();
}