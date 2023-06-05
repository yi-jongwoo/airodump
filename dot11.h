#include "proto_structures.h"

// radio tap header | beacon frame
// BSSID, Beacons, (#Data), (ENC), ESSID
// PWR?
struct __attribute__((packed)) dot11{
	ignore_bytes(2);
	uint16_t rth_len;
	uint32_t bitmask;
	uint8_t data[0];
	uint8_t pwr();
};
struct __attribute__((packed)) beacon_frame{
	uint8_t beacon;
};
