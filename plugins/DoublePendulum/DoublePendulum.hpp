// PluginDoublePendulum.hpp
// Aleksandar Koruga (aleksandar.koruga@gmail.com)

#pragma once

#include "SC_PlugIn.hpp"

namespace DoublePendulum {
    struct Component 
    {
        float phi;
        float theta;
        float mass;
        float length;
        Component() : phi( std::rand()/(float) RAND_MAX), theta(std::rand() / (float)RAND_MAX), mass(1), length(1) {}
    };


class DoublePendulum : public SCUnit {
public:
    DoublePendulum();

    // Destructor
    // ~DoublePendulum();

private:
    // Calc function
    void next(int nSamples);

    // Member variables
protected:

    Component pt1;
    Component pt2;
    float rot;

    void TimeStep(float dT,float damp);

    void UpdateSystem(float dT, float damp, float forcingFreq, float forcingConst);
    


};

} // namespace DoublePendulum
