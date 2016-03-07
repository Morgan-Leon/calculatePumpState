//
//  LiBrPump.cpp
//  calculatePumpState
//
//  Created by Morgan on 15/11/16.
//  Copyright © 2015年 Morgan. All rights reserved.
//

#include "LiBrPump.hpp"



LiBrPump::LiBrPump(){
    
    this->deltaT_w = calDeltaT_w();
    this->deltaT_w1 = calDeltaT_w1();
    this->deltaT_w2 = calDeltaT_w2();

    this->e = Evaporator(Twei,Tweo,deltaT_e);
    cout << "蒸发器构建成功" << endl;
    e.printEvaporator();
    
    double p_a = calPressrueOfAbsorber(e.getP1o(), this->deltaP_e);
    //默认吸收器与冷凝器温度差为6摄氏度
    this->a = Absorber(Twai, deltaT_w1,6.000,p_a, deltaX_a);
    cout << "\n吸收器构建成功" <<endl;
    a.printAbsorber();
    
    this->c = Condenser(Twco,deltaT_c);
    cout <<"\n冷凝器构建成功" <<endl;
    c.printCondenser();
    
    //构造发生器需要吸收器入口温度浓度和冷凝器出口温度
    this->g = Generator(c.getT3o(),c.getP3o(),a.getX2o(),a.getX6i());
    cout <<"\n发生器构建成功" <<endl;
    g.printGenerator();
    
    this->XL = a.getX2o();
    this->XH = g.getX4o();
    
    this->circulationRate = calCirculationRate(XL, XH);
    
    //构造溶液热交换器需要吸收器稀溶液出口温度和浓度以及发生器浓溶液出口浓度
    this->h = HeatExchanger(a.getT2o(),XL, XH, g.getH4o(),a.getH2o());
    cout <<"\n溶液热交换器构造成功" <<endl;
    h.printHeatExchanger();
    
}

double LiBrPump::calDeltaT_w(){
    return Twco - Twai;
}

double LiBrPump::calDeltaT_w1(){
    return  deltaT_w*a_tdr;
};

double LiBrPump::calDeltaT_w2(){
    return deltaT_w*c_tdr;
};

double LiBrPump::calCirculationRate(double XL, double XH){
    return XH / (XH - XL);
}

double LiBrPump::calPressrueOfAbsorber(double p1o,double deltaP_e){
    return p1o-(deltaP_e/1000);
}

double LiBrPump::getCirculationRate(){
    return this->circulationRate;
}

void LiBrPump::set_tdrAC(double a,double b){
    this->a_tdr = a/(a+b);
    this->c_tdr = b/(a+b);
    this->deltaT_w1 = calDeltaT_w1();
    this->deltaT_w2 = calDeltaT_w2();
};