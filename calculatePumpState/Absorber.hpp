//
//  Absorber.hpp
//  calculatePumpState
//
//  Created by Morgan on 15/11/16.
//  Copyright © 2015年 Morgan. All rights reserved.
//

#ifndef Absorber_hpp
#define Absorber_hpp

#include <stdio.h>
#include <iostream>
#include "Formular.hpp"

using namespace std;

/*
 溴化锂吸收式热泵的吸收器（Absorber）。
 吸收器:
 已知量为二次水的入口温度 Twai = 50˚C、二次水的出口温度 Twco = 70˚C,以及∆T
 所求
 状态点    物质       位置          温度/˚C      压力/kPa       焓/(kJ/kg)   质量分数（LiBr）%
 2        稀溶液      吸收器出口      T2o         P2o           H2o         X2o
 6        浓溶液      吸收器入口      T6i         P6i           H6i         X6i
 
 ∆: /'delta/
 
 */

class Absorber {
    
private:
    //二次水入口温度及二次水出吸收器的温度
    double Twai,Twao;
    //二次水在吸收器中升温幅度
    double deltaTw1;
    //出口稀溶液温升
    double deltaT_a = 6;
    
    //再循环倍率（circulationRate） f = M/(ML-MH) 即单位质量流量的水蒸气需要稀溶液的质量流量
    double circulationRate_a = 30;
    
    double T2o,P2o,H2o,X2o;
    double T6i,P6i,H6i,X6i;
    
    double calTwao();
    
    double calT2o();
    
    double calP2o();
    
    double calX2o();
    
    double calT6i();
    
    double calX6i();
    
    double calH2o();
    
    double calH6i();
    
public:
    
    Absorber();
    
    Absorber(double Twai,double deltaTw1,double deltaT_a,double p_a,double deltaX_a);
    
    void setDeltaT_a();
    
    void printAbsorber();
    
    double getX6i();
    
    double getX2o();
    
    double getT2o();
    
    double getH2o();
    
};

#endif /* Absorber_hpp */
