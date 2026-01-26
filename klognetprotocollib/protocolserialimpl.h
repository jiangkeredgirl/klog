#include "protocolserial.h"

class ProtocolSerial : public IProtocolSerial
{
public:
	ProtocolSerial(void);
	virtual ~ProtocolSerial(void);

public:
	virtual int Serial(const string& serial, NetEvent& object) override;
	virtual int Serial(const NetEvent& object, string& serial) override;
	virtual int Serial(const string& serial, SendKlogClientTypeEvent& object) override;
	virtual int Serial(const SendKlogClientTypeEvent& object, string& serial) override;
	virtual int Serial(const string& serial, GetKlogServerPortEvent& object) override;
	virtual int Serial(const GetKlogServerPortEvent& object, string& serial) override;
	virtual int Serial(const string& serial, SendKlogServerPortEvent& object) override;
	virtual int Serial(const SendKlogServerPortEvent& object, string& serial) override;
	virtual int Serial(const string& serial, SendKlogConfigEvent& object) override;
	virtual int Serial(const SendKlogConfigEvent& object, string& serial) override;
	virtual int Serial(const string& serial, GetKlogConfigEvent& object) override;
	virtual int Serial(const GetKlogConfigEvent& object, string& serial) override;
	virtual int Serial(const string& serial, SendKlogMessageEvent& object) override;
	virtual int Serial(const SendKlogMessageEvent& object, string& serial) override;
	virtual int Serial(const string& serial, GetKlogMessageEvent& object) override;
	virtual int Serial(const GetKlogMessageEvent& object, string& serial) override;
};