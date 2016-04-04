//
//  LiBrPump.cpp
//  calculatePumpState
//
//  Created by Morgan on 15/11/16.
//  Copyright © 2015年 Morgan. All rights reserved.
//

#include "LiBrPump.hpp"



LiBrPump::LiBrPump(){
    
    pumpInit(this->Twai, this->Twco, this->a_tdr, this->c_tdr);

    this->e = Evaporator(Twei,Tweo,deltaT_e);
    cout << "蒸发器构建成功" << endl;
    e.printEvaporator();
    
    double p_a = calPressrueOfAbsorber(e.getP1o(), this->deltaP_e);
    //默认吸收器与冷凝器温度差为6摄氏度
    this->a = Absorber(Twai, deltaT_w1,deltaT_a,p_a, deltaX_a);
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
    this->h = HeatExchanger(a.getT2o(),XL, XH, g.getH4o(),a.getH2o(), this->deltaT_h);
    cout <<"\n溶液热交换器构造成功" <<endl;
    h.printHeatExchanger();
    
    calCOP();
    
}


LiBrPump::LiBrPump(double Twai, double Twco, double Twei, double Tweo, double deltaT_e
                   ,double a_tdr, double c_tdr, double deltaT_a
                   ,double deltaP_e ,double deltaX_a
                   ,double deltaT_c, double deltaT_h){
    pumpInit(Twco,Twai,a_tdr,c_tdr);
    
    this->e = Evaporator(Twei,Tweo,deltaT_e);
    cout << "蒸发器构建成功" << endl;
    e.printEvaporator();
    //由蒸发器决定吸收器压强
    double p_a = calPressrueOfAbsorber(e.getP1o(), this->deltaP_e);
    //默认吸收器与冷凝器温度差为6摄氏度
    this->a = Absorber(Twai, deltaT_w1,deltaT_a, p_a, deltaX_a);
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
    this->h = HeatExchanger(a.getT2o(),XL, XH, g.getH4o(),a.getH2o(), deltaT_h);
    cout <<"\n溶液热交换器构造成功" <<endl;
    h.printHeatExchanger();
    
    this->circulationRate = calCirculationRate(XL, XH);
    
    calCOP();
    
}

LiBrPump::LiBrPump(double Twai, double Twco, double Twei, double Tweo){
    
    
}

/*
 吸收器和冷凝器 二次水温差
*/

void LiBrPump::pumpInit(double Twai, double Twco, double a_tdr, double c_tdr){
    
    this->deltaT_w = Twco - Twai;
    this->deltaT_w1 = this->deltaT_w*a_tdr;
    this->deltaT_w2 = this->deltaT_w*c_tdr;
}

//double LiBrPump::calDeltaT_w(t1,t2){
////    return Twco - Twai;
//    return t2 - t1;
//}
//
//double LiBrPump::calDeltaT_w1(t,r){
////    return  deltaT_w*a_tdr;
//    return t*r
//};
//
//double LiBrPump::calDeltaT_w2(deltaT_w,c_tdr){
//    return deltaT_w*c_tdr;
//};

double LiBrPump::calCirculationRate(double XL, double XH){
    this->circulationRate = XH / (XH - XL);
    return this->circulationRate;
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
    this->deltaT_w1 = this->deltaT_w * this->a_tdr;
    this->deltaT_w2 = this->deltaT_w * this->c_tdr;
};

double LiBrPump::calQe(){
    this->Q_e = e.getH1o() - c.getH3o();
    return this->Q_e;
}

double LiBrPump::calQc(){
    this->Q_c = g.getH4wo() - c.getH3o();
    return this->Q_c;
}

double LiBrPump::calQa(){
    double a = getCirculationRate();
    this->Q_a = e.getH1o() + (a - 1) * h.getH8o() - a * this->a.getH2o();
    return this->Q_a;
}

double LiBrPump::calQg(){
    double a = getCirculationRate();
    this->Q_g = (a - 1) * g.getH4o() + g.getH4wo() - a * h.getH7o();
    return this->Q_g;
}

double LiBrPump::calQex(){
    double a = getCirculationRate();
    this->Q_ex = a * (h.getH7o() - this->a.getH2o());
    return this->Q_ex;
}

double LiBrPump::calCOP(){
    calQa();
    calQc();
    calQe();
    calQex();
    calQg();
    cout << "Qg + Qe = " << Q_g + Q_e << endl;
    cout << "Qc + Qa = " << Q_c + Q_a << endl;
    this->cop = (Q_c + Q_a) / Q_g;
    cout << cop <<endl;
    return cop;
}



