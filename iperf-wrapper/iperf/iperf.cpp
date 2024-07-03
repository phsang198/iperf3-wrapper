#pragma once
#include "iperf.h"
#define PROJECT_NAME "iperf3-wrapper.exe"

std::thread iperf::server::tIperf;
std::string iperf::server::port = "5222";

std::string iperf::client::exec(const char* cmd) {
	std::array<char, 128> buffer;
	std::string result;
	std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd, "r"), _pclose);
	if (!pipe) {
		throw std::runtime_error("popen() failed!");
	}
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
		result += buffer.data();
	}
	return result;
}

std::string iperf::client::check(std::string ip, std::string host)
{
	std::string iperf_path = iperf::getExePath(PROJECT_NAME) + R"(iperf\run)";
	std::string cmd = "cd /D " + iperf_path + " && iperf3 -c " + ip + " -p " + host;
	//int a = system(cmd.c_str());

	return exec(cmd.c_str());
}
//----------------------------------------------------------------------------
void iperf::server::start()
{
	auto wrap = [&]() {
		std::string iperf_path = iperf::getExePath(PROJECT_NAME) + R"(iperf\run)";
		std::string cmd = "cd /D " + iperf_path + " && iperf3 -s -p " + port + " -1";
		int a = system(cmd.c_str());
	};
	iperf::server::tIperf = std::move(std::thread(wrap));
	iperf::server::tIperf.detach();
}
void iperf::server::stop()
{
	if (TerminateThread(iperf::server::tIperf.native_handle(), 1))
	{
		iperf::server::tIperf.detach();
	}
}
