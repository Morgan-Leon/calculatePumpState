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

double Absorber::calTwao(){
    return this->Twai + this->deltaTw1;
}

double Absorber::calT2o(){
    return Twao + deltaT_a;
};

Absorber::Absorber(){
    
}

Absorber::Absorber(double Twai,double deltaTw1,double deltaT_a){
    this->Twai = Twai;
    this->deltaTw1 = deltaTw1;
    this->deltaT_a = deltaT_a;
    this->Twao = calTwao();
    this->T2o  = calT2o();
    
}

void Absorber::printAbsorber(){
    cout << "\t吸收器状态参数如下所示:\n";
    cout << "\t    Twai = "<<Twai<<"˚C"<<endl;
    cout << "\t    Twao = "<<Twao<<"˚C"<<endl;
    cout << "\t    ∆Tw1 = "<<deltaTw1<<"˚C"<<endl;
    cout << "\t    T2o = " <<T2o<<"˚C" <<endl;
}
