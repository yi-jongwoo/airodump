#include "dot11.h"

bool beacon_frame::is_beacon(){
	return beacon==0x80;
	
}
std::string beacon_frame::essid(){
	if(tag[0])
		return std::string();
	return std::string(tag+2,tag[1]);
}
uint8_t dot11::pwr(){
	static const int sz[]={8,1,1,2,2,1};
	int j=0;
	for(int i=0;i<5;i++)
		if(bitmask>>i&1)
			j+=sz[i];
	for(int i=0;i<5;i++)
		std::cout<<std::hex<<(int)data2[j+i]<<' ';
	std::cout<<std::endl;
	return data2[j];
}
beacon_frame* dot11::bf(){
	return (beacon_frame*)(data+rth_len);
}
