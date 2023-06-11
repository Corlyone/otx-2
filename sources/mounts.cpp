#include "otpch.h"
#include "mounts.h"
#include "tools.h"

bool Mounts::parseMountNode(xmlNodePtr p) {
	if (xmlStrcmp(p->name, (const xmlChar*)"mount"))
		return false;

	int32_t intValue;
	std::string strValue;

	if (!readXMLInteger(p, "id", intValue)) {
		std::clog << "[Error - Mounts::parseMountNode] Missing mount id." << std::endl;
		return false;
	}

	uint16_t id = intValue, clientId = 0;
	std::string name;
	bool premium = false;

	if (readXMLInteger(p, "clientid", intValue)) {
		clientId = intValue;
	}

	if (!readXMLString(p, "name", strValue)) {
		std::stringstream ss;
		ss << "Mount #" << id;
		name = ss.str();
	} else {
		name = strValue;
	}

	if (readXMLString(p, "premium", strValue)) {
		premium = booleanString(strValue);
	}

	Mount newMount(
		id,
		clientId,
		name,
		premium
	);
	mounts.push_back(newMount);

	return true;
}

bool Mounts::loadFromXml() {
	xmlDocPtr doc = xmlParseFile(getFilePath(FILE_TYPE_XML, "mounts.xml").c_str());
	if (!doc) {
		std::clog << "[Warning - Mounts::loadFromXml] Cannot load mounts file." << std::endl << getLastXMLError() << std::endl;
		return false;
	}

	xmlNodePtr p, root = xmlDocGetRootElement(doc);
	if (xmlStrcmp(root->name, (const xmlChar*)"mounts")) {
		std::clog << "[Error - Mounts::loadFromXml] Malformed mounts file." << std::endl;
		xmlFreeDoc(doc);
		return false;
	}

	p = root->children;

	while (p) {
		parseMountNode(p);
		p = p->next;
	}

	xmlFreeDoc(doc);
	return true;
}

Mount* Mounts::getMountByID(uint8_t id) {
	for (std::vector<Mount>::iterator it = mounts.begin(); it != mounts.end(); ++it) {
		if (it->id == id) {
			return &*it;
		}
	}

	return NULL;
}

Mount* Mounts::getMountByClientID(uint16_t clientId) {
	for (std::vector<Mount>::iterator it = mounts.begin(); it != mounts.end(); ++it) {
		if (it->clientId == clientId) {
			return &*it;
		}
	}

	return NULL;
}

uint16_t Mounts::getDressedMount(uint16_t clientId, uint16_t outfitId) {
	if (clientId == 0) {
		return 0;
	}

	return 0;
}
