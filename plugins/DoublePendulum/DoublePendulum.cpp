// PluginDoublePendulum.cpp
// Aleksandar Koruga (aleksandar.koruga@gmail.com)

#include "SC_PlugIn.hpp"
#include "DoublePendulum.hpp"

static InterfaceTable* ft;

namespace DoublePendulum {

DoublePendulum::DoublePendulum() : pt1(),pt2(){
    mCalcFunc = make_calc_function<DoublePendulum, &DoublePendulum::next>();
    next(1);
}

void DoublePendulum::next(int nSamples) {

    const float* m1 = in(0);
    const float* m2 = in(1);
    const float* l1 = in(2);
    const float* l2 = in(3);
    const float* k = in(4);
    const float* t = in(5);
    const float* freq = in(6);
    const float* d = in(7);


    float* outbuf = out(0);
    float* outbuf1 = out(1);
    float* outbuf2 = out(2);
    float* outbuf3 = out(3);


    for (int i = 0; i < nSamples; ++i) {

        pt1.mass = m1[i];
        pt2.mass = m2[i];
        pt1.length = l1[i];
        pt2.length = l2[i];

        UpdateSystem(t[i], d[i], freq[i], k[i]);
        
        outbuf[i] = pt1.phi;
        outbuf1[i] = pt1.theta;
        outbuf2[i] = pt2.phi;
        outbuf3[i] = pt2.theta;

    }
}

void DoublePendulum::TimeStep(float dT, float damp)
{
    float dA = pt1.phi - pt1.theta;

    //pt2
    float x = -1.0f * (pt2.mass * ((pt2.length * powf( pt2.theta,2.0f)  ) + (pt1.length *(float) powf(pt2.phi,2.0f)  * cosf(dA))) * sinf(dA)) / (pt1.length * (pt1.mass + (pt2.mass * (float) powf(sinf(dA),2.0f)    )));
    //pt2
    float y= (((pt1.mass + pt2.mass) * (pt1.length * powf(pt2.phi,2.0f) ) + pt2.length * pt2.mass * cosf(dA) * powf(pt2.theta,2.0f) ) * (sinf(dA))) / (pt2.length * (pt1.mass + (pt2.mass * powf(sinf(dA), 2.0f))   ));
   
    
    pt2.phi = zapgremlins( sc_wrap2((pt2.phi+(x*dT))*damp, twopi_f));
    pt2.theta =zapgremlins( sc_wrap2((pt2.theta + (y * dT)) * damp, twopi_f));

    pt1.phi = zapgremlins(sc_wrap2(pt1.phi + pt2.phi*dT, twopi_f));
    pt1.theta = zapgremlins(sc_wrap2(pt1.theta + pt2.theta * dT, twopi_f));

}
void DoublePendulum::UpdateSystem(float dT, float damp, float forcingFreq, float forcingConst )
{
    pt1.theta += forcingConst * sinf(rot * forcingFreq);
    pt1.theta= zapgremlins(sc_wrap2(pt1.theta, twopi_f));
    TimeStep(dT, damp);
    rot = sc_mod(pt1.theta, twopi_f);
}


} // namespace DoublePendulum

PluginLoad(DoublePendulumUGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<DoublePendulum::DoublePendulum>(ft, "DoublePendulum", false);
}
