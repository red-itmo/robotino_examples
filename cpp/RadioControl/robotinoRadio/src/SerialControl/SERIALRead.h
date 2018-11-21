#ifndef SERIALREAD_H
#define SERIALREAD_H

#include <string.h>
#include <boost/asio.hpp>
#include <boost/asio/read.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace boost::asio;

class SERIALReader{

public:
  SERIALReader(string portname, int baud_rate);
  vector<float> getSignalForInterval();
private:
  string _portname;
  int _baud_rate;
  io_service _io;
  serial_port _serial;
  string _getFloatSignal();
  vector <string> _splitLine(string line, string splitter);
};

#endif /*SERIALREAD_H*/
