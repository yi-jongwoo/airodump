#include "dot11.h"
uint8_t dot11::pwr(){
	static const int sz[]={8,1,1,2,2,1};
	int j=0;
	for(int i=0;i<5;i++)
		if(bitmask>>i&1)
			j+=sz[i];
	return data[j];
}
