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

double LiBrPump::calPressrueOfAbsorber(double p1o,double deltaP_e){
    return p1o-(deltaP_e/1000);
}

void LiBrPump::set_tdrAC(double a,double b){
    this->a_tdr = a/(a+b);
    this->c_tdr = b/(a+b);
    this->deltaT_w1 = calDeltaT_w1();
    this->deltaT_w2 = calDeltaT_w2();
};