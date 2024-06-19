#include "iperf/iperf.h"

int main() {
    
    iperf::server::start();
    Sleep(10000); 
    std::cout << iperf::client::check("10.222.3.84"); 
    return 0;
}