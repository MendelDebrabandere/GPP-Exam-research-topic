#ifndef SECTOR
#define SECTOR



#include <bitset>

class Portal;

class Sector final
{
public:
	explicit Sector(const Elite::Vector2& center,
					std::vector<uint8>* costField);

	~Sector();

	// rule of 5 copypasta
	Sector(const Sector& other) = delete;
	Sector(Sector&& other) = delete;
	Sector& operator=(const Sector& other) = delete;
	Sector& operator=(Sector&& other) = delete;


	void Draw(bool drawEdged, bool drawCells, bool showPortals) const;
	void MakePortals(const std::vector<Sector*>& sectorPtrs);
	bool IsWall(int idx) const;
	Elite::Vector2 GetCenter() const;

	void Make1Portal(int otherSectorIdx, const Elite::Vector2& startPortalPos, const Elite::Vector2& endPortalPos);
private:
	static constexpr uint8 s_Cells{10};
	static constexpr uint8 s_CellSize{1};

	Elite::Vector2 m_Center{};

	//1 Byte per item, 255 = wall
	std::vector<uint8>* m_CostField{};
	//4 Bytes per item, float = total integrated cost, bitset[0] = active wavefront flag, bitset[1] = LOS flag
	std::vector<std::pair<float, std::bitset<2>>>* m_IntegrationField{};
	//2 Bytes per item, uint8_t = key for direction lookupTable, bitset[0] = pathable flag, bitset[1] = LOS flag
	std::vector<std::pair< uint8, std::bitset<2>>>* m_FlowField{};

	std::vector<Portal*> m_PortalsPtrs;

	std::vector<RigidBody*> m_RBptrs{};

	//std::vector<Portal> m_Portals;

	void TryToMakePortal(bool& IsMakingPortal, int myIdx, int otherSectorIdx, const Elite::Vector2& startPortalPos, const Elite::Vector2& endPortalPos, const std::vector<Sector*>& sectorPtrs);

};

#endif
