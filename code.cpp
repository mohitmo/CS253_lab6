#include <iostream>
#include<math.h>
#include<iomanip>
using namespace std;


class Point{
    private:
        double x;
        double y;
    public:
        Point(double a, double b){
            x = a;
            y = b;
        }
        Point(){}
        double get_x(){
            return x;
        }
        double get_y(){
            return y;
        }
        void translate_point(double a, double b){
            x+=a;
            y+=b;
        }
        void rotate_point(double angle){
            double xnew = x*cos(angle) - y*sin(angle);
            double ynew = x*sin(angle) + y*cos(angle);
            x = xnew;
            y = ynew;
        }

        bool check_line( Point b, Point c, Point d){

            double slope = (( y-b.get_y() )/( x-b.get_x()));
            double intercept = y - slope*x;
            
            double sat1 = (c.get_y()-y)*(b.get_x()-x) - (b.get_y()-y)*(c.get_x()-x);
            double sat2 = (d.get_y()-y)*(b.get_x()-x) - (b.get_y()-y)*(d.get_x()-x);

            if(sat1*sat2 >= 0.0) return true;
            else return false;
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
        virtual void rotate(double angle){

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

        void translate(double x, double y){
            r->translate(x,y);
        }

        void rotate(double angle){
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

        void translate(double x, double y){
            r1->translate(x,y);
            r2->translate(x,y);
        }

        void rotate(double angle){
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

        void translate(double x, double y){
            r->translate(x,y);
        }

        void rotate(double angle){
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

        void translate(double x, double y){
            r1->translate(x,y);
            r2->translate(x,y);
        }

        void rotate(double angle){
            r1->rotate(angle);
            r2->rotate(angle);
        }
};




class Circle: public Basic{
    private:
        Point centre;
        int radius;
    public:
        Circle(Region *x, double a, double b, double c): Basic(x){
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

        void rotate(double angle){
            centre.rotate_point(angle);
        }
};


class Triangle: public Basic{
    private: 
        Point a,b,c;
    public:
        Triangle(Region *x, Point a1, Point b1, Point c1): Basic(x){
            a = a1;
            b = b1;
            c = c1;
        }

        bool contains_point(Point x){
            if(a.check_line(b,c,x) && b.check_line(c,a,x) && c.check_line(a,b,x)) return true;
            else return false;
        }

        void translate(double x, double y){
            a.translate_point(x,y);
            b.translate_point(x,y);
            c.translate_point(x,y);
        }
        void rotate(double angle){
            a.rotate_point(angle);
            b.rotate_point(angle);
            c.rotate_point(angle);
        }
};


class Square: public Basic{
    private:
        Point a,b,c,d;
    public:
        Square(Region *x, Point a1, Point b1, Point c1, Point d1): Basic(x){
            a = a1;
            b = b1;
            c = c1;
            d = d1;
        }

        bool contains_point(Point x){
            if(a.check_line(b,c,x) && b.check_line(c,a,x) && c.check_line(d,b,x) && d.check_line(a,c,x)) return true;
            else return false;
        }

        void translate(double x, double y){
            a.translate_point(x,y);
            b.translate_point(x,y);
            c.translate_point(x,y);
            d.translate_point(x,y);
        }
        void rotate(double angle){
            a.rotate_point(angle);
            b.rotate_point(angle);
            c.rotate_point(angle);
            d.rotate_point(angle);
        }
        void getPoints(){
            cout<<a.get_x()<<" "<<a.get_y()<<"\n";
            cout<<b.get_x()<<" "<<b.get_y()<<"\n";
            cout<<c.get_x()<<" "<<c.get_y()<<"\n";
            cout<<d.get_x()<<" "<<d.get_y()<<"\n";
        }
};

class Rectangle: public Basic{
    private:
        Point a,b,c,d;
    public:
        Rectangle(Region *x, Point a1, Point b1, Point c1, Point d1): Basic(x){
            a = a1;
            b = b1;
            c = c1;
            d = d1;
        }

        bool contains_point(Point x){
            if(a.check_line(b,c,x) && b.check_line(c,a,x) && c.check_line(d,b,x) && d.check_line(a,c,x)) return true;
            else return false;
        }

        void translate(double x, double y){
            a.translate_point(x,y);
            b.translate_point(x,y);
            c.translate_point(x,y);
            d.translate_point(x,y);
        }
        void rotate(double angle){
            a.rotate_point(angle);
            b.rotate_point(angle);
            c.rotate_point(angle);
            d.rotate_point(angle);
        }
};


int main(){
    cout<<fixed;
    cout<<  setprecision(6);
    Point p1(0,0), p2(1,0), p3(1,1), p4(0,1), p5(1, 1.0001), p6(2,0), p7(2,1);
    Region *r1, *r2, *r3, *r4;
    Square s(r1,p1,p2,p3,p4);
    r1 = &s;
    r1->translate(1,0);
    Circle c(r2,1,1,1);
    r2 = &c;
    Intersection i(r1,r2);
    r3 = &i;
    Square t(r3, p2, p6, p7, p3);
    r4 = &t;
    Intersection i2(r3, r4);
    cout<<i2.contains_point(p5);

}