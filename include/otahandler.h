#ifndef OTAHANDLER_H_
#define OTAHANDLER_H_

class OtaHandler {
	public:
		void begin(bool reboot);
		void handle();
};

#endif // OTAHANDLER_H_