// PluginDoublePendulum.hpp
// Aleksandar Koruga (aleksandar.koruga@gmail.com)

#pragma once

#include "SC_PlugIn.hpp"

namespace DoublePendulum {

class DoublePendulum : public SCUnit {
public:
    DoublePendulum();

    // Destructor
    // ~DoublePendulum();

private:
    // Calc function
    void next(int nSamples);

    // Member variables
};

} // namespace DoublePendulum
