#pragma once
#include "Model.h"
#include "WorldTransform.h"

enum class MapChipType { 
	kBlank,
	kBlock,
};

struct MapChipData {
	std::vector<std::vector<MapChipType>> data;
 };

class MapChipField {
public:

	void ResetMapChipData();
	void LoadMapChipCsv(const std::string& filePath);
	MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);
	Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);

	static inline const uint32_t GetNumBlockVirtical() { return kNumBlockVirtical; }
	static inline const uint32_t GetNumBlockHorizontal() { return kNumBlockHorizontal; }


private:

	MapChipData mapChipData_;
	//1ブロックのさいず
	static inline const float kBlockWidth = 1.0f;
	static inline const float kBlockHeight = 1.0f;
	//個数
	static inline const uint32_t kNumBlockVirtical = 20;
	static inline const uint32_t kNumBlockHorizontal = 100;
};
