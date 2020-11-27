#include "define.h"

class count{
        private:
        unsigned int M1,M2,VES,cal,cal2;
        float F1,F2,V,V2;
        const float TEMP=10000;
        char out[10],out2[10];
        Vector <int> MS,MS2,MS_,MS2_,MS3_;
        Vector <float> V_,V2_,V_l;
        void test_(){
            V= random(100,300)/100; 
        }
        void sensor(){
             V = ina3221.getBusVoltage_V(CH_1);
             dtostrf(V,7, 3, out);
        }
        void myDelayMicroseconds(uint32_t us) {
  uint32_t tmr = micros();
  while (micros() - tmr < us);
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
        void massa_c(){
            for(unsigned int i=1;i<V_.size();i++){ 
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
             if (cal2==0) for(unsigned int i=2;i<V_l.size();i++){ 
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

        template <typename ...T> 
        void vec(Vector <float> &m, float a, T... b){
            m.push_back(a);
            vec(m,b...);
        } 
        template <typename ...T> 
        void vec(Vector <float> &m){} 
        
        public:
        void initalization(int i,int j){
            cal=i;
            cal2=j;
            if (cal!=0 && V_.size()!=cal) for (unsigned int i=0;i<V_.size()-cal;i++) {MS.pop_back();MS2.pop_back();V_.pop_back();}
            if (cal2!=0 && V2_.size()!=cal2) for (unsigned int i=0;i<V2_.size()-cal2;i++) {MS3_.pop_back();MS_.pop_back();MS2_.pop_back();V2_.pop_back();V_l.pop_back();}
        }//  Use if you have 1 sensor or more(Use when the data doesn't match      
               
        void Massa(int a,int b,int c,int d, int e,int f){
            abc(MS,a,b,c,d,e,f);
        }  // For trucks with 1 sensor or more 
            
        void Massa2(int a,int b,int c,int d, int e,int f){
            abc(MS2,a,b,c,d,e,f);
        } // For trucks with 1 sensor or more 
        
        void Massa_lazy(int a,int b,int c,int d, int e,int f){
            abc(MS_,a,b,c,d,e,f);
        }// For trucks with 2 sensors(Lazy)
        void Massa_lazy2(int a,int b,int c,int d, int e,int f){
            abc(MS2_,a,b,c,d,e,f);
        }//For trucks with Lazy-system 
        void Massa_lazy3(int a,int b,int c,int d, int e,int f){
            abc(MS3_,a,b,c,d,e,f);
        }//For trucks with Lazy-system

        // Functions for calibration data(The Weight of the truck)
  
        void Voltage(float a, float b, float c,float d,float e, float f){
            vec(V_,a,b,c,d,e,f);
        } // For trucks with 1 sensor or more 
        void Voltage2(float a, float b, float c,float d,float e, float f){
             vec(V2_,a,b,c,d,e,f);
        } // For trucks with 2 sensors only 
        void Voltage_lazy(float a, float b, float c,float d,float e, float f){
            vec(V_l,a,b,c,d,e,f);
        } // For trucks with 2 sensors only 
        //Functions for calibration data(The voltage of the sensors)
        void test(){
        test_();
        massa_c();
        Serial.print("M1= ");Serial.println(M1); Serial.print("M2= ");Serial.println(M2);
        Serial.print("INPUT V1= ");Serial.println(V);
        Serial.print("INPUT V2= ");Serial.println(V2);

        }
        
};