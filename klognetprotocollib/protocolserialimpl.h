#include "protocolserial.h"

class ProtocolSerial : public IProtocolSerial
{
public:
	ProtocolSerial(void);
	virtual ~ProtocolSerial(void);

public:
	virtual int Serial(const string& serial, SendKlogConfig& object) override;
	virtual int Serial(const SendKlogConfig& object, string& serial) override;
	virtual int Serial(const string& serial, GetKlogConfig& object) override;
	virtual int Serial(const GetKlogConfig& object, string& serial) override;
	virtual int Serial(const string& serial, SendKlogMessage& object) override;
	virtual int Serial(const SendKlogMessage& object, string& serial) override;
	virtual int Serial(const string& serial, GetKlogMessage& object) override;
	virtual int Serial(const GetKlogMessage& object, string& serial) override;
};