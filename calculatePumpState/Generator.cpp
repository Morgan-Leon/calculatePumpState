//
//  Generator.cpp
//  calculatePumpState
//
//  Created by Morgan on 15/11/16.
//  Copyright © 2015年 Morgan. All rights reserved.
//

#include "Generator.hpp"

Generator::Generator(){
    this->T4o = calT4o(75, 62.6386);
}

//发生器中的三个点的压力均相同 且都由冷凝器的压力决定（认为两者压力差极小，可忽略）
Generator::Generator(double T3o, double P3o, double X2o, double X6i){
    
    //T4wo为过热水蒸气温度，等于溴化锂水溶液露点温度
    //其浓度按照出口稀溶液浓度和入口浓溶液浓度的平均值计算
    this->T4wo = calT4wo(T3o, (X6i + X2o)/2);
    
    this->P4wo = P3o;
    this->H4wo = calH4wo(T3o, T4wo);
    this->X4wo = 0;
    
    this->P4o = P3o;
    this->T4o = calT4o(T3o, X6i);
    this->X4o = X6i;
    this->H4o = calH4o(T4o, X4o);
    
    this->P5i = P3o;
    this->T5i = calT5i(T3o,X2o);
    this->X5i = X2o;
    this->H5i = calH5i(T5i, X5i);
    
}

double Generator::calH4wo(double saturationTemperatureH2O_C,double saturationTemperatureLiBr_C){
    return _H2OHeat_enthalpy(saturationTemperatureH2O_C, saturationTemperatureLiBr_C);
}

double Generator::calT4wo(double t, double x){
    return dewTLiBr(t, x);
}

double Generator::calT4o(double t, double x){
    return dewTLiBr(t, x);
}

double Generator::calT5i(double t, double x){
    return dewTLiBr(t, x);
}

double Generator::calH4o(double t, double x){
    return enthalpyLiBrSolution(t, x);
}

double Generator::calH5i(double t, double x){
    return enthalpyLiBrSolution(t, x);
}

void Generator::printGenerator(){
    cout << "\t发生器状态参数如下所示:" <<endl;
    
//    cout << "\t  已知:" <<endl;
//    cout << "\t    Twei = "<<Twei<<"˚C"<<endl;
//    cout << "\t    Tweo = "<<Tweo<<"˚C"<<endl;
//    
//    cout << "\t  假定:" <<endl;
//    cout << "\t    ∆Te  = " <<deltaT_e<<"˚C"<<endl;
    
    cout << "\t  求得:" <<endl;
    cout << "\t    T4wo  = " <<T4wo <<"˚C"<<endl;
    cout << "\t    P4wo  = " <<P4wo <<"kPa"<<endl;
    cout << "\t    H4wo  = " <<H4wo <<"kJ/kg"<<endl;
    cout << "\t    X4wo  = " <<X4wo <<"%"<<endl;
    cout << "\t    T4o  = " <<T4o <<"˚C"<<endl;
    cout << "\t    P4o  = " <<P4o <<"kPa"<<endl;
    cout << "\t    H4o  = " <<H4o <<"kJ/kg"<<endl;
    cout << "\t    X4o  = " <<X4o <<"%"<<endl;
    cout << "\t    T5i  = " <<T5i <<"˚C"<<endl;
    cout << "\t    P5i  = " <<P5i <<"kPa"<<endl;
    cout << "\t    H5i  = " <<H5i <<"kJ/kg"<<endl;
    cout << "\t    X5i  = " <<X5i <<"%"<<endl;
}