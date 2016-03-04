//
//  Absorber.cpp
//  calculatePumpState
//
//  Created by Morgan on 15/11/16.
//  Copyright © 2015年 Morgan. All rights reserved.
//

#include "Absorber.hpp"

/*
 溴化锂吸收式热泵的吸收器
 */

Absorber::Absorber(){
    
}

//各参数意义：吸收器入口二次水温度， 二次水在吸收器中的升温程度,
Absorber::Absorber(double Twai,double deltaT_w1,double deltaT_a,double p_a,double deltaX_a){
    this->Twai = Twai;
    this->deltaTw1 = deltaT_w1;
    this->deltaT_a = deltaT_a;
    this->Twao = calTwao();
    this->T2o  = calT2o();
    this->P2o = p_a;
    this->X2o = calX2o();
    this->H2o = calH2o();
    
    

    this->P6i = p_a;
    this->X6i = X2o + deltaX_a * 100;
    this->T6i = calT6i();
    this->H6i = calH6i();
    
}

double Absorber::calTwao(){
    return this->Twai + this->deltaTw1;
}

double Absorber::calT2o(){
    return Twao + deltaT_a;
}

double Absorber::calX2o(){
    return _concentration_LiBrSolution(T2o, P2o);
}

double Absorber::calH2o(){
    return enthalpyLiBrSolution(T2o, X2o);
}

double Absorber::calT6i(){
    double temperatureForWater = saturationTemperatureH2O(P6i);
    return dewTLiBr(temperatureForWater, X6i);
}

double Absorber::calH6i(){
    return enthalpyLiBrSolution(T6i, X6i);
}

void Absorber::printAbsorber(){
    cout << "\t吸收器状态参数如下所示:\n";
    
    cout << "\t  已知:" <<endl;
    cout << "\t    Twai = "<<Twai<<"˚C"<<endl;
    cout << "\t    Twao = "<<Twao<<"˚C"<<endl;
    
    cout << "\t  假定:" <<endl;
    cout << "\t    ∆Tw1 = "<<deltaTw1<<"˚C"<<endl;
    
    cout << "\t  求得:" <<endl;
    cout << "\t    T2o = " <<T2o<<"˚C" <<endl;
    cout << "\t    P2o = " <<P2o<<"kPa" <<endl;
    cout << "\t    H2o = " <<H2o<<"kJ/kg" <<endl;
    cout << "\t    X2o = " <<X2o<<"%" <<endl;
    
    cout << "\t    T6o = " <<T6i<<"˚C" <<endl;
    cout << "\t    P6i = " <<P6i<<"kPa" <<endl;
    cout << "\t    H6i = " <<H6i<<"kJ/kg" <<endl;
    cout << "\t    X6i = " <<X6i<<"%" <<endl;
}
