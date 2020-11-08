#include <lafez/utils/Log.hpp>

int main() {
    LZ_CLIENT_INFO("test message at {0}", __func__);
    return 0;
}