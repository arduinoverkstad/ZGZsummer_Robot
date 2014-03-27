#include "IRremote.h"
#include "IRremoteTools.h"
#include <Arduino.h>

IRrecv * irrecv=(IRrecv*)malloc(sizeof(IRrecv));
decode_results results; // container for received IR codes

void beginIRremote(int recvpin){
	irrecv=&IRrecv(recvpin);
	irrecv->enableIRIn(); // Start the receiver
}

bool IRrecived(){
	return irrecv->decode(&results);
}

void resumeIRremote(){
    irrecv->resume(); // resume receiver
}

unsigned long getIRresult(){
	return results.value;
}

