#ifndef OTAUPDATER_H
#define OTAUPDATER_H

class OtaUpdater {
public:
	void init(bool rebootOnSuccess);
	void handle();
};

#endif // OTAUPDATER_H
