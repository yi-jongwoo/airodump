#include "dot11.h"

bool beacon_frame::is_beacon(){
	return beacon==0x80;
	
}
std::string beacon_frame::essid(){
	if(tag[0])
		return std::string();
	return std::string(tag+2,tag[1]);
}
std::string beacon_frame::enc(){
	uint8_t* it=(uint8_t*)tag;
	while(it[0]!=0x30){
		it+=2+it[1];
	}
	return it[2]==1?"WPA ":"WPA2";
}
uint8_t dot11::pwr(){
	static const int sz[]={8,1,1,4,2,1};
	int j=(bitmask>>31)*4;
	for(int i=0;i<5;i++)
		if(bitmask>>i&1)
			j+=sz[i];
	return data2[j];
}
beacon_frame* dot11::bf(){
	return (beacon_frame*)(data+rth_len);
}
