#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include "io.h"

using namespace std;

#define PI 3.1415927

double DegMod(double Angle)
    {
      while(Angle >= 360)
         {
           Angle -= 360;
         }
      while(Angle < 0)
         {
           Angle += 360;
         }
      return Angle;
    }

int main()
    {
      int second = 0;
      bool catches = 0, reaches = 0;
      double mouseAngle=0, catAngle=0, catRadius=0;

      mouseAngle = getParam("Please enter the initial mouse angle: ");
      mouseAngle = DegMod(mouseAngle);
      catAngle = getParam("Please enter the initial cat angle: ");
      catAngle = DegMod(catAngle);

      catRadius = getParam("Please enter the initial cat radius: ");
      while(catRadius < 1)
         {
           cout<<"Error: the cat radius is less than the base radius 1!"<<endl;
           catRadius = getParam("Please enter the initial cat radius: ");
         }

      printHeader();


      if (catRadius == 1)
         {
           reaches = 1;
         }

      while((second <= 30) && (reaches == 0))
         {
           printData(second, mouseAngle, catAngle, catRadius); 

           if ((catRadius) * cos ((catAngle - mouseAngle)*PI/180) >= 1)
              {
                if (catRadius > 2)
                   {
                     catRadius--;
                   }
                else
                   {
                     catRadius = 1;
                     reaches = 1;
                   }    
              }
           else
              {
                catAngle += (1.25/catRadius)*180/PI;
                catAngle = DegMod(catAngle);
              }
         
           mouseAngle += 180/PI;
           mouseAngle = DegMod(mouseAngle); 

           second ++;
         }

      if (reaches ==1)
         {
           double Delta = mouseAngle - catAngle;
           Delta = DegMod(Delta);
           while ((Delta >= 0) && (second <= 30))
              {
                printData(second, mouseAngle, catAngle, catRadius);
                Delta -= 0.25*180/PI;

                catAngle += 1.25*180/PI;
                catAngle = DegMod(catAngle);
                mouseAngle += 180/PI;
                mouseAngle = DegMod(mouseAngle); 
                second++;
              }
           
           if ((Delta < 0) && (second <= 30))
              {
                printData(second, mouseAngle, catAngle, catRadius);
                catches = 1;
              }
         }

      printResult(catches);
      return 0;
    }
