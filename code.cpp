#include <iostream>
#include<math.h>
// #include "package.h"
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
        virtual void translate(double x, double y){

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
            if( r1->contains_point(a) && r2->contains_point(a)){
                cout<<"point is inside the intersection";
                return true;
            }
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
        Circle(Region *x, Point p, double r): Basic(x){
            centre = p;
            radius = r;
        }

        bool contains_point(Point a){
            if(pow(abs(a.get_x()-centre.get_x()),2) + pow(abs(a.get_y()-centre.get_y()), 2) <= pow(radius,2)){
                return true;
            }
            else return false;
        }

        void translate(double x, double y){
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
    // Origin is (0,0)
    // All rotations and translations will be done with repect to it.
    // If a point is inside a region 1 will be returned else 0.

    // 1. Circle
    {
        cout << "\nCircle : " << endl;
        Region *r, *r1, *r2;

        Point a(1,0), cent(1,1);

        float rad = 1;
        
        Circle c(r,cent,rad), c_copy(r1,cent,rad), c_copy2(r2,cent, rad);  // cent is Point for Centre and 1 is radius of circle

        r = &c;
        r1 = &c_copy;
        r2 = &c_copy2;

        cout << "\n1. Checking where Point (" << a.get_x() << "," << a.get_y() <<") lies with respect to circle with centre (" << cent.get_x() << "," << cent.get_y() <<") having radius "<< rad << endl;

        if (r->contains_point(a)) cout<<"\tPoint is inside the region"<< endl;
        else cout<<"\tPoint is outside the region" << endl;


        Point b(2,3);


        cout << "\n2. Checking where Point (" << b.get_x() << "," << b.get_y() <<") lies with respect to circle with centre (" << cent.get_x() << "," << cent.get_y() <<") having radius "<< rad << endl;
        if (r->contains_point(b)) cout<<"\tPoint is inside the region"<< endl;
        else cout<<"\tPoint is outside the region" << endl;

        float x = 3, y = 3;


        cout << "\n3. Translating region's x coordinate by " << x << " and y coordinate by " << y << " unit" << endl;
        r1->translate(x,y);


        Point a1(1,0);
        cout << "\n4. Checking where Point (" << a1.get_x() << "," << a1.get_y() <<") lies with respect to circle with centre (" << cent.get_x() << "," << cent.get_y() <<") having radius "<< rad << " and also its translated version " << endl;


        if(r->contains_point(a1) && !r1->contains_point(a1)) cout<<"\tPoint is inside inital region but outside translated region" << endl;
        else cout << "\tCan't say" << endl;

        Point b1(4,3);

        cout << "\n5. Checking where Point (" << b1.get_x() << "," << b1.get_y() <<") lies with respect to circle with centre (" << cent.get_x() << "," << cent.get_y() <<") having radius "<< rad << " and also its translated version " << endl;


        if(!r->contains_point(b1) && r1->contains_point(b1)) cout<<"\tPoint is outside inital region but inside translated region" << endl;
        else cout << "\tCan't say" << endl;

        cout << "\n6. Rotating initial circle " << endl;
        r2->rotate(M_PI/4);

        Point a2(1,0), b2(-0.5,1);

        cout << "\n7. Checking where Point (" << a2.get_x() << "," << a2.get_y() <<") lies with respect to circle with centre (" << cent.get_x() << "," << cent.get_y() <<") having radius "<< rad << " and also its rotated version " << endl;

        if(r->contains_point(a2) && !r2->contains_point(a2)) cout<<"\tPoint is inside inital region but outside rotated region" << endl;
        else cout << "\tCan't say" << endl;


        cout << "\n8. Checking where Point (" << b2.get_x() << "," << b2.get_y() <<") lies with respect to circle with centre (" << cent.get_x() << "," << cent.get_y() <<") having radius "<< rad << " and also its rotated version " << endl;

        if(!r->contains_point(b2) && r2->contains_point(b2)) cout<<"\tPoint is inside rotated region but outside inital region" << endl;
        else cout << "\tCan't say" << endl;
    }

    //2. Triangle
    {
        cout << "\nTriangle : " << endl;
        Region *r, *r1, *r2;
        Point p1(0,0), p2(1,0), p3(0,1); // 3 Points to form a triangle

        Point a(0,0.2);
        Triangle t(r,p1,p2,p3), t1(r1,p1,p2,p3), t_copy2(r2,p1,p2,p3);  // cent is Point for Centre and 1 is radius of circle
        Region *ra, *rb;
        r = &t;
        r1 = &t1;
        r2 = &t_copy2;

        cout << "\n1. Checking where Point (" << a.get_x() << "," << a.get_y() <<") lies with respect to triangle with vertices (" << p1.get_x() << "," << p1.get_y() <<") , (" << p2.get_x() << "," << p2.get_y() <<") , (" << p3.get_x() << "," << p3.get_y() <<") " << endl;

        if (r->contains_point(a)) cout<<"\tPoint is inside the region"<< endl;
        else cout<<"\tPoint is outside the region" << endl;


        Point b(2,3);


        cout << "\n2. Checking where Point (" << b.get_x() << "," << b.get_y() <<") lies with respect to triangle with vertices (" << p1.get_x() << "," << p1.get_y() <<") , (" << p2.get_x() << "," << p2.get_y() <<") , (" << p3.get_x() << "," << p3.get_y() <<") " << endl;
        if (r->contains_point(b)) cout<<"\tPoint is inside the region"<< endl;
        else cout<<"\tPoint is outside the region" << endl;

        double x = 3, y = 3;

        cout << "\n3. Translating region's x coordinate by " << x << " and y coordinate by " << y << " unit" << endl;

        r1->translate(x,y);
        // t1.translate(x,y);

        Point a1(1,0);


        cout << "\n4. Checking where Point (" << a1.get_x() << "," << a1.get_y() <<") lies with respect to triangle with vertices (" << p1.get_x() << "," << p1.get_y() <<") , (" << p2.get_x() << "," << p2.get_y() <<") , (" << p3.get_x() << "," << p3.get_y() <<") and its translated version" << endl;


        if( r->contains_point(a1) && !r1->contains_point(a1) ) cout<<"\tPoint is inside inital region but outside translated region" << endl;
        else cout << "\tCan't say" << endl;


        Point b1(3,3);


        cout << "\n5. Checking where Point (" << b1.get_x() << "," << b1.get_y() <<") lies with respect to triangle with vertices (" << p1.get_x() << "," << p1.get_y() <<") , (" << p2.get_x() << "," << p2.get_y() <<") , (" << p3.get_x() << "," << p3.get_y() <<") and its translated version" << endl;


        if(!r->contains_point(b1) && r1->contains_point(b1)) cout<<"\tPoint is outside inital region but inside translated region" << endl;
        else cout << "\tCan't say" << endl;

        cout << "\n6. Rotating initial triangle " << endl;
        r2->rotate(M_PI/2);

        Point a2(1,0), b2(-0.2,0.1);

        cout << "\n7. Checking where Point (" << a2.get_x() << "," << a2.get_y() <<") lies with respect to triangle with vertices (" << p1.get_x() << "," << p1.get_y() <<") , (" << p2.get_x() << "," << p2.get_y() <<") , (" << p3.get_x() << "," << p3.get_y() <<") and its rotated version" << endl;

        if(r->contains_point(a2) && !r2->contains_point(a2)) cout<<"\tPoint is inside inital region but outside rotated region" << endl;
        else cout << "\tCan't say" << endl;


        cout << "\n8. Checking where Point (" << b2.get_x() << "," << b2.get_y() <<") lies with respect to triangle with vertices (" << p1.get_x() << "," << p1.get_y() <<") , (" << p2.get_x() << "," << p2.get_y() <<") , (" << p3.get_x() << "," << p3.get_y() <<") and its rotated version" << endl;

        if(!r->contains_point(b2) && r2->contains_point(b2)) cout<<"\tPoint is inside rotated region but outside inital region" << endl;
        else cout << "\tCan't say" << endl;
    }

    // Square
    {
        cout << "\nSquare : " << endl;
        Region *r, *r1, *r2;
        Point p1(0,0), p2(1,0), p3(0,1), p4(1,1); // 4 Points to form a square

        Point a(0,0.2);
        Square s(r,p1,p2,p4,p3), s_copy(r,p1,p2,p4,p3), s_copy2(r,p1,p2,p4,p3);  // cent is Point for Centre and 1 is radius of circle

        r = &s;
        r1 = &s_copy;
        r2 = &s_copy2;

        cout << "\n1. Checking where Point (" << a.get_x() << "," << a.get_y() <<") lies with respect to square with vertices (" << p1.get_x() << "," << p1.get_y() <<") , (" << p2.get_x() << "," << p2.get_y() <<") , (" << p3.get_x() << "," << p3.get_y() <<") , (" << p4.get_x() << "," << p4.get_y() <<")"<< endl;

        if (r->contains_point(a)) cout<<"\tPoint is inside the region"<< endl;
        else cout<<"\tPoint is outside the region" << endl;


        Point b(2,3);


        cout << "\n2. Checking where Point (" << b.get_x() << "," << b.get_y() <<") lies with respect to square with vertices (" << p1.get_x() << "," << p1.get_y() <<") , (" << p2.get_x() << "," << p2.get_y() <<") , (" << p3.get_x() << "," << p3.get_y() <<") , (" << p4.get_x() << "," << p4.get_y() <<")"<< endl;

        if (r->contains_point(b)) cout<<"\tPoint is inside the region"<< endl;
        else cout<<"\tPoint is outside the region" << endl;

        double x = 3, y = 3;

        cout << "\n3. Translating region's x coordinate by " << x << " and y coordinate by " << y << " unit" << endl;

        r1->translate(x,y);
        // t1.translate(x,y);

        Point a1(1,0);
        cout << "\n4. Checking where Point (" << a1.get_x() << "," << a1.get_y() <<") lies with respect to square with vertices (" << p1.get_x() << "," << p1.get_y() <<") , (" << p2.get_x() << "," << p2.get_y() <<") , (" << p3.get_x() << "," << p3.get_y() <<") , (" << p4.get_x() << "," << p4.get_y() << ") and its translated version "<< endl;


        if( r->contains_point(a1) && !r1->contains_point(a1) ) cout<<"\tPoint is inside inital region but outside translated region" << endl;
        else cout << "\tCan't say" << endl;

        Point b1(3,3);

        cout << "\n5. Checking where Point (" << b1.get_x() << "," << b1.get_y() <<") lies with respect to square with vertices (" << p1.get_x() << "," << p1.get_y() <<") , (" << p2.get_x() << "," << p2.get_y() <<") , (" << p3.get_x() << "," << p3.get_y() <<") , (" << p4.get_x() << "," << p4.get_y() << ") and its translated version "<< endl;


        if(!r->contains_point(b1) && r1->contains_point(b1)) cout<<"\tPoint is outside inital region but inside translated region" << endl;
        else cout << "\tCan't say" << endl;

        cout << "\n6. Rotating initial square " << endl;
        r2->rotate(M_PI/2);

        Point a2(0.5,0.5), b2(-0.5,0.5);

        cout << "\n7. Checking where Point (" << a2.get_x() << "," << a2.get_y() <<") lies with respect to square with vertices (" << p1.get_x() << "," << p1.get_y() <<") , (" << p2.get_x() << "," << p2.get_y() <<") , (" << p3.get_x() << "," << p3.get_y() <<") , (" << p4.get_x() << "," << p4.get_y() << ") and its rotated version "<< endl;

        if(r->contains_point(a2) && !r2->contains_point(a2)) cout<<"\tPoint is inside inital region but outside rotated region" << endl;
        else cout << "\tCan't say" << endl;


        cout << "\n8. Checking where Point (" << b2.get_x() << "," << b2.get_y() <<") lies with respect to square with vertices (" << p1.get_x() << "," << p1.get_y() <<") , (" << p2.get_x() << "," << p2.get_y() <<") , (" << p3.get_x() << "," << p3.get_y() <<") , (" << p4.get_x() << "," << p4.get_y() << ") and its rotated version "<< endl;

        if(!r->contains_point(b2) && r2->contains_point(b2)) cout<<"\tPoint is inside rotated region but outside inital region" << endl;
        else cout << "\tCan't say" << endl;

    }

    {
        cout << "\nRectangle : " << endl;
        Region *r, *r1, *r2;
        Point p1(0,0), p2(2,0), p3(0,1), p4(2,1); // 4 Points to form a square

        Point a(0.5,0.5);
        Square rec(r,p1,p2,p4,p3), rec_copy(r,p1,p2,p4,p3), rec_copy2(r,p1,p2,p4,p3);  // cent is Point for Centre and 1 is radius of circle

        r = &rec;
        r1 = &rec_copy;
        r2 = &rec_copy2;

        cout << "\n1. Checking where Point (" << a.get_x() << "," << a.get_y() <<") lies with respect to Rectangle with vertices (" << p1.get_x() << "," << p1.get_y() <<") , (" << p2.get_x() << "," << p2.get_y() <<") , (" << p3.get_x() << "," << p3.get_y() <<") , (" << p4.get_x() << "," << p4.get_y() <<")"<< endl;

        if (r->contains_point(a)) cout<<"\tPoint is inside the region"<< endl;
        else cout<<"\tPoint is outside the region" << endl;


        Point b(2,1.1);


        cout << "\n2. Checking where Point (" << b.get_x() << "," << b.get_y() <<") lies with respect to Rectangle with vertices (" << p1.get_x() << "," << p1.get_y() <<") , (" << p2.get_x() << "," << p2.get_y() <<") , (" << p3.get_x() << "," << p3.get_y() <<") , (" << p4.get_x() << "," << p4.get_y() <<")"<< endl;

        if (r->contains_point(b)) cout<<"\tPoint is inside the region"<< endl;
        else cout<<"\tPoint is outside the region" << endl;

        double x = 3, y = 3;

        cout << "\n3. Translating region's x coordinate by " << x << " and y coordinate by " << y << " unit" << endl;

        r1->translate(x,y);
        // t1.translate(x,y);

        Point a1(1,0);
        cout << "\n4. Checking where Point (" << a1.get_x() << "," << a1.get_y() <<") lies with respect to Rectangle with vertices (" << p1.get_x() << "," << p1.get_y() <<") , (" << p2.get_x() << "," << p2.get_y() <<") , (" << p3.get_x() << "," << p3.get_y() <<") , (" << p4.get_x() << "," << p4.get_y() << ") and its translated version "<< endl;


        if( r->contains_point(a1) && !r1->contains_point(a1) ) cout<<"\tPoint is inside inital region but outside translated region" << endl;
        else cout << "\tCan't say" << endl;

        Point b1(4,4);

        cout << "\n5. Checking where Point (" << b1.get_x() << "," << b1.get_y() <<") lies with respect to Rectangle with vertices (" << p1.get_x() << "," << p1.get_y() <<") , (" << p2.get_x() << "," << p2.get_y() <<") , (" << p3.get_x() << "," << p3.get_y() <<") , (" << p4.get_x() << "," << p4.get_y() << ") and its translated version "<< endl;


        if(!r->contains_point(b1) && r1->contains_point(b1)) cout<<"\tPoint is outside inital region but inside translated region" << endl;
        else cout << "\tCan't say" << endl;

        cout << "\n6. Rotating initial Rectangle " << endl;
        r2->rotate(M_PI/2);

        Point a2(0.5,0.5), b2(-0.5,0.5);

        cout << "\n7. Checking where Point (" << a2.get_x() << "," << a2.get_y() <<") lies with respect to Rectangle with vertices (" << p1.get_x() << "," << p1.get_y() <<") , (" << p2.get_x() << "," << p2.get_y() <<") , (" << p3.get_x() << "," << p3.get_y() <<") , (" << p4.get_x() << "," << p4.get_y() << ") and its rotated version "<< endl;

        if(r->contains_point(a2) && !r2->contains_point(a2)) cout<<"\tPoint is inside inital region but outside rotated region" << endl;
        else cout << "\tCan't say" << endl;


        cout << "\n8. Checking where Point (" << b2.get_x() << "," << b2.get_y() <<") lies with respect to Rectangle with vertices (" << p1.get_x() << "," << p1.get_y() <<") , (" << p2.get_x() << "," << p2.get_y() <<") , (" << p3.get_x() << "," << p3.get_y() <<") , (" << p4.get_x() << "," << p4.get_y() << ") and its rotated version "<< endl;

        if(!r->contains_point(b2) && r2->contains_point(b2)) cout<<"\tPoint is inside rotated region but outside inital region" << endl;
        else cout << "\tCan't say" << endl;
    }

    {
        cout << "\nComplement of Circle : " << endl;

        Region *r, *r1, *r2;

        Point a(0,0), cent(1,1);

        float rad = 1;
        
        Circle c(r,cent,rad), c_copy(r1,cent,rad), c_copy2(r2,cent, rad);  // cent is Point for Centre and 1 is radius of circle

        r = &c;
        r1 = &c_copy;
        r2 = &c_copy2;

        Complement comp(r), comp1(r1), comp2(r2);

        cout << "\n1. Checking where Point (" << a.get_x() << "," << a.get_y() <<") lies with respect to circle with centre (" << cent.get_x() << "," << cent.get_y() <<") having radius "<< rad << endl;

        if (comp.contains_point(a)) cout<<"\tPoint is inside the Complement"<< endl;
        else cout<<"\tPoint is outside the Complement" << endl;


        Point b(1,1);


        cout << "\n2. Checking where Point (" << b.get_x() << "," << b.get_y() <<") lies with respect to circle with centre (" << cent.get_x() << "," << cent.get_y() <<") having radius "<< rad << endl;
        if (comp.contains_point(b)) cout<<"\tPoint is inside the Complement"<< endl;
        else cout<<"\tPoint is outside the Complement" << endl;

        float x = 3, y = 3;


        cout << "\n3. Translating region's x coordinate by " << x << " and y coordinate by " << y << " unit" << endl;
        comp1.translate(x,y);


        Point a1(4,4);
        cout << "\n4. Checking where Point (" << a1.get_x() << "," << a1.get_y() <<") lies with respect to circle with centre (" << cent.get_x() << "," << cent.get_y() <<") having radius "<< rad << " and also its translated version " << endl;


        if(comp.contains_point(a1) && !comp1.contains_point(a1)) cout<<"\tPoint is inside inital Complement but outside translated Complement" << endl;
        else cout << "\tCan't say" << endl;

        Point b1(1,1);

        cout << "\n5. Checking where Point (" << b1.get_x() << "," << b1.get_y() <<") lies with respect to circle with centre (" << cent.get_x() << "," << cent.get_y() <<") having radius "<< rad << " and also its translated version " << endl;


        if(!comp.contains_point(b1) && comp1.contains_point(b1)) cout<<"\tPoint is outside inital Complement but inside translated Complement" << endl;
        else cout << "\tCan't say" << endl;

        cout << "\n6. Rotating initial circle " << endl;
        comp2.rotate(M_PI);

        Point a2(-1,-1), b2(1,1);

        cout << "\n7. Checking where Point (" << a2.get_x() << "," << a2.get_y() <<") lies with respect to circle with centre (" << cent.get_x() << "," << cent.get_y() <<") having radius "<< rad << " and also its rotated version " << endl;

        if(comp.contains_point(a2) && !comp2.contains_point(a2)) cout<<"\tPoint is inside inital Complement but outside Complement region" << endl;
        else cout << "\tCan't say" << endl;


        cout << "\n8. Checking where Point (" << b2.get_x() << "," << b2.get_y() <<") lies with respect to circle with centre (" << cent.get_x() << "," << cent.get_y() <<") having radius "<< rad << " and also its rotated version " << endl;

        if(!comp.contains_point(b2) && comp2.contains_point(b2)) cout<<"\tPoint is inside rotated Complement but outside inital Complement" << endl;
        else cout << "\tCan't say" << endl; 

    }
}
