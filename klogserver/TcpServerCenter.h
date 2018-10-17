#pragma once
class TcpServerCenter
{
public:
	TcpServerCenter();
	~TcpServerCenter();
	static TcpServerCenter& instance();

public:
	int Run(bool async);
};

