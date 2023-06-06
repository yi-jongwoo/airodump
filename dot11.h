#include "proto_structures.h"

// radio tap header | beacon frame
// BSSID, Beacons, (#Data), (ENC), ESSID
// PWR?
struct __attribute__((packed)) beacon_frame{
	uint8_t beacon;
	ignore_bytes(15);
	mac_addr bssid;
	ignore_bytes(14);
	char tag[0];
	bool is_beacon();
	std::string essid();
	std::string enc();
};
struct __attribute__((packed)) dot11{
	uint8_t data[0];
	ignore_bytes(2);
	uint16_t rth_len;
	uint32_t bitmask;
	uint8_t data2[0];
	uint8_t pwr();
	beacon_frame* bf();
};

