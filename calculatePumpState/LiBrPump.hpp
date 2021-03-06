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
    
    //默认出口稀溶液温升
    double deltaT_a = 6.000;
    
    //蒸发器与吸收器间的压力差(13.3-65)Pa
    double deltaP_e = 25;
    
    //吸收器进口浓溶液与稀溶液间的浓度差(XH-XL) = 0.03至0.06
    double deltaX_a = 0.04;
    
    //冷凝器出口水温要略高于二次水出口，其大小由冷凝管决定（3-5˚C）
    double deltaT_c = 5;
    
    //T8o 与冷端(T2o)温差通常控制在5˚C以上（5-25˚C），即∆T_h = 17（5至25之间）
    double deltaT_h = 17;
    
    //XH:溴化锂浓溶液浓度 XL:溴化锂稀溶液浓度
    double XH, XL;
    
    //循环倍率（circulationRate）：a = XH/(XH-XL)
    double circulationRate;
    
    
    Evaporator e;
    Absorber a;
    Condenser c;
    Generator g;
    HeatExchanger h;
    
//    double calDeltaT_w(double,double);
//    double calDeltaT_w1(double,double);
//    double calDeltaT_w2(double,double);
    
    void pumpInit(double,double,double,double);
    
    //计算循环倍率a
    double calCirculationRate(double XL, double XH);
    
    double calPressrueOfAbsorber(double p1o,double deltaP_e);
    
    /*
        Q_e: 蒸发器吸热量 = h1o - h3o
        Q_c: 冷凝器放热量 = h4wo - h3o
        Q_a: 吸收器放热量 = h1o + (a - 1) * h8o - a * h2o
        Q_g: 发生器耗热量 = (a - 1) * h4o + h4wo - a * h7o
        Q_ex: 溶液热交换器的换热量 = a * (h7o - h2o)
     */
    double Q_e, Q_c, Q_a, Q_g, Q_ex;
    
    double calQe();
    
    double calQc();
    
    double calQa();
    
    double calQg();
    
    double calQex();
    
    //热能效率
    double cop;
    
    double calCOP();
    
public:
    
    LiBrPump();
    
    //构建一个热泵需要：
    //Twai: 二次水入口温度
    //Twco: 二次水出口温度，所制取热水温度
    //Twei: 低品质热源入口温度
    //Tweo: 低品质热源出口温度
    //deltaT_e: 蒸发器温升
    //a_trd: 吸收器升温比
    //c_trd: 冷凝器升温比
    //deltaP_e: 蒸发器与吸收器间的压力差(13.3-65)Pa
    //deltaX_a: 吸收器进口浓溶液与稀溶液间的浓度差(XH-XL) = 0.03至0.06
    //deltaT_c: 冷凝器出口水温要略高于二次水出口，其大小由冷凝管决定（3-5˚C）
    //deltaT_h: T8o 与冷端(T2o)温差通常控制在5˚C以上（5-25˚C），即∆T_h = 17（5至25之间）
    LiBrPump(double Twai, double Twco, double Twei, double Tweo, double deltaT_e
             ,double a_trd, double c_trd, double deltaT_a
             ,double deltaP_e ,double deltaX_a
             ,double deltaT_c, double deltaT_h);
    
    
    //构建一个热泵需要：
    //Twai: 二次水入口温度
    //Twco: 二次水出口温度，所制取热水温度
    //Twei: 低品质热源入口温度
    //Tweo: 低品质热源出口温度
    //其他参数为默认状态
    LiBrPump(double Twai, double Twco, double Twei, double Tweo);
    
    double getCirculationRate();


    //设置吸收器和冷凝器的温差比
    void set_tdrAC(double a,double b);
    
    double getCOP();
    
    
};

#endif /* LiBrPump_hpp */
