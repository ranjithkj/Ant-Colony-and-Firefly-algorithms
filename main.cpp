//
//  main.cpp
//  Firefly
//
//  Created by Ranjith Kumar on 2015-12-01.
//  Copyright (c) 2015 Ranjith Kumar. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <ctime>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>

#define EPS 1e-3


using namespace std;
ofstream File("/Users/ranjith/Desktop/Firefly/Results.txt");
vector<vector<double> >Position;
vector<vector<double> >  finalposition;
int iter=0;
double objectivefunction(vector <double> v)
{
    float d= 0.0297*(v[0])+1.615*(v[1])-0.00488*((v[0])*(v[2]));
    float I=d;
    return I;
}
vector<double> generatepop ()
{
    //Random-Intensity,Coordinates(x,y,z)
    //Intensity=0;
    vector<double> Coordinate;
    vector<vector<double> >Coordinates;
    vector<double> Objective;
    //vector<double> ;
    float j,k,l;
    srand(time(NULL));
    
    for(int i=0;i<200;i++)
    {
        //srand(rand());
        j=rand()%7+4;
        k=(rand()%16+15.0)/100.0;
        l=rand()%5+1;
        Coordinate.push_back(j);
        Coordinate.push_back(k);
        Coordinate.push_back(l);
        Objective.push_back(objectivefunction(Coordinate));
        Coordinates.push_back(Coordinate);
        Coordinate.resize(0);
    }
    Position=Coordinates;
    for(int i=0;i<Coordinates.size();i++)
    {
        for(int j=0;j<Coordinates[i].size();j++)
        {
            cout<<Coordinates[i][j]<<",";
        }
        cout<<endl;
        
    }
    cout<<"population generated"<<endl;
    cin.get();
    for(int i=0;i<Objective.size();i++)
    {
        cout<<Objective[i]<<",";
        cout<<endl;
    }
    cout<<"objective function:"<<endl;
    cin.get();
    return Objective;
    
}
vector<double> altercoordinate(vector<double> v1,vector<double> v2)
{
    float alpha;
    alpha=0.2*(pow(0.9,(1-(iter/10))));
    
    float x,y,z,rx,ry,rz,r;
    float x1,y1,z1;
    x1=v1[0];
    y1=v1[1];
    z1=v1[2];
    srand(time(NULL));
    vector<double> pos;
    rx=v2[0]-v1[0];
    ry=v2[1]-v1[1];
    rz=v2[2]-v1[2];
    r=sqrt(pow(rx,2)+pow(ry,2)+pow(rz,2));
    x=v1[0]+ exp((-1)*pow(r,2))+ alpha*((double)rand() / ((double)RAND_MAX-0.5));
    y=v1[1]+ exp((-1)*pow(r,2))+ alpha*((double)rand() / ((double)RAND_MAX-0.5));
    z=v1[2]+ exp((-1)*pow(r,2))+ alpha*((double)rand() / ((double)RAND_MAX-0.5));
    if(x>=10.1||x<4||z<1||z>=5.1||y<0.15||y>=0.31)
    {
        cout<<"Warning";
        cout<<"X: "<<x<<" Y: "<<y<<" Z: "<<z;
        x=x1;
        y=y1;
        z=z1;
    }
    
    pos.push_back(x);
    pos.push_back(y);
    pos.push_back(z);
    return pos;
    //pos.resize(0);
}
vector<vector<double> > ranksolns(vector<double> &ObjValue,vector<vector<double> >v2)
{
    vector<double> v1;
    vector<double> temp1;
    v1=ObjValue;
    finalposition.resize(0);
    temp1.resize(0);
    finalposition=v2;
    int i, j, flag = 1;    // set flag to 1 to start first pass
    double temp;
    for(i = 1; (i <= v1.size()) && flag; i++)
    {
        flag = 0;
        for (j=0; j < ((v1.size()) -1); j++)
        {
            if (v1[j+1] > v1[j])      // ascending order simply changes to <
             {
                temp1=finalposition[j];
                finalposition[j]=finalposition[j+1];
                finalposition[j+1]=temp1;
                temp = v1[j];             // swap elements
                v1[j] = v1[j+1];
                v1[j+1] = temp;
                flag = 1;               // indicates that a swap occurred.
             }
         }
    }
    ObjValue=v1;
    return finalposition;
}

int main()
{

    vector<double> ObjValue;
    ObjValue= generatepop();
    while(iter<10)
    {
      for(int m=0; m<ObjValue.size();m++)
      {
        for(int n=m+1; n<ObjValue.size();n++)
        {
            
              if(ObjValue[m]>ObjValue[n])
             {
                Position[m]=altercoordinate(Position[m], Position[n]);
                ObjValue[m]=objectivefunction(Position[m]);
             }
                
            //update intensity
        }
        
     }
        for(int i=0;i<Position.size();i++)
      {
        for(int j=0;j<Position[i].size();j++)
        {
            cout<<Position[i][j]<<",";
        }
        cout<<endl;
      }
        
    for(int i=0;i<ObjValue.size();i++)
    {
        cout<<ObjValue[i]<<endl;
    }
        cout<<"Updated Objective Values of the fireflies"<<endl<<"We are the "<<iter<<"th iteration"<<endl;
    finalposition=ranksolns(ObjValue,Position);
    for(int i=0;i<finalposition.size();i++)
    {
        for(int j=0;j<finalposition[i].size();j++)
        {
            cout<<finalposition[i][j]<<",";
        }
        cout<<endl;
    }
       
    
        iter++;
  }
    File << "Solutions"<<endl;
    for(int i=0;i<finalposition.size();i++)
    {
        if(i<=10)
        {
            File << i <<". ";
           for(int j=0;j<finalposition[i].size();j++)
         {
            File<<finalposition[i][j]<<",";
            cout<<finalposition[i][j]<<",";
          }
           File<<endl;
          cout<<endl;
       }
    }

     File << "Index Values:"<<endl;
    for(int i=0;i<ObjValue.size();i++)
    {
        if(i<=10)
        {
            File << i <<".";
            File << ObjValue[i]<<endl;
          cout<<ObjValue[i]<<endl;
        }
    }
     cin.get();
    
    
}








