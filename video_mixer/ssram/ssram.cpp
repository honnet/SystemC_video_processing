// ssram.cpp

#include "ssram.h"

void ssram::read_data(){
   data_out.write( ram_data[addr.read()] ); // actif à l'état bas
}

void ssram::write_data(){
   if (!wen_bar) ram_data[addr.read()] = data_in.read();
}


