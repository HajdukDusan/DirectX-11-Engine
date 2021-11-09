#ifndef _ASSETPANEL_H_
#define _ASSETPANEL_H_

#pragma once
#include <vector>
#include <string>
#include <thread>
#include <filesystem>

#include "../../Core/Renderer/DirectX/d3dclass.h"

using namespace std;

class AssetPanel
{
public:
	AssetPanel(D3DClass*);
	~AssetPanel();

	void Render();

	//filesystem::directory_iterator directoryFiles;
	vector<filesystem::directory_entry> directoryFiles;

private:

	filesystem::path m_CurrentDirectory;

	void UpdateDirectoryFilesLoop();
	void UpdateDirectoryFiles();
	thread updateThread;
};

#endif

