#ifndef OTAHANDLER_H
#define OTAHANDLER_H

class OtaHandler {
	public:
		void begin(bool reboot);
		void handle();
};

#endif // OTAHANDLER_H