#pragma once
#include <lafez/lafez_pch.hpp>

namespace Lafez {
    class RendererBackend {
    public:
        // ctor
        // dtor

        // static void startUp();
        // static void shutDown();
        // funcs

    protected:

    private:
        static LzShrPtr<RendererBackend> sShared;
    };
};