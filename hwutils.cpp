#include "stdafx.h"
#include "hwutils.h"
#include <iostream>
#include <urlmon.h>
#include <string>
#include <wininet.h>
#include <locale>
#include <windows.h>


#include <sstream> 

#pragma comment(lib, "wininet")
#pragma comment(lib,"wininet.lib")
#pragma comment(lib, "urlmon.lib")

using namespace std;
bool HWID::HWID;
bool HWID::HWID1;
bool HWID::HWID2;
bool HWID::HWID3;
bool HWID::HWID4;
bool HWID::HWID5;
bool HWID::HWID6;
bool HWID::HWID7;
std::string ReadHWFile() {
	std::ifstream ifs("C:\\h.txt");
	std::string content((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));
	return content;
}
string serial() {
	DWORD  lVolSerialNbr = 0;
	char sHDSerial[255] = "";
	//nSize = sizeof(cUsername); 
	GetVolumeInformation("C:\\", 0, 0, &lVolSerialNbr, 0, 0, 0, 0); 
	_ultoa(lVolSerialNbr, sHDSerial, 10); 
	std::string c(sHDSerial); 
	return c;
}

int encrypt(float Xv, int Bv) {
	int x = Xv;
	int B = 3; Bv % 21;
	//int y = (((((((x) ^ 2)*2.7 - 44) + B*(x / 32.3) * 81 + cos(x) - sin(x ^ 3 + B)*B*x) / (421)) - x)*(2.3)*sin(x) + 2 * cos(x)*cos(x) - (B*x) / 3 + cos(x) * 13)*10;
	int y = (x * 3);
	return abs(y);
}
bool jakeschecks() {
	IStream* pStream = NULL;
	string var1 = ReadHWFile();
	string var2 = serial();
	int Xv = rand() % 40000;
	int Bv = (atoi(var2.c_str()));
	int encrypts = encrypt(Xv, Bv);

	string var3 = "1";
	string website = "http://server.elitesoftware.xyz/loader/server.php?var1=";
	website.append(var1).append("&var2=").append(var2).append("&var3=").append(var3).append("&var4=").append(to_string(Xv));
	LPCSTR lpcstr = website.c_str();
	//cout << website << endl;
	if (SUCCEEDED(URLOpenBlockingStream(0, lpcstr, &pStream, 0, 0))) {
		pStream->Release();
		HINTERNET connect = InternetOpen("MyBrowser", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);

		HINTERNET OpenAddress = InternetOpenUrl(connect, lpcstr, NULL, 0, INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_KEEP_CONNECTION, 0);

		if (!OpenAddress) {
			InternetCloseHandle(connect);
			return true;
		}
		char DataReceived[100];
		DWORD NumberOfBytesRead = 0;
		while (InternetReadFile(OpenAddress, DataReceived, 100, &NumberOfBytesRead) && NumberOfBytesRead) {}

		InternetCloseHandle(OpenAddress);
		InternetCloseHandle(connect);
		//cout << "DR " << DataReceived << endl;
		stringstream value;
		for (int i = 0; i < 20; i++) {
			if (DataReceived[i] == '0' || DataReceived[i] == '1' || DataReceived[i] == '2' || DataReceived[i] == '3' || DataReceived[i] == '4' || DataReceived[i] == '5' || DataReceived[i] == '6' || DataReceived[i] == '7' || DataReceived[i] == '8' || DataReceived[i] == '9')
				value << DataReceived[i];
		}
		string encc(value.str());
		int encryptedint;
		value >> encryptedint;
		//cout << encryptedint << endl;
		int decrypted = encryptedint;
		//cout << "De: " << (decrypted) << " Ekey: " << encrypts << endl;
		if (strstr(DataReceived, "7767")) {
			return true;
		}
		else {
			//Unhook_Cheat = true;
			//return false;
			
			return false;

		}
	

	}
	else {
		return true;

	}
	return true;
}

bool DoesHWIDMatch() {
	HINTERNET connect = InternetOpen("MyBrowser", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);

	if (!connect)
	{
		//return false;
		return false;
	}
	

	std::string URL = "https://rektcrew.xyz/rektcrew-dc/hwid_req.php?hwid=" + serial()+ "&secret=hyper421";
	LPCSTR Final = URL.c_str();

	HINTERNET OpenAddress = InternetOpenUrl(connect, Final, NULL, INTERNET_DEFAULT_HTTPS_PORT, INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_KEEP_CONNECTION, 0);

	if (!OpenAddress) {
		InternetCloseHandle(connect);
		//return false;
		return false;
	}

	char DataReceived[4096];
	DWORD NumberOfBytesRead = 0;
	while (InternetReadFile(OpenAddress, DataReceived, 4096, &NumberOfBytesRead) && NumberOfBytesRead) {}

	InternetCloseHandle(OpenAddress);
	InternetCloseHandle(connect);


		if (strstr(DataReceived, "OK_I9")) {
	//if(serial() == "3170025071") {
		//return false;
		return true;
	}
	else {
		Hacks.UnHook();
	}
	return false;
}

void HWIDCHECK() {
	if (DoesHWIDMatch()) {
		HWID::HWID = true;
		HWID::HWID1 = true;
		HWID::HWID2 = true;
		HWID::HWID3 = true;
		HWID::HWID4 = true;
		HWID::HWID5 = true;
		HWID::HWID6 = true;
		HWID::HWID7 = true;
	}
	else {
		HWID::HWID = false;
		HWID::HWID1 = rand() % 2;
		HWID::HWID2 = rand() % 2;
		HWID::HWID3 = rand() % 2;
		HWID::HWID4 = rand() % 2;
		HWID::HWID5 = rand() % 2;
		HWID::HWID6 = rand() % 2;
		HWID::HWID7 = rand() % 2;
	}
}