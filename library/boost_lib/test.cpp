#include <boost/filesystem.hpp>
#include <string>

int main () {
    boost::filesystem::exists("/app/test.cpp");
    return 0;   
}