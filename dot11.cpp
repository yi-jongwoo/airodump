#include "dot11.h"

bool beacon_frame::is_beacon(){
	return beacon==0x80;
	
}
std::string beacon_frame::essid(){
	if(tag[0])
		return std::string();
	return std::string(tag+2,tag[1]);
}
std::string beacon_frame::enc(int tlen){
	
	uint8_t* it=(uint8_t*)tag;
	while(((int8_t*)it-(int8_t*)tag)<tlen&&it[0]!=0x30){
		it+=2+it[1];
	}
	if(it[0]!=0x30)return "NULL";

	int x=*(uint16_t*)(it+8);
	switch(it[15+4*x]){
		case 1:return "WPA ";
		case 2:return "WPA2";
	}
	return "UNKN";
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
