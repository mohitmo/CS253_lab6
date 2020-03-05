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

            if((sat1*sat2 ) > 0) return true;
            else if( abs(sat1*sat2 -0.0) < 1e-9) return true;
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

    //---------------------------------------   Circle  --------------------------------------------------
    {


        cout << "---------------------- Circle ----------------------" << endl;
        Region *r, *r1, *r2;

        Point cent(1,1);                // Centre of Circle

        float rad = 1;                  //redius of Circle
        
        Circle c(r,cent,rad), c_copy(r1,cent,rad), c_copy2(r2,cent, rad);  // Creating circle object c; c_copy and c_copy2 will be used for translation and rotation

        r = &c;                         // Assigning region pointers to its respective objects
        r1 = &c_copy;
        r2 = &c_copy2;


        // 1st Case
        Point a(1,0);  

        cout << "\n1. Checking where Point (" << a.get_x() << "," << a.get_y() <<") lies with respect to circle with centre (" << cent.get_x() << "," << cent.get_y() <<") having radius "<< rad << endl;

        if (r->contains_point(a)) cout<<"\tPoint is inside the Circle"<< endl;
        else cout<<"\tPoint is outside the Circle" << endl;

        
        // 2nd Case
        Point b(2,3);

        cout << "\n2. Checking where Point (" << b.get_x() << "," << b.get_y() <<") lies with respect to circle with centre (" << cent.get_x() << "," << cent.get_y() <<") having radius "<< rad << endl;
        if (r->contains_point(b)) cout<<"\tPoint is inside the Circle"<< endl;
        else cout<<"\tPoint is outside the Circle" << endl;


        // 3rd Case
        float x = 3, y = 3;

        cout << "\n3. Translating Circle's x coordinate by " << x << " and y coordinate by " << y << " unit" << endl;
        r1->translate(x,y);

        
        // 4th Case
        Point a1(1,0);
        cout << "\n4. Checking where Point (" << a1.get_x() << "," << a1.get_y() <<") lies with respect to circle with centre (" << cent.get_x() << "," << cent.get_y() <<") having radius "<< rad << " and also its translated version " << endl;

        if(r->contains_point(a1) && !r1->contains_point(a1)) cout<<"\tPoint is inside inital Circle but outside translated Circle" << endl;
        else cout << "\tCan't say" << endl;

        
        // 5th Case
        Point b1(4,3);

        cout << "\n5. Checking where Point (" << b1.get_x() << "," << b1.get_y() <<") lies with respect to circle with centre (" << cent.get_x() << "," << cent.get_y() <<") having radius "<< rad << " and also its translated version " << endl;

        if(!r->contains_point(b1) && r1->contains_point(b1)) cout<<"\tPoint is outside inital Circle but inside translated Circle" << endl;
        else cout << "\tCan't say" << endl;

        
        // 6th Case
        double angle = M_PI/4;
        cout << "\n6. Rotating initial circle " << "by " << angle << " radians" << endl;
        r2->rotate(angle);

        

        // 7th and 8th Case
        Point a2(1,0), b2(-0.5,1);

        cout << "\n7. Checking where Point (" << a2.get_x() << "," << a2.get_y() <<") lies with respect to circle with centre (" << cent.get_x() << "," << cent.get_y() <<") having radius "<< rad << " and also its rotated version " << endl;

        if(r->contains_point(a2) && !r2->contains_point(a2)) cout<<"\tPoint is inside inital Circle but outside rotated Circle" << endl;
        else cout << "\tCan't say" << endl;

        cout << "\n8. Checking where Point (" << b2.get_x() << "," << b2.get_y() <<") lies with respect to circle with centre (" << cent.get_x() << "," << cent.get_y() <<") having radius "<< rad << " and also its rotated version " << endl;

        if(!r->contains_point(b2) && r2->contains_point(b2)) cout<<"\tPoint is outside inital Circle but inside rotated Circle" << endl;
        else cout << "\tCan't say" << endl;
    }

    //---------------------------------------   Triangle  --------------------------------------------------
    {
        
        cout << "\n\n---------------------- Triangle ----------------------" << endl;
        

        Region *r, *r1, *r2;
        Point p1(0,0), p2(1,0), p3(0,1);                                   // 3 Points to form a triangle
        
        Triangle t(r,p1,p2,p3), t_copy(r1,p1,p2,p3), t_copy2(r2,p1,p2,p3); // Creating triangle object t; t_copy and t_copy2 are for translation and rotation
        

        r = &t;                                                            // Assigning region pointer to respective triangle objects
        r1 = &t_copy;
        r2 = &t_copy2;


        // 1st Case
        Point a(0,0.2);

        cout << "\n1. Checking where Point (" << a.get_x() << "," << a.get_y() <<") lies with respect to triangle with vertices (" << p1.get_x() << "," << p1.get_y() <<") , (" << p2.get_x() << "," << p2.get_y() <<") , (" << p3.get_x() << "," << p3.get_y() <<") " << endl;

        if (r->contains_point(a)) cout<<"\tPoint is inside the Triangle"<< endl;
        else cout<<"\tPoint is outside the Triangle" << endl;

        
        // 2nd Case
        Point b(2,3);

        cout << "\n2. Checking where Point (" << b.get_x() << "," << b.get_y() <<") lies with respect to triangle with vertices (" << p1.get_x() << "," << p1.get_y() <<") , (" << p2.get_x() << "," << p2.get_y() <<") , (" << p3.get_x() << "," << p3.get_y() <<") " << endl;
        if (r->contains_point(b)) cout<<"\tPoint is inside the Triangle"<< endl;
        else cout<<"\tPoint is outside the Triangle" << endl;

        
        // 3rd Case
        double x = 3, y = 3;

        cout << "\n3. Translating Triangle's x coordinate by " << x << " and y coordinate by " << y << " unit" << endl;

        r1->translate(x,y);

        
        // 4th Case
        Point a1(1,0);

        cout << "\n4. Checking where Point (" << a1.get_x() << "," << a1.get_y() <<") lies with respect to triangle with vertices (" << p1.get_x() << "," << p1.get_y() <<") , (" << p2.get_x() << "," << p2.get_y() <<") , (" << p3.get_x() << "," << p3.get_y() <<") and its translated version" << endl;

        if( r->contains_point(a1) && !r1->contains_point(a1) ) cout<<"\tPoint is inside inital Triangle but outside translated Triangle" << endl;
        else cout << "\tCan't say" << endl;

        
        // 5th Case
        Point b1(3,3);

        cout << "\n5. Checking where Point (" << b1.get_x() << "," << b1.get_y() <<") lies with respect to triangle with vertices (" << p1.get_x() << "," << p1.get_y() <<") , (" << p2.get_x() << "," << p2.get_y() <<") , (" << p3.get_x() << "," << p3.get_y() <<") and its translated version" << endl;

        if(!r->contains_point(b1) && r1->contains_point(b1)) cout<<"\tPoint is outside inital Triangle but inside translated Triangle" << endl;
        else cout << "\tCan't say" << endl;

        
        // 6th Case
        double angle = M_PI/2;
        cout << "\n6. Rotating initial triangle " << "by " << angle << " radians" << endl;
        r2->rotate(angle);


        // 7th and 8th Case
        Point a2(1,0), b2(-0.2,0.1);

        cout << "\n7. Checking where Point (" << a2.get_x() << "," << a2.get_y() <<") lies with respect to triangle with vertices (" << p1.get_x() << "," << p1.get_y() <<") , (" << p2.get_x() << "," << p2.get_y() <<") , (" << p3.get_x() << "," << p3.get_y() <<") and its rotated version" << endl;

        if(r->contains_point(a2) && !r2->contains_point(a2)) cout<<"\tPoint is inside inital Triangle but outside rotated Triangle" << endl;
        else cout << "\tCan't say" << endl;

        cout << "\n8. Checking where Point (" << b2.get_x() << "," << b2.get_y() <<") lies with respect to triangle with vertices (" << p1.get_x() << "," << p1.get_y() <<") , (" << p2.get_x() << "," << p2.get_y() <<") , (" << p3.get_x() << "," << p3.get_y() <<") and its rotated version" << endl;

        if(!r->contains_point(b2) && r2->contains_point(b2)) cout<<"\tPoint is outside inital Triangle but inside rotated Triangle" << endl;
        else cout << "\tCan't say" << endl;


    }

    //---------------------------------------   Square  --------------------------------------------------

    {


        cout << "\n\n---------------------- Square ----------------------" << endl;
        Region *r, *r1, *r2;
        Point p1(0,0), p2(1,0), p3(0,1), p4(1,1);                                // 4 Points to form a square

        
        Square s(r,p1,p2,p4,p3), s_copy(r,p1,p2,p4,p3), s_copy2(r,p1,p2,p4,p3);  // Creating square object s; s_copy and s_copy2 will be used for translation and rotation

        r = &s;                                                                  // Assigning region pointers to particular
        r1 = &s_copy;
        r2 = &s_copy2;


        // 1st Case
        Point a(0,0.2);

        cout << "\n1. Checking where Point (" << a.get_x() << "," << a.get_y() <<") lies with respect to square with vertices (" << p1.get_x() << "," << p1.get_y() <<") , (" << p2.get_x() << "," << p2.get_y() <<") , (" << p3.get_x() << "," << p3.get_y() <<") , (" << p4.get_x() << "," << p4.get_y() <<")"<< endl;

        if (r->contains_point(a)) cout<<"\tPoint is inside the Square"<< endl;
        else cout<<"\tPoint is outside the Square" << endl;


        // 2nd Case
        Point b(2,3);

        cout << "\n2. Checking where Point (" << b.get_x() << "," << b.get_y() <<") lies with respect to square with vertices (" << p1.get_x() << "," << p1.get_y() <<") , (" << p2.get_x() << "," << p2.get_y() <<") , (" << p3.get_x() << "," << p3.get_y() <<") , (" << p4.get_x() << "," << p4.get_y() <<")"<< endl;

        if (r->contains_point(b)) cout<<"\tPoint is inside the Square"<< endl;
        else cout<<"\tPoint is outside the Square" << endl;

        
        // 3rd Case
        double x = 3, y = 3;

        cout << "\n3. Translating Square's x coordinate by " << x << " and y coordinate by " << y << " unit" << endl;
        r1->translate(x,y);
        

        // 4th Case
        Point a1(1,0);
        cout << "\n4. Checking where Point (" << a1.get_x() << "," << a1.get_y() <<") lies with respect to square with vertices (" << p1.get_x() << "," << p1.get_y() <<") , (" << p2.get_x() << "," << p2.get_y() <<") , (" << p3.get_x() << "," << p3.get_y() <<") , (" << p4.get_x() << "," << p4.get_y() << ") and its translated version "<< endl;

        if( r->contains_point(a1) && !r1->contains_point(a1) ) cout<<"\tPoint is inside inital Square but outside translated Square" << endl;
        else cout << "\tCan't say" << endl;

        
        // 5th Case
        Point b1(3,3);

        cout << "\n5. Checking where Point (" << b1.get_x() << "," << b1.get_y() <<") lies with respect to square with vertices (" << p1.get_x() << "," << p1.get_y() <<") , (" << p2.get_x() << "," << p2.get_y() <<") , (" << p3.get_x() << "," << p3.get_y() <<") , (" << p4.get_x() << "," << p4.get_y() << ") and its translated version "<< endl;

        if(!r->contains_point(b1) && r1->contains_point(b1)) cout<<"\tPoint is outside inital Square but inside translated Square" << endl;
        else cout << "\tCan't say" << endl;

        
        // 6th Case
        double angle = M_PI/2;
        cout << "\n6. Rotating initial square " << "by " << angle << " radians" << endl;
        r2->rotate(angle);

        
        // 7th and 8th Case
        Point a2(0.5,0.5), b2(-0.5,0.5);

        cout << "\n7. Checking where Point (" << a2.get_x() << "," << a2.get_y() <<") lies with respect to square with vertices (" << p1.get_x() << "," << p1.get_y() <<") , (" << p2.get_x() << "," << p2.get_y() <<") , (" << p3.get_x() << "," << p3.get_y() <<") , (" << p4.get_x() << "," << p4.get_y() << ") and its rotated version "<< endl;

        if(r->contains_point(a2) && !r2->contains_point(a2)) cout<<"\tPoint is inside inital Square but outside rotated Square" << endl;
        else cout << "\tCan't say" << endl;

        cout << "\n8. Checking where Point (" << b2.get_x() << "," << b2.get_y() <<") lies with respect to square with vertices (" << p1.get_x() << "," << p1.get_y() <<") , (" << p2.get_x() << "," << p2.get_y() <<") , (" << p3.get_x() << "," << p3.get_y() <<") , (" << p4.get_x() << "," << p4.get_y() << ") and its rotated version "<< endl;

        if(!r->contains_point(b2) && r2->contains_point(b2)) cout<<"\tPoint is outside inital Square but inside rotated Square" << endl;
        else cout << "\tCan't say" << endl;



    }


    //---------------------------------------   Rectangle  --------------------------------------------------
    {


        cout << "\n\n---------------------- Rectangle ----------------------" << endl;
        Region *r, *r1, *r2;
        Point p1(0,0), p2(2,0), p3(0,1), p4(2,1);                   // 4 Points to form a square

        
        Square rec(r,p1,p2,p4,p3), rec_copy(r,p1,p2,p4,p3), rec_copy2(r,p1,p2,p4,p3);  // Creating rectangle object rec; and rec_copy and rec_copy2 will be used for translation and rotatation

        r = &rec;                     // Assigning region pointers to respective objects
        r1 = &rec_copy;
        r2 = &rec_copy2;


        // 1st Case
        Point a(0.5,0.5);

        cout << "\n1. Checking where Point (" << a.get_x() << "," << a.get_y() <<") lies with respect to Rectangle with vertices (" << p1.get_x() << "," << p1.get_y() <<") , (" << p2.get_x() << "," << p2.get_y() <<") , (" << p3.get_x() << "," << p3.get_y() <<") , (" << p4.get_x() << "," << p4.get_y() <<")"<< endl;

        if (r->contains_point(a)) cout<<"\tPoint is inside the Rectangle"<< endl;
        else cout<<"\tPoint is outside the Rectangle" << endl;


        
        // 2nd Case
        Point b(2,1.1);

        cout << "\n2. Checking where Point (" << b.get_x() << "," << b.get_y() <<") lies with respect to Rectangle with vertices (" << p1.get_x() << "," << p1.get_y() <<") , (" << p2.get_x() << "," << p2.get_y() <<") , (" << p3.get_x() << "," << p3.get_y() <<") , (" << p4.get_x() << "," << p4.get_y() <<")"<< endl;

        if (r->contains_point(b)) cout<<"\tPoint is inside the Rectangle"<< endl;
        else cout<<"\tPoint is outside the Rectangle" << endl;

        
        // 3rd Case
        double x = 3, y = 3;

        cout << "\n3. Translating Rectangle's x coordinate by " << x << " and y coordinate by " << y << " unit" << endl;
        r1->translate(x,y);
        
        
        // 4th Case
        Point a1(1,0);
        
        cout << "\n4. Checking where Point (" << a1.get_x() << "," << a1.get_y() <<") lies with respect to Rectangle with vertices (" << p1.get_x() << "," << p1.get_y() <<") , (" << p2.get_x() << "," << p2.get_y() <<") , (" << p3.get_x() << "," << p3.get_y() <<") , (" << p4.get_x() << "," << p4.get_y() << ") and its translated version "<< endl;

        if( r->contains_point(a1) && !r1->contains_point(a1) ) cout<<"\tPoint is inside inital Rectangle but outside translated Rectangle" << endl;
        else cout << "\tCan't say" << endl;

        
        // 5th Case
        Point b1(4,4);

        cout << "\n5. Checking where Point (" << b1.get_x() << "," << b1.get_y() <<") lies with respect to Rectangle with vertices (" << p1.get_x() << "," << p1.get_y() <<") , (" << p2.get_x() << "," << p2.get_y() <<") , (" << p3.get_x() << "," << p3.get_y() <<") , (" << p4.get_x() << "," << p4.get_y() << ") and its translated version "<< endl;

        if(!r->contains_point(b1) && r1->contains_point(b1)) cout<<"\tPoint is outside inital Rectangle but inside translated Rectangle" << endl;
        else cout << "\tCan't say" << endl;

        
        // 6th Case
        double angle = M_PI/2;
        cout << "\n6. Rotating initial Rectangle " << "by " << angle << " radians" << endl;
        r2->rotate(angle);


        // 7th and 8th Case
        Point a2(0.5,0.5), b2(-0.5,0.5);

        cout << "\n7. Checking where Point (" << a2.get_x() << "," << a2.get_y() <<") lies with respect to Rectangle with vertices (" << p1.get_x() << "," << p1.get_y() <<") , (" << p2.get_x() << "," << p2.get_y() <<") , (" << p3.get_x() << "," << p3.get_y() <<") , (" << p4.get_x() << "," << p4.get_y() << ") and its rotated version "<< endl;

        if(r->contains_point(a2) && !r2->contains_point(a2)) cout<<"\tPoint is inside inital Rectangle but outside rotated Rectangle" << endl;
        else cout << "\tCan't say" << endl;


        cout << "\n8. Checking where Point (" << b2.get_x() << "," << b2.get_y() <<") lies with respect to Rectangle with vertices (" << p1.get_x() << "," << p1.get_y() <<") , (" << p2.get_x() << "," << p2.get_y() <<") , (" << p3.get_x() << "," << p3.get_y() <<") , (" << p4.get_x() << "," << p4.get_y() << ") and its rotated version "<< endl;

        if(!r->contains_point(b2) && r2->contains_point(b2)) cout<<"\tPoint is outside inital Rectangle but inside rotated Rectangle" << endl;
        else cout << "\tCan't say" << endl;
   

    }

    //---------------------------------------   Complement of Circle  --------------------------------------------------
    {
        cout << "\n\n---------------------- Complement of Circle ----------------------" << endl;

        Region *r, *r1, *r2;

        Point cent(1,1);             // Centre of circle

        float rad = 1;               // Radius of circle
        
        Circle c(r,cent,rad), c_copy(r1,cent,rad), c_copy2(r2,cent, rad);  // cent is Point for Centre and 1 is radius of circle

        r = &c;
        r1 = &c_copy;
        r2 = &c_copy2;

        Complement comp(r), comp1(r1), comp2(r2);                          // Creating complement objects. comp1 and comp2 will be used for translation and rotation


        // 1st Case
        Point a(0,0);

        cout << "\n1. Checking where Point (" << a.get_x() << "," << a.get_y() <<") lies with respect to circle with centre (" << cent.get_x() << "," << cent.get_y() <<") having radius "<< rad << endl;

        if (comp.contains_point(a)) cout<<"\tPoint is inside the Complement"<< endl;
        else cout<<"\tPoint is outside the Complement" << endl;


        // 2nd Case
        Point b(1,1);

        cout << "\n2. Checking where Point (" << b.get_x() << "," << b.get_y() <<") lies with respect to circle with centre (" << cent.get_x() << "," << cent.get_y() <<") having radius "<< rad << endl;
        if (comp.contains_point(b)) cout<<"\tPoint is inside the Complement"<< endl;
        else cout<<"\tPoint is outside the Complement" << endl;

        
        // 3rd Case
        float x = 3, y = 3;

        cout << "\n3. Translating Complement's x coordinate by " << x << " and y coordinate by " << y << " unit" << endl;
        comp1.translate(x,y);


        // 4th Case
        Point a1(4,4);
        
        cout << "\n4. Checking where Point (" << a1.get_x() << "," << a1.get_y() <<") lies with respect to circle with centre (" << cent.get_x() << "," << cent.get_y() <<") having radius "<< rad << " and also its translated version " << endl;

        if(comp.contains_point(a1) && !comp1.contains_point(a1)) cout<<"\tPoint is inside inital Complement but outside translated Complement" << endl;
        else cout << "\tCan't say" << endl;

        
        // 5th Case
        Point b1(1,1);

        cout << "\n5. Checking where Point (" << b1.get_x() << "," << b1.get_y() <<") lies with respect to circle with centre (" << cent.get_x() << "," << cent.get_y() <<") having radius "<< rad << " and also its translated version " << endl;

        if(!comp.contains_point(b1) && comp1.contains_point(b1)) cout<<"\tPoint is outside inital Complement but inside translated Complement" << endl;
        else cout << "\tCan't say" << endl;

        
        // 6th Case
        double angle = M_PI;
        cout << "\n6. Rotating initial circle " << "by " << angle << " radians" << endl;
        comp2.rotate(angle);

        
        // 7th and 8th Case
        Point a2(-1,-1), b2(1,1);

        cout << "\n7. Checking where Point (" << a2.get_x() << "," << a2.get_y() <<") lies with respect to circle with centre (" << cent.get_x() << "," << cent.get_y() <<") having radius "<< rad << " and also its rotated version " << endl;

        if(comp.contains_point(a2) && !comp2.contains_point(a2)) cout<<"\tPoint is inside inital Complement but outside Complement region" << endl;
        else cout << "\tCan't say" << endl;


        cout << "\n8. Checking where Point (" << b2.get_x() << "," << b2.get_y() <<") lies with respect to circle with centre (" << cent.get_x() << "," << cent.get_y() <<") having radius "<< rad << " and also its rotated version " << endl;

        if(!comp.contains_point(b2) && comp2.contains_point(b2)) cout<<"\tPoint is outside inital Complement but inside rotated Complement" << endl;
        else cout << "\tCan't say" << endl; 

    }

    //---------------------------------------   Annular Region  --------------------------------------------------
    {
        cout << "\n\n---------------------- Annular Region ----------------------" << endl;

        Region *r, *r1, *r2;
        Region *r_out, *r1_out, *r2_out;

        Point cent(2,2);                       // Centre of the two concentric circles
        double rad1 = 1.0, rad2 = 2.0;         // Inner and Outer redii of Annular region

        Circle c(r, cent, rad1), c_copy(r, cent, rad1), c_copy2(r, cent, rad1);  // Objects for Inner circle in annular region
        Circle c1(r_out, cent, rad2), c1_copy(r1_out,cent,rad2), c1_copy2(r2_out, cent, rad2);  // Objects for Outer circle in annular region

        r = &c;                         // Assigning each region pointer to its object
        r1 = &c_copy;
        r2 = &c_copy2;
        r_out = &c1;
        r1_out = &c1_copy;
        r2_out = &c1_copy2;


        Complement comp(r), comp1(r1), comp2(r2);                                     // creating complement of inner circle.

        Intersection i(r_out, &comp), i1(r1_out, &comp1), i2(r2_out, &comp2);         // Creating intersection object. i1 and i2 will be used for transalting and rotating.

        
        // 1st case
        Point a(0.5,2);

        cout << "\n1. Checking where Point (" << a.get_x() << "," << a.get_y() <<") lies with respect to annular region with centre (" << cent.get_x() << "," << cent.get_y() <<") having inner radius "<< rad1 << "and outer radius " << rad2 << endl;

        if (i.contains_point(a)) cout<<"\tPoint is inside the annular region"<< endl;
        else cout<<"\tPoint is outside the outside annular region" << endl;


        
        // 2nd Case
        Point b(2,2);

        cout << "\n2. Checking where Point (" << b.get_x() << "," << b.get_y() <<") lies with respect to annular region with centre (" << cent.get_x() << "," << cent.get_y() <<") having inner radius "<< rad1 << "and outer radius " << rad2 << endl;
        
        if (i.contains_point(b)) cout<<"\tPoint is inside the annular region"<< endl;
        else cout<<"\tPoint is outside the outside annular region" << endl;

        
        // 3rd Case
        float x = 2, y = 0;

        cout << "\n3. Translating Annular region's x coordinate by " << x << " and y coordinate by " << y << " unit" << endl;
        i1.translate(x,y);


        // 4th Case
        Point a1(3.5,2);

        cout << "\n4. Checking where Point (" << a1.get_x() << "," << a1.get_y() <<") lies with respect to annular region with centre (" << cent.get_x() << "," << cent.get_y() <<") having inner radius "<< rad1 << "and outer radius " << rad2 <<  " and its translated version" << endl;

        if(i.contains_point(a1) && !i1.contains_point(a1)) cout<<"\tPoint is inside inital annulus but outside translated annulus" << endl;
        else cout << "\tCan't say" << endl;

        
        // 5th Case
        Point b1(2.5 , 2);

        cout << "\n5. Checking where Point (" << b1.get_x() << "," << b1.get_y() <<") lies with respect to annular region with centre (" << cent.get_x() << "," << cent.get_y() <<") having inner radius "<< rad1 << "and outer radius " << rad2 <<  " and its translated version" << endl;

        if(!i.contains_point(b1) && i1.contains_point(b1)) cout<<"\tPoint is outside inital annulus but inside translated annulus" << endl;
        else cout << "\tCan't say" << endl;


        // 6th Case
        double angle = M_PI;
        cout << "\n6. Rotating initial annulus " << "by " << angle << " radians" << endl;
        i2.rotate(angle);

        
        // 7th and 8th Case
        Point a2( 0.5 , 2), b2( -0.5, -2);

        cout << "\n7. Checking where Point (" << a2.get_x() << "," << a2.get_y() <<") lies with respect to annular region with centre (" << cent.get_x() << "," << cent.get_y() <<") having inner radius "<< rad1 << "and outer radius " << rad2 <<  " and its rotated version" << endl;

        if(i.contains_point(a2) && !i2.contains_point(a2)) cout<<"\tPoint is inside inital annulus but outside annulus region" << endl;
        else cout << "\tCan't say" << endl;


        cout << "\n8. Checking where Point (" << b2.get_x() << "," << b2.get_y() <<") lies with respect to annular region with centre (" << cent.get_x() << "," << cent.get_y() <<") having inner radius "<< rad1 << "and outer radius " << rad2 <<  " and its rotated version" << endl;

        if(!i.contains_point(b2) && i2.contains_point(b2)) cout<<"\tPoint is outside inital annulus but inside rotated annulus" << endl;
        else cout << "\tCan't say" << endl;

    }

    //---------------------------------------   L-shaped Region  --------------------------------------------------
    {
        cout << "\n\n---------------------- L-shaped Region ----------------------" <<endl;

        Region *r, *r1, *r2, *r3, *r4, *r5;  // Regions required for union

        Point A(0,0), B(4,0), C(4,2) , D(2,2), E(2,6), F(0,6);  // A, B, C, D, E, F are points must for L-shaped region

        Point G(A.get_x(), D.get_y()), H(E.get_x(), A.get_y()); // G, H are extra points based on above points to construct 2 rectangles

        Rectangle rec1(r, A,B,C,G), rec1_copy(r1, A,B,C,G), rec1_copy2(r2, A,B,C,G);   // constructing rectangle 1 and its two copies
        Rectangle rec2(r3, A,H,E,F), rec2_copy(r1, A,H,E,F), rec2_copy2(r2, A,H,E,F);  // constructing rectangle 2 and its two copies

        // Assigning each region to its object
        r = &rec1;                
        r1 = &rec1_copy;
        r2 = &rec1_copy2;
        r3 = &rec2;
        r4 = &rec2_copy;
        r5 = &rec2_copy2;

        Union u(r,r3) , u1(r1,r4) , u2(r2, r5);   // Constucting union as required. u1 and u2 will be used to translate and rotate respectively.
 
        // 1st Case
        Point a(1,2);

        cout << "\n1. Checking where Point (" << a.get_x() << "," << a.get_y() <<") lies with respect to L-shaped region with vertices (" << A.get_x() << "," << A.get_y() <<") , " << "(" << B.get_x() << "," << B.get_y() <<") , " << "(" << C.get_x() << "," << C.get_y() <<") , " << "(" << D.get_x() << "," << D.get_y() <<") , " << "(" << E.get_x() << "," << E.get_y() <<") , " << "(" << F.get_x() << "," << F.get_y() <<")" << endl; 

        if (u.contains_point(a)) cout<<"\tPoint is inside the L-shaped region"<< endl;
        else cout<<"\tPoint is outside the outside L-shaped region" << endl;


        // 2nd Case
        Point b(3,3);

        cout << "\n2. Checking where Point (" << b.get_x() << "," << b.get_y() <<") lies with respect to L-shaped region with vertices (" << A.get_x() << "," << A.get_y() <<") , " << "(" << B.get_x() << "," << B.get_y() <<") , " << "(" << C.get_x() << "," << C.get_y() <<") , " << "(" << D.get_x() << "," << D.get_y() <<") , " << "(" << E.get_x() << "," << E.get_y() <<") , " << "(" << F.get_x() << "," << F.get_y() <<")" << endl; 
        
        if (u.contains_point(b)) cout<<"\tPoint is inside the L-shaped region"<< endl;
        else cout<<"\tPoint is outside the outside L-shaped region" << endl;

        
        // 3rd Case
        float x = 2, y = 2;

        cout << "\n3. Translating L-shaped region's x coordinate by " << x << " and y coordinate by " << y << " unit" << endl;
        u1.translate(x,y);


        // 4th Case
        Point a1(1,1);
        cout << "\n4. Checking where Point (" << a1.get_x() << "," << a1.get_y() <<") lies with respect to L-shaped region with vertices (" << A.get_x() << "," << A.get_y() <<") , " << "(" << B.get_x() << "," << B.get_y() <<") , " << "(" << C.get_x() << "," << C.get_y() <<") , " << "(" << D.get_x() << "," << D.get_y() <<") , " << "(" << E.get_x() << "," << E.get_y() <<") , " << "(" << F.get_x() << "," << F.get_y() <<") and its translated version" << endl; 

        if(u.contains_point(a1) && !u1.contains_point(a1)) cout<<"\tPoint is inside inital L-shaped region but outside translated L-shaped region" << endl;
        else cout << "\tCan't say" << endl;


        // 5th Case
        Point b1(3 , 3);
        cout << "\n5. Checking where Point (" << b1.get_x() << "," << b1.get_y() <<") lies with respect to L-shaped region with vertices (" << A.get_x() << "," << A.get_y() <<") , " << "(" << B.get_x() << "," << B.get_y() <<") , " << "(" << C.get_x() << "," << C.get_y() <<") , " << "(" << D.get_x() << "," << D.get_y() <<") , " << "(" << E.get_x() << "," << E.get_y() <<") , " << "(" << F.get_x() << "," << F.get_y() <<") and its translated version" << endl; 

        if(!u.contains_point(b1) && u1.contains_point(b1)) cout<<"\tPoint is outside inital L-shaped region but inside translated L-shaped region" << endl;
        else cout << "\tCan't say" << endl;

        
        // 6th Case
        double angle = M_PI;
        cout << "\n6. Rotating initial L-shaped region " << "by " << angle << " radians" << endl;
        u2.rotate(angle);

        

        // 7th and 8th Case
        Point a2( 1 , 1), b2( -1, -1);

        cout << "\n7. Checking where Point (" << a2.get_x() << "," << a2.get_y() <<") lies with respect to L-shaped region with vertices (" << A.get_x() << "," << A.get_y() <<") , " << "(" << B.get_x() << "," << B.get_y() <<") , " << "(" << C.get_x() << "," << C.get_y() <<") , " << "(" << D.get_x() << "," << D.get_y() <<") , " << "(" << E.get_x() << "," << E.get_y() <<") , " << "(" << F.get_x() << "," << F.get_y() <<") and its rotated version" << endl; 

        if(u.contains_point(a2) && !u2.contains_point(a2)) cout<<"\tPoint is inside inital L-shaped region but outside rotated L-shaped region" << endl;
        else cout << "\tCan't say" << endl;


        cout << "\n8. Checking where Point (" << b2.get_x() << "," << b2.get_y() <<") lies with respect to L-shaped region with vertices (" << A.get_x() << "," << A.get_y() <<") , " << "(" << B.get_x() << "," << B.get_y() <<") , " << "(" << C.get_x() << "," << C.get_y() <<") , " << "(" << D.get_x() << "," << D.get_y() <<") , " << "(" << E.get_x() << "," << E.get_y() <<") , " << "(" << F.get_x() << "," << F.get_y() <<") and its rotated version" << endl; 

        if(!u.contains_point(b2) && u2.contains_point(b2)) cout<<"\tPoint is outside inital L-shaped region but inside rotated L-shaped region" << endl;
        else cout << "\tCan't say" << endl;

    }
    
}
