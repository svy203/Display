#include "define.h"

class count{
        private:
        static int M1,M2,VES,cal,cal2;
        static float F1,F2,TEMP=10000,V,V2;
        static char out[10],out2[10];
        Vector <int> MS,MS2,MS3,MS_,MS2_;
        Vector <float> V_,V2_,V_l;
        void sensor(){
             V = ina3221.getBusVoltage_V(CH_1);
             dtostrf(V,7, 3, out);
        }
        void _sw(uint8_t i){
         if (i > 7) return;
         Wire.beginTransmission(TCAADDR);
         Wire.write(1 << i);
         Wire.endTransmission();  
        }
        void sensors(){
         _sw(0);
        V = ina3221.getBusVoltage_V(CH_1);
        _sw(1);
        V2 = ina3221.getBusVoltage_V(CH_1);
        dtostrf(V,7, 3, out);
        dtostrf(V2,7, 3, out2);
        }
        void massa(){
            for(int i=2;i<V_.size();i++){ 
                int j,j2;
                if (V<=V_[1]){j=1;j2=0;}
                else if (V>V_[i-1]) {j=i;j2=i-1;}
                M1= ((MS[j]-MS[j2])*V+V_[j]*MS[j2]-V_[j2]*MS[j])/(V_[j]-V_[j2]);
                M2= ((MS2[j]-MS2[j2])*V+V_[j]*MS2[j2]-V_[j2]*MS2[j])/(V_[j]-V_[j2]);
              
            }
            if (M1<0) M1=0;
            if (M2<0) M2=0;
            VES=M1+M2; 
        }
        void lazy(){
             if (cal2==0) for(int i=2;i<V_l.size();i++){ 
                int j,j2;
                if (V<=V_[1]){j=1;j2=0;}
                else if (V>V_[i-1]) {j=i;j2=i-1;}
                M1= ((MS_[j]-MS_[j2])*V+V_[j]*MS[j2]-V_[j2]*MS[j])/(V_[j]-V_[j2]);
                M2= ((MS2_[j]-MS2_[j2])*V+V_[j]*MS2[j2]-V_[j2]*MS2[j])/(V_[j]-V_[j2]);
              
            }
            else 
            if (M1<0) M1=0;
            if (M2<0) M2=0;
            VES=M1+M2; 
        }
       
                      
        void setup_dsp(){
            tft.begin(0x9341);
            tft.setRotation(1);    //Landscape
            tft.fillScreen(Blue);
            delay(200);
        }
        template <typename ...T> 
        void abc(Vector <int> &m, int a, T... b){
            m.push_back(a);
            abc(m,b...);
        } 
        template <typename ...T> 
        void abc(Vector <int> &m){} 
        
        public:
        void initalization(int i,int j){
            cal=i;
            cal2=j;
        }// Number of calibrations       
               
        void Massa(int a,int b,int c,int d, int e,int f){
            abc(MS,a,b,c,d,e,f);
        }  // For trucks with 1 sensor or more 
  
            
         
        void Massa2(int a,int b,int c,int d, int e,int f){
            MS2.push_back(a);MS2.push_back(b);MS2.push_back(c);
            MS2.push_back(d);MS2.push_back(e);MS2.push_back(f);
        } // For trucks with 1 sensor or more 
        
        void Massa3(int a,int b,int c,int d, int e,int f){
            MS3.push_back(a);MS3.push_back(b);MS3.push_back(c);
            MS3.push_back(d);MS3.push_back(e);MS3.push_back(f);
        }// For trucks with 2 sensors(Lazy)
        void Massa_lazy(int a,int b,int c,int d, int e,int f){
            MS_.push_back(a);MS_.push_back(b);MS_.push_back(c);
            MS_.push_back(d);MS_.push_back(e);MS_.push_back(f);
        }//For trucks with Lazy-system 
        void Massa2_lazy(int a,int b,int c,int d, int e,int f){
            MS2_.push_back(a);MS2_.push_back(b);MS2_.push_back(c);
            MS2_.push_back(d);MS2_.push_back(e);MS2_.push_back(f);
        }//For trucks with Lazy-system

        // Functions for calibration data(The Weight of the truck)
  
        void Voltage(float a, float b, float c,float d,float e, float f){
            V_.push_back(a);V_.push_back(b);V_.push_back(c);
            V_.push_back(d);V_.push_back(e);V_.push_back(f);
        } // For trucks with 1 sensor or more 
        void Voltage2(float a, float b, float c,float d,float e, float f){
            V2_.push_back(a);V2_.push_back(b);V2_.push_back(c);
            V2_.push_back(d);V2_.push_back(e);V2_.push_back(f);
        } // For trucks with 2 sensors only 
        void Voltage_lazy(float a, float b, float c,float d,float e, float f){
            V_l.push_back(a);V_l.push_back(b);V_l.push_back(c);
            V_l.push_back(d);V_l.push_back(e);V_l.push_back(f);
        } // For trucks with 2 sensors only 
        //Functions for calibration data(The voltage of the sensors)
        
        void flush(){
            if (cal!=0 && V_.size()!=cal) for (int i=0;i<V_.size()-cal;i++) {MS.pop_back();MS2.pop_back();V_.pop_back();}
            if (cal2!=0 && V2_.size()!=cal2) for (int i=0;i<V2_.size()-cal2;i++) {MS3.pop_back();MS_.pop_back();MS2_.pop_back();V2_.pop_back();V_l.pop_back();}

        } // Use if you have 1 sensor or more(Use when the data doesn't match)  
};