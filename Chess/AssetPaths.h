#pragma once
#include <unordered_map>

class AssetPaths
{
private:
	static const std::unordered_map<std::string, std::string> m_AssetPaths;

public:
	const std::string* getAssetPath(const std::string& requestedAsset) const;
	~AssetPaths();
};

