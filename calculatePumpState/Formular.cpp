//
//  Formular.cpp
//  calculatePumpState
//
//  Created by Morgan on 15/11/15.
//  Copyright © 2015年 Morgan. All rights reserved.
//

#include "Formular.hpp"


/*
 摄氏度转开尔文温度
 */
double conversionT_C2K(double temperature_C){
    return temperature_C + 273.15;
}

/*
 开尔文温度转摄氏度
 */
double conversionT_K2C(double temperature_K){
    return temperature_K - 273.15;
}

/*
 mmHg与kPa换算
 */
double conversion_P_lgmmHg2kPa(double lgp){
    return  pow(10, lgp)*0.1333224;
}

/*计算水的饱和蒸汽压力
 Calculate saturated vapor pressure(svp) of H2O.
 lgsvp，lg为以10为底的对数
 */
double lgsvp(double satsaturationTemperatureH2O_K){
    double lgsvp;
    double t = satsaturationTemperatureH2O_K;
    double lgT = log10(t);
    lgsvp = 31.46559 - 8.2*lgT - 3142.305/t + 0.0024804*t;
    return lgsvp;
}

/*计算水的饱和温度 公式来源《蒸发过程饱和水蒸气对应参数的计算方程》-高俊
 Calculate saturated vapor temperature(svp) of H2O.
 适用于2kpa- 1500kpa 相对误差≤0.3%
 按此公式与上述压力计算公式反算 每个温度值与标准值几乎都相差0.4，遂在计算末加之
 */
double saturationTemperatureH2O(double satsaturationPressureH2O_kPa){
    double t = 0.0000000;
    double p = satsaturationPressureH2O_kPa;
    double c[] = {6.004553,15.89247,-0.1723261,0.3940772,-4.631586e-2,3.01707e-3};
    for (int i = 0; i < 6; i++) {
        t += c[i]*pow(log(p), i);
    }
    return t+0.4;
}

/*
 #06
 换算：1千卡 = 4.184千焦
 */
double conversionQ_kCal2kJ(double kCal){
    return kCal * 4.184;
}


/*
 #07
 计算饱和水的气化潜热(latent heat of vaporization)
 r = 597.34 - 0.555t1 - 0.2389 * 10^y
 y = 5.1463 - 1540/(t1+273.16)
 结果转化为kJ
 t1 为压力p时饱和水蒸气的温度，可利用#05计算
 */
double _H2O_latentHeatOfVaporization(double saturationTemperatureH2O_C){
    
    double t1 = saturationTemperatureH2O_C;
    double y = 5.1463 - 1540/(t1+273.16);
    double r = (597.34 - 0.555 * t1 - 0.2389 * pow(10, y));
    r = conversionQ_kCal2kJ(r);
    cout << "\t温度为" << t1 << "时水的气化潜热r = " << r << endl;
    return r;
}

/*
 #08
 计算水的焓值: h1 = t1 + 100 (kcal/kg)
 t1为水的温度（˚C）
 结果用公式6换算成千焦
 */
double _H2O_enthalpy(double temperatureH2O_C){
    return conversionQ_kCal2kJ(temperatureH2O_C + 100.00);
}

/*
 #09
 计算水蒸气的焓值：h2 = h1 + r (kJ/kg)
 r为饱和水的气化潜热
 */
double _H2OVapor_enthalpy(double temperatureH2O_C){
    return _H2O_enthalpy(temperatureH2O_C) + _H2O_latentHeatOfVaporization(temperatureH2O_C);
}

/*
 #10
 过热水蒸气的焓值
 h = h2 + Cp(t-t1)
 h2 = h1 + r
 h1 = t1 + 100
 
 t1 为压力p时饱和水蒸气的温度，可利用#05计算 ˚C
 t 为过热水蒸气的温度即压力p时溶液的平衡温度，可利用#08计算 ˚C
 h1 为温度为t1时饱和水的焓 kcal/kg
 h2 为温度为kcal/kg
 Cp 为过热水蒸气t1-t的定呀平均比热。计算普通单级循环蒸汽焓值时,Cp ≈ 0.46kcal/kg
 */

double _H2OHeat_enthalpy(double saturationTemperatureH2O_C, double saturationTemperatureLiBr_C){
    double Cp = 0.46;
    double t = saturationTemperatureLiBr_C;
    double t1 = saturationTemperatureH2O_C;
    double r = _H2O_latentHeatOfVaporization(t1);
    double h1 = t1 + 100;
    double h2 = h1 + r;
    double h = h2 + Cp * (t - t1);
    h = conversionQ_kCal2kJ(h);
    return h;
}


/*计算溴化锂的露点温度(Calculate dew temperature of LiBr)
 
 satsaturationTemperatureH2O_C:水的饱和温度（摄氏度）
 concentrationOfLiBrSolution :100kg 溴化锂水溶液中含有溴化锂的千克数
 此方程试用范围：
 0℃ < satsaturationTemperatureH2O_C < 100℃
 45% < concentrationOfLiBrSolution < 65%
 */

double dewTLiBr(double satsaturationTemperatureH2O_C, double concentrationOfLiBrSolution){
    
    double a[]={0.770033,1.45455e-2,-2.63906e-4,2.27609e-6};
    double b[]={140.877,-8.55749,0.16709,-8.82641e-4};
    
    double t= satsaturationTemperatureH2O_C;
    double x = concentrationOfLiBrSolution;
    
    double sum1 =0.000000 ,sum2=0.000000;
    
    //循环语句用于求和
    for (int i =0; i<4; i++) {
        sum1+=t*a[i]*pow(x, i);
        sum2+=b[i]*pow(x, i);
    }
    
    double dewTLiBr = sum1 + sum2;
    
    return dewTLiBr;
}


/*
 已知溶液的温度t和压强P,确定溶液的浓度X%,平均相对误差0.76%，最大相对误差1.749%
 t----压强为P时，溴化锂溶液的饱和温度，˚C
 t1----压强为P时，对应水的饱和温度，˚C，即需要先根据P求出水的饱和温度
 10˚ ≤ t ≤ 130˚C
 2kpa ≤ P ≤ 1500kpa
 */
double _concentration_LiBrSolution(double solutionTemperatureLiBr_C,double pressure_kPa){
    double t = solutionTemperatureLiBr_C;
    double t1 = saturationTemperatureH2O(pressure_kPa);
    double a[] = {0.31057,-1.282e-2,-1.7312e-4,5.3303e-7};
    double b[] = {1.232e-2,3.846e-4,-7.1457e-8,-5.73e-9};
    double c[] = {-1.9166e-4,-3.334e-6,5.3123e-8,-3.6012e-10,1.0257e-12};
    double d[] = {1.6386e-6,-2.16e-8,1.505e-10,-4.678e-13};
    double sum1 = 0.000000,sum2= 0.000000,sum3 = c[4]*pow(t1, 4),sum4 = 0.000000;
    
    double x = 0.0000000;
    
    for (int i = 0; i < 4; i++) {
        sum1 += a[i] * pow(t1, i);
        sum2 += b[i] * pow(t1, i);
        sum3 += c[i] * pow(t1, i);
        sum4 += d[i] * pow(t1, i);
    }
    
    x = sum1 + sum2*t + sum3*t*t + sum4*t*t*t;
    
    return x * 100;
}

/*计算溴化锂水溶液的焓值（Calculate the enthalpy of LiBr solution）单位：kcal/kg;
 
 solutionTemperatureLiBr_C: 溴化锂溶液的温度，˚C
 concentrationOfLiBrSolution :100kg 溴化锂水溶液中含有溴化锂的千克数
 
 
 solutionTemperatureLiBr_C ≤ 200 ˚C
 30% < concentrationOfLiBrSolution < 75%
 
 1千卡(kcal)=1大卡=4.184千焦(kJ)
 测试数据：
 t = 45.83
 x = 58.998
 h = 282.773
 */
double enthalpyLiBrSolution(double solutionTemperatureLiBr_C,double concentrationOfLiBrSolution){
    double a[] = {3.22313e2,3.83413e2,-2.65438e3,2.87262e3};
    double b[] = {4.19928,-9.39005,1.60770e1,-1.36171e1};
    double c[] = {1.00479e-3,-1.41857e-3,-2.06186e-3,5.92438e-3};
    double sum1 = 0.00000000 , sum2 = 0.0000000 , sum3 = 0.0000000;
    double t = solutionTemperatureLiBr_C;
    double x = concentrationOfLiBrSolution/100;
    double h;
    /*
     sum1 = ∑ax^n
     
     */
    for (int i=0; i<4; i++) {
        sum1 += a[i]*pow(x,i);
        sum2 += b[i]*pow(x, i);
        sum3 += c[i]*pow(x, i);
    }
    
    h = sum1 + sum2*t + sum3*t*t;
    
    h = conversionQ_kCal2kJ(h);
    
    return  h;
}
