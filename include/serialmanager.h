#ifndef SERIALMANAGER_H
#define SERIALMANAGER_H

class SerialManager {
public:
	void init(unsigned long baud);
	void printDebugInfo();
	void printMemInfo();
};

#endif // SERIALMANAGER_H
