#include "SERIALRead.h"

SERIALReader::SERIALReader(std::string portname, int baud_rate):
_io(),_serial(_io, portname)
{
  cout<<"OpenPort"<<endl;
  this->_baud_rate=baud_rate;
  this->_portname=portname;
  _serial.set_option(boost::asio::serial_port_base::baud_rate(baud_rate));
  sleep(2);
  cout<<"Port is opened"<<endl;
}

string SERIALReader::_getFloatSignal(){
  char c;
  std::string result;
  bool getFlag=true;
  while(getFlag){
    read(_serial,buffer(&c,1));
    switch(c){
      case '\r':
        break;
      case '\n':
        getFlag=false;
        break;
      default:
        result+=c;
      }
    }
    return result;
}

vector <string> SERIALReader::_splitLine(string line, string splitter){
    vector <string> sen;
    char* cline = new char[line.length()+1];
    strcpy(cline,line.c_str());
    char* token = strtok(cline, splitter.c_str());
    while(token != NULL){
        string s(token);
        sen.push_back(s);
        token=strtok(NULL,splitter.c_str());
    }
    free(cline);
    free(token);
    return sen;
}

  vector<float> SERIALReader::getSignalForInterval(){
  string val=_getFloatSignal();
  vector<float> speeds;
  for(int i=0;i<4;i++){
    speeds.push_back(0.0);
  }
  vector<string> sp=_splitLine(val," ");

  try{
    for(int i=0;i<sp.size();i++){
      speeds[i]=atof(sp[i].c_str());
    }
  }catch(const std::exception& e){
    std::perror("connection lost");
  }

  return speeds;
}
