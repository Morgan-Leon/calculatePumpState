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
    
    this->a = Absorber(Twai, deltaT_w1,6.000);
    cout << "\n吸收器构建成功" <<endl;
    a.printAbsorber();
    
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

void LiBrPump::set_tdrAC(double a,double b){
    this->a_tdr = a/(a+b);
    this->c_tdr = b/(a+b);
    this->deltaT_w1 = calDeltaT_w1();
    this->deltaT_w2 = calDeltaT_w2();
};