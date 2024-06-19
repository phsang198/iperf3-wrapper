#pragma once
#include <iostream>
#include <array>
#include <memory>
#include <stdexcept>
#include <string>
#include <regex>
#include <cstdio>
#include <sstream>
#include <thread>
#include <Windows.h>
#include <processthreadsapi.h>

namespace iperf
{
	static std::string getExePath(std::string projectName)
	{
		char curPath[FILENAME_MAX];
		GetModuleFileNameA(NULL, curPath, sizeof(curPath));
		std::string szCurDir(curPath);

		size_t found = szCurDir.find(projectName);
		szCurDir.erase(found, szCurDir.length() - 1);
		return szCurDir;
	}
	static void parseIperfOutput(const std::string& output) {
		std::regex lineRegex(R"(\[\s*\d+\]\s+(\d+\.\d+-\d+\.\d+ sec)\s+(\d+ MBytes)\s+(\d+\.\d+ Gbits/sec)\s+(\d+)\s+(\d+ KBytes))");
		std::smatch match;

		std::istringstream outputStream(output);
		std::string line;
		while (std::getline(outputStream, line)) {
			if (std::regex_search(line, match, lineRegex)) {
				std::string interval = match[1].str();
				std::string transfer = match[2].str();
				std::string bitrate = match[3].str();
				std::string retr = match[4].str();
				std::string cwnd = match[5].str();

				std::cout << "Interval: " << interval << "\n";
				std::cout << "Transfer: " << transfer << "\n";
				std::cout << "Bitrate: " << bitrate << "\n";
				std::cout << "Retr: " << retr << "\n";
				std::cout << "Cwnd: " << cwnd << "\n";
				std::cout << "--------------------\n";
			}
		}
	}

	class client
	{
	public:
		static std::string check(std::string ip, std::string host = "5201");
	private:
		static std::string exec(const char* cmd);
	};
	class server
	{
	public:
		static std::thread tIperf; 
		static std::string port;
	public:
		static void start();
		static void stop();
	};
}