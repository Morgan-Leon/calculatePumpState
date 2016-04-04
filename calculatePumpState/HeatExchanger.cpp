//
//  HeatExchanger.cpp
//  calculatePumpState
//
//  Created by Morgan on 16/3/7.
//  Copyright © 2016年 Morgan. All rights reserved.
//

#include "HeatExchanger.hpp"

HeatExchanger::HeatExchanger(){
};

HeatExchanger::HeatExchanger(double T2o, double X2o, double X4o, double H4o, double H2o, double deltaT_h){
    
    setDeltaT_h(deltaT_h);
    
    this->XL = X2o;
    this->XH = X4o;
    
    this->X7o = XL;
    this->X8o = XH;
    
    this->T8o = calT8o(T2o);
    
    this->H8o = calH8o(T8o, X8o);
    
    this->H7o = calH7o(H4o, H2o);
    
    this->T7o = calT7o(H7o, X7o);
    
};


double HeatExchanger::calT8o(double t){
    return (t + this->deltaT_h);
}

double HeatExchanger::calH8o(double t, double x){
    return enthalpyLiBrSolution(t, x);
}

double HeatExchanger::calH7o(double h4, double h2){
    return (h4-this->H8o) * (this->XL / this->XH) + h2;
}

double HeatExchanger::calT7o(double H7o, double X7o){
    return temperaturLiBrSolution(H7o, X7o);
}

void HeatExchanger::setDeltaT_h(double h){
    this->deltaT_h = h;
}

double HeatExchanger::getH7o(){
    return this->H7o;
}

double HeatExchanger::getH8o(){
    return this->H8o;
}

void HeatExchanger::printHeatExchanger(){
    cout << "\t溶液热交换器状态参数如下所示:\n";
    
//    cout << "\t  已知:" <<endl;
//    cout << "\t    Twai = "<<Twai<<"˚C"<<endl;
//    cout << "\t    Twao = "<<Twao<<"˚C"<<endl;
    
    cout << "\t  假定:" <<endl;
    cout << "\t    ∆T_h = "<<deltaT_h<<"˚C"<<endl;
    
    cout << "\t  求得:" <<endl;
    cout << "\t    T7o = " <<T7o<<"˚C" <<endl;
    cout << "\t    P7o = " <<"--" <<endl;
    cout << "\t    H7o = " <<H7o<<"kJ/kg" <<endl;
    cout << "\t    X7o = " <<X7o<<"%" <<endl;
    
    cout << "\t    T8o = " <<T8o<<"˚C" <<endl;
    cout << "\t    P8o = " <<"--" <<endl;
    cout << "\t    H8o = " <<H8o<<"kJ/kg" <<endl;
    cout << "\t    X8o = " <<X8o<<"%" <<endl;

}