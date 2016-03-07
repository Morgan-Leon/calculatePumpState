//
//  LiBrPump.hpp
//  calculatePumpState
//
//  Created by Morgan on 15/11/16.
//  Copyright © 2015年 Morgan. All rights reserved.
//

#ifndef LiBrPump_hpp
#define LiBrPump_hpp

#include <stdio.h>
#include "Evaporator.hpp"
#include "Absorber.hpp"
#include "Condenser.hpp"
#include "Generator.hpp"
#include "HeatExchanger.hpp"

/*
  ∆: /'delta/
 */
class LiBrPump{
private:
    //thermal load : 热负荷Q（KW）
    double thermalLoad = 5000;
    //tdr: Temperature difference ratio 温差比
    //吸收器与冷凝器的温差比
    double a_tdr = 1.3/2.4;
    double c_tdr = 1.1/2.4;
    
    //驱动热源温度 Twgi = 150˚C
    double Twgi = 150;
    
    //低品质热源温度：
    double Twei =45,Tweo = 30, deltaT_e=3.00000;
    //所制取热水温度：
    double Twco = 70,Twai = 50;
    
    //二次水的温差
    double deltaT_w;
    //二次水在吸收器中的升温程度
    double deltaT_w1;
    //二次水在冷凝器中的升温程度
    double deltaT_w2;
    
    //蒸发器与吸收器间的压力差(13.3-65)Pa
    double deltaP_e = 25;
    
    //吸收器进口浓溶液与稀溶液间的浓度差(XH-XL) = 0.03至0.06
    double deltaX_a = 0.04;
    
    //冷凝器出口水温要略高于二次水出口，其大小由冷凝管决定（3-5˚C）
    double deltaT_c = 5;
    
    //T8o 与冷端(T2o)温差通常控制在5˚C以上（5-25˚C），即∆T_h = 17（5至25之间）
    double deltaT_h = 17;
    
    Evaporator e;
    Absorber a;
    Condenser c;
    Generator g;
    HeatExchanger h;
    
    double calDeltaT_w();
    double calDeltaT_w1();
    double calDeltaT_w2();
    
    double calPressrueOfAbsorber(double p1o,double deltaP_e);
    
public:
    
    LiBrPump();

    //设置吸收器和冷凝器的温差比
    void set_tdrAC(double a,double b);
    
};

#endif /* LiBrPump_hpp */
