#include "iperf/iperf.h"

int main() {
    
    iperf::server::start();
    Sleep(20000); 
    std::cout << iperf::client::check("10.222.3.84","5202");
    return 0;
}