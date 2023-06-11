#ifndef __MOUNTS__
#define __MOUNTS__

struct Mount {
	Mount(uint8_t id, uint16_t clientId, std::string name, bool premium) :
		name(name), clientId(clientId), id(id), premium(premium) {}

	std::string name;
	uint16_t clientId;
	uint8_t id;
	bool premium;
};

class Mounts {
	public:
		virtual ~Mounts() {}
		static Mounts* getInstance() {
			static Mounts instance;
			return &instance;
		}

		bool loadFromXml();
		bool parseMountNode(xmlNodePtr p);
		Mount* getMountByID(uint8_t id);
		Mount* getMountByClientID(uint16_t clientId);
		uint16_t getDressedMount(uint16_t clientId, uint16_t outfitId);

		const std::vector<Mount>& getMounts() const {
			return mounts;
		}

	private:
		std::vector<Mount> mounts;
};

#endif
