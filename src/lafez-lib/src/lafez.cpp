#include <spdlog/spdlog.h>
#include "lafez.hpp"

namespace Lafez {
    void init() {
        spdlog::info("LafeZ initialized");
        spdlog::warn("Printing test warning");
    }
}