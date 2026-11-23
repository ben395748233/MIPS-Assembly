#pragma once

#include <cstdint>

namespace mipslab {

    enum class EngineType {
        Sequential,
        Pipeline
    };

    struct SimulationConfig {
        EngineType engine = EngineType::Sequential;

        std::uint64_t max_cycles = 1'000'000;

        bool verbose = false;
    };

}

