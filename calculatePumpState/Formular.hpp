//
//  Formular.hpp
//  calculatePumpState
//
//  Created by Morgan on 15/11/15.
//  Copyright © 2015年 Morgan. All rights reserved.
//

#ifndef Formular_hpp
#define Formular_hpp

#include <iostream>
#include <math.h>
using namespace std;

//温度换算 摄氏度转开尔文
double conversionT_C2K(double temperature_C);

//开尔文转摄氏度
double conversionT_K2C(double temperature_K);

//压强转换公式 毫米汞柱转千帕
double conversion_P_lgmmHg2kPa(double lgp);

//已知饱和水蒸气温度 计算压强
double lgsvp(double satsaturationTemperatureH2O);

//已知饱和水蒸汽压强 计算温度
double saturationTemperatureH2O(double satsaturationPressureH2O_kPa);

//千卡换算千焦
double conversionQ_kCal2kJ(double kCal);

//水的焓值（kJ/kg）
double _H2O_enthalpy(double temperatureH2O_C);

//水蒸气的焓值
double _H2OVapor_enthalpy(double temperatureH2O_C);

//过热水蒸气的焓值
double _H2OHeat_enthalpy(double saturationTemperatureH2O_C, double saturationTemperatureLiBr_C);

//计算溴化锂溶液露点温度
double dewTLiBr(double satsaturationTemperatureH2O_C, double concentrationOfLiBrSolution);

//计算溴化锂溶液的焓值
double enthalpyLiBrSolution(double solutionTemperatureLiBr_C,double concentrationOfLiBrSolution);

//计算溴化锂溶液的温度
double temperaturLiBrSolution(double enthalpyLiBrSolution, double concentrationOfLiBrSolution);

//计算溴化锂溶液的浓度
double _concentration_LiBrSolution(double solutionTemperatureLiBr_C,double pressure_kPa);

#endif /* Formular_hpp */
