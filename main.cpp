#include "dot11.h"
#include "addr_set.h"
#include <pcap.h>
#include <iostream>
#include <cstdlib>
#include <map>
#include <tuple>
#include <thread>
#include <mutex>
#include <unistd.h>
using std::cout;
using std::endl;

std::map<addr_set<mac_addr>,std::tuple<int,int,int,std::string,std::string>> L;
std::mutex ex;

std::string int5(int a){
	std::string res;
	res.push_back(a/10000%10+'0');
	res.push_back(a/1000%10+'0');
	res.push_back(a/100%10+'0');
	res.push_back(a/10%10+'0');
	res.push_back(a%10+'0');
	return res;
}

void prn(){
	for(;;){
		sleep(1);
		ex.lock();
		system("clear");
		cout<<"BSSID             POWER #BEACON #DATA ENC  NAME\n";
		for(auto[bs,ext]:L)
			cout<<(std::string)(mac_addr)bs<<' '
			<<get<0>(ext)<<"   "
			<<int5(get<1>(ext))<<"   "
			<<int5(get<2>(ext))<<' '
			<<get<3>(ext)<<' '
			<<get<4>(ext)<<' '
			<<endl;
		ex.unlock();
	}
}

void dot11parse(dot11& packet){
	beacon_frame& bf=*packet.bf();
	mac_addr id=bf.bssid;
	int power=(int8_t)packet.pwr();
	if(!bf.is_beacon()){
		ex.lock();
		get<0>(L[id])=power;
		get<2>(L[id])++;
		ex.unlock();
		return;
	}
	std::string name=bf.essid();
	std::string enc=bf.enc();
	//cout<<name<<' '<<enc<<endl;
	ex.lock();
	get<0>(L[id])=power;
	get<1>(L[id])++;
	get<3>(L[id])=enc;
	get<4>(L[id])=name;
	ex.unlock();
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
	std::thread th(prn);
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
