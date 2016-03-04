//
//  Condenser.cpp
//  calculatePumpState
//
//  Created by Morgan on 15/11/16.
//  Copyright © 2015年 Morgan. All rights reserved.
//

#include "Condenser.hpp"


Condenser::Condenser(){
    this->T3o = Twco + deltaT_c;
}

Condenser::Condenser(double Twco, double deltaT_c){
    this->deltaT_c = deltaT_c;
    this->T3o = Twco + deltaT_c;
    this->P3o = calP3o(T3o);
    this->X3o = 0;
    this->H3o = calH3o(T3o);
    
}

//三步法计算水的饱和蒸汽压力
double Condenser::calP3o(double t){
    double lgP3o = lgsvp(conversionT_C2K(t));
    return conversion_P_lgmmHg2kPa(lgP3o);
}

double Condenser::calH3o(double t){
    return _H2O_enthalpy(t);
}

double Condenser::setDeltaT_C(double deltaT_C){
    return deltaT_C;
}

double Condenser::setTwco(double Twco){
    return Twco;
}

void Condenser::printCondenser(){
    
    cout << "\t冷凝器状态参数如下所示:" <<endl;
    
    cout << "\t  已知:" <<endl;
    cout << "\t    Twco = "<<Twco<<"˚C"<<endl;
    
    cout << "\t  假定:" <<endl;
    cout << "\t    ∆Tc  = " <<deltaT_c<<"˚C"<<endl;
    
    cout << "\t  求得:" <<endl;
    cout << "\t    T3o  = " <<T3o <<"˚C"<<endl;
    cout << "\t    P3o  = " <<P3o <<"kPa"<<endl;
    cout << "\t    H3o  = " <<H3o <<"kJ/kg"<<endl;
    cout << "\t    X3o  = " <<X3o <<"%"<<endl;
    
}