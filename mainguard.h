#pragma once 
class get_information
{
public:
	virtual ~get_information() = 0 {}
	virtual std::string get_time(std::string host, std::string path) = 0;
	virtual std::string get_inject(std::string host, std::string path) = 0;
	virtual std::string get_download_url(std::string url, std::string host_gate_inject) = 0;
	virtual void gen_key(std::string login, std::string password) = 0;
	virtual std::string gen_token(std::string login, std::string password, std::string key, std::string url_time) = 0;
	virtual std::string get_gen_url(std::string host, std::string path, std::string host_gate_login, std::string user_name, std::string host_gate_password, std::string user_password,
		std::string host_gate_system_key, std::string generate_key, std::string host_gate_token, std::string get_token) = 0;

	virtual int URLDownloadBinary(LPCSTR lpszURL, BYTE **ppBuffer, DWORD *pdwSize) = 0;
};

class get_info : public get_information
{
public:
	auto get_time(std::string host, std::string path) -> std::string
	{
		std::string url_time = "";
		return url_time = host + path + "time.php";
	}


	auto get_download_url(std::string url, std::string host_gate_inject)-> std::string
	{
		std::string download_dll = "http://" + url + host_gate_inject;
		return download_dll;
	}

	auto get_inject(std::string url, std::string host_gate_inject)-> std::string
	{
		std::string url_inject = "";
		return url_inject = "http://" + url + host_gate_inject;
	}

	auto gen_key(std::string login, std::string password) -> void
	{
		std::string g_key = "";

		my_lic->user_name = login.c_str();
		my_lic->user_password = login.c_str();
		g_key = my_lic->generate_key();

	}

	auto gen_token(std::string login, std::string password, std::string key, std::string url_time)-> std::string
	{
		std::string _tkn_one = md5(login).substr(0, 15),
			_tkn_two = md5(password).substr(0, 15),
			_tkn_three = md5(key).substr(0, 15),
			_tkn_four = md5(my_lic->GetRec(url_time, HTTP_CLEAR)).substr(0, 15);

		std::string _general_tkn = _tkn_one + _tkn_two + _tkn_three + _tkn_four;
		_general_tkn = md5(_general_tkn);

		return _general_tkn;
	}


	auto get_gen_url(std::string host, std::string path, std::string host_gate_login, std::string user_name, std::string host_gate_password, std::string user_password,
		std::string host_gate_system_key, std::string generate_key, std::string host_gate_token, std::string get_token)-> std::string
	{

		std::string gen_url = host + path + host_gate_login + user_name + host_gate_password + user_password + host_gate_system_key + generate_key + host_gate_token + get_token;

		return gen_url;
	}



	auto URLDownloadBinary(LPCSTR lpszURL, BYTE **ppBuffer, DWORD *pdwSize) -> int
	{

		LPSTREAM lpStream = 0;
		BYTE *pResult = 0;
		int nResult = 0;

		if (lpszURL && SUCCEEDED(URLOpenBlockingStream(NULL, lpszURL, &lpStream, 0, NULL)))
		{
			STATSTG statStream;
			if (SUCCEEDED(lpStream->Stat(&statStream, STATFLAG_NONAME)))
			{
				DWORD dwSize = statStream.cbSize.LowPart;
				pResult = (BYTE *)malloc(dwSize);
				if (pResult)
				{
					LARGE_INTEGER liPos;
					ZeroMemory(&liPos, sizeof(liPos));
					lpStream->Seek(liPos, STREAM_SEEK_SET, NULL);
					lpStream->Read(pResult, dwSize, NULL);
					*ppBuffer = pResult;
					*pdwSize = dwSize;
					nResult = 1;
				}
			}
			lpStream->Release();
		}

		return nResult;
	}

};

unique_ptr<get_information> g_info(new get_info());