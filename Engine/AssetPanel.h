#ifndef _ASSETPANEL_H_
#define _ASSETPANEL_H_

#pragma once
#include <vector>
#include <string>
#include <thread>
#include <filesystem>

#include "Asset.h"
#include "d3dclass.h"

using namespace std;

class AssetPanel
{
public:
	AssetPanel(D3DClass*);
	~AssetPanel();

	void Render();

	vector<Asset*> m_Assets;

	//filesystem::directory_iterator directoryFiles;
	vector<pair<filesystem::path, bool>> directoryFiles;

private:

	filesystem::path m_CurrentDirectory;

	void UpdateDirectoryFilesLoop();
	void UpdateDirectoryFiles();
	thread updateThread;
};

#endif

