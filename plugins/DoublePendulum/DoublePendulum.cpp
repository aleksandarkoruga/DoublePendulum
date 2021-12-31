// PluginDoublePendulum.cpp
// Aleksandar Koruga (aleksandar.koruga@gmail.com)

#include "SC_PlugIn.hpp"
#include "DoublePendulum.hpp"

static InterfaceTable* ft;

namespace DoublePendulum {

DoublePendulum::DoublePendulum() {
    mCalcFunc = make_calc_function<DoublePendulum, &DoublePendulum::next>();
    next(1);
}

void DoublePendulum::next(int nSamples) {
    const float* input = in(0);
    const float* gain = in(1);
    float* outbuf = out(0);

    // simple gain function
    for (int i = 0; i < nSamples; ++i) {
        outbuf[i] = input[i] * gain[i];
    }
}

} // namespace DoublePendulum

PluginLoad(DoublePendulumUGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<DoublePendulum::DoublePendulum>(ft, "DoublePendulum", false);
}
