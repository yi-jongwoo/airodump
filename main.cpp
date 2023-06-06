#include "dot11.h"
#include <pcap.h>
#include <iostream>
#include <cstdlib>
using std::cout;
using std::endl;
void dot11parse(dot11& packet){
	uint8_t x=packet.pwr();
	cout<<(int)x<<endl;
}
int main(int c,char** v){
	if(c!=2){
		cout<<"usage : airodump <interface>"<<endl;
		exit(1);
	}
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t* handle=pcap_open_live(v[1],BUFSIZ,1,1,errbuf);
	if(handle==nullptr){
		std::cout<<"pcap error : "<<errbuf<<std::endl;
		exit(1);
	}
	for(;;){
		pcap_pkthdr* hdr;
		const uint8_t* ptr;
		if(!pcap_next_ex(handle,&hdr,&ptr)){
			printf("pcap listing failed\n");
			exit(1);
		}
		dot11parse(*(dot11*)ptr);
	}
}
