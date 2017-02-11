#include "stats.h"
#include <assert.h>
using namespace std;
using namespace main_savitch_2C;


statistician::statistician()
{
count =0;
total = 0;
}
void statistician::next(double r)
{
    if (count ==0){
        tinyest = r;
        }
    if (count == 0){
        largest = r;
    }
    if (tinyest > r){
        tinyest = r;
    }
    if (largest < r){
        largest = r;
    }
    count++;
    total +=r;
}
void statistician::reset()
{
    count = 0;
    total = 0;
    tinyest = 0;
    largest = 0;
}
int statistician::length() const
{

    return count;
}
double statistician::sum() const
{
    return total;
}
double statistician::mean()const
{
    assert (length()>0);
    return total/count;
}
double statistician::minimum()const
{

    return tinyest;
}
double statistician::maximum()const
{

    return largest;
}

namespace main_savitch_2C{

statistician operator+(const statistician& s1, const statistician& s2)
{
    if (s1.length()==0 && s2.length()==0){
        return s1;
    }
    else if ( s2.length()==0){
        return s1;
    }
    else if (s1.length()== 0){
        return s2;
    }
    else{
    statistician s3;
    s3.count = s1.length()+s2.length();
    s3.total = s1.sum() + s2.sum();
    if (s1.minimum()< s2.minimum()){
        s3.tinyest = s1.minimum();
    }
    else {
        s3.tinyest = s2.minimum();
         }

    if (s1.maximum()> s2.maximum()){
        s3.largest = s1.maximum();
    }
    else{
        s3.largest = s2.maximum();
        }
        return s3;
    }
}
statistician operator * (double scale, const statistician& s){
    if(s.length()==0){
        return s;
    }
    statistician s3;
    s3.count = s.length();
    s3.total = (s.sum()*scale);
    if(scale<0){
        s3.tinyest=s.maximum()*scale;
        s3.largest = s.minimum()*scale;
    }
    else if (scale>=0){
        s3.tinyest=s.minimum()*scale;
        s3.largest=s.maximum()*scale;
    }
    return s3;

}
bool operator ==(const statistician& s1, const statistician& s2)
{

    return
        (s1.length() == s2.length())    &&
        (s1.sum() == s2.sum())          &&
        (s1.minimum() == s2.minimum())  &&
        (s1.maximum() == s2.maximum());

}
}

