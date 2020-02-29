#include <iostream>
#include<math.h>
using namespace std;


class Point{
    private:
        float x;
        float y;
    public:
        Point(float a, float b){
            x = a;
            y = b;
        }
        Point(){}
        float get_x(){
            return x;
        }
        float get_y(){
            return y;
        }
        void translate_point(float a, float b){
            x+=a;
            y+=b;
        }
        void rotate_point(float angle){
            float xnew = x*cos(angle) - y*sin(angle);
            float ynew = x*sin(angle) + y*cos(angle);
            x = xnew;
            y = ynew;
        }
        bool check_line(Point a, Point b, Point c, Point d){
            float slope = ((a.get_y()-b.get_y)/(a.get_x()-b.get_x()));
            float intercept = a.get_y() - slope*a.get_x();
        }
        
};


class Region: public Point{
    private:
       Point origin;
    public:
        Region(){
            Point temp(0,0);
            origin = temp;
        }
        virtual bool contains_point(Point x){
            return false;
        }
        virtual void translate(int x, int y){

        }
        virtual void rotate(float angle){

        }
};

class Basic: public Region{
    private:
        Region *r ;
    public:
        Basic(Region *b){
            r = b;
        }
        bool contains_point(Point a){
            return r->contains_point(a);
        }

        void translate(float x, float y){
            r->translate(x,y);
        }

        void rotate(float angle){
            r->rotate(angle);
        }
};


class Union: public Region{
    private:
        Region *r1, *r2 ;
    public:
        Union(Region *b, Region *c){
            r1 = b;
            r2 = c;
        }
        bool contains_point(Point a){
            if( r1->contains_point(a) || r2->contains_point(a)) return true;
            else return false;
        }

        void translate(float x, float y){
            r1->translate(x,y);
            r2->translate(x,y);
        }

        void rotate(float angle){
            r1->rotate(angle);
            r2->rotate(angle);
        }
};

class Complement: public Region{
    private:
        Region *r;
    public:
        Complement(Region *b){
            r = b;
        }
        bool contains_point(Point a){
            return !(r->contains_point(a));
        }

        void translate(float x, float y){
            r->translate(x,y);
        }

        void rotate(float angle){
            r->rotate(angle);
        }
};

class Intersection: public Region{
    private:
        Region *r1, *r2 ;
    public:
        Intersection(Region *b, Region *c){
            r1 = b;
            r2 = c;
        }
        bool contains_point(Point a){
            if( r1->contains_point(a) && r2->contains_point(a)) return true;
            else return false;
        }

        void translate(float x, float y){
            r1->translate(x,y);
            r2->translate(x,y);
        }

        void rotate(float angle){
            r1->rotate(angle);
            r2->rotate(angle);
        }
};




class Circle: public Basic{
    private:
        Point centre;
        int radius;
    public:
        Circle(Region *x, float a, float b, float c): Basic(x){
            Point temp(a,b);
            centre = temp;
            radius = c;
        }
        
        bool contains_point(Point a){
            if(pow(abs(a.get_x()-centre.get_x()),2) + pow(abs(a.get_y()-centre.get_y()), 2) <= pow(radius,2)){
                return true;
            }
            else return false;
        }

        void translate(int x, int y){
            centre.translate_point(x,y);
        }

        void rotate(float angle){
            centre.rotate_point(angle);
        }
};


// class Triangle: public Basic{
//     public: 
//     Point a,b,c;
//     Triangle(Region *x, Point a1, Point b1, Point c1): Basic(x){
//         a = a1;
//         b = b1;
//         c = c1;
//     }

//     bool contains_point(Point a){
        
//     }

//     void tranlate(float x, float y){
//         a.translate_point(x,y);
//         b.translate_point(x,y);
//         c.translate_point(x,y);
//     }
// };



int main(){
    Region *r, *r1, *r2 ;
    Circle c(r1,0,0,1);

    Point p(0,1);
    r1 = &c;
    
    // p.rotate_point(M_PI/2);
    // cout<<p.get_x()<<" "<<p.get_y();
    // cout<<u.contains_point(p);
    cout<<r->contains_point(p);
    r->rotate(M_PI);
    cout<<r->contains_point(p);
}