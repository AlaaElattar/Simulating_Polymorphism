#include <iostream>
#include <cmath>
using namespace std;

//Struct to hold addresses of functions of derived class.
struct ShapeVtable;

//Base class (Interface) to be inherited.
struct Shape
{
    ShapeVtable* vtable; //Object of struct Vtable, to hold its virtual functions.
};

//Declaration of the above struct in line 6.
struct ShapeVtable
{
    //Pure Virtual functions.
    void (*GetArea) (Shape*);   //Get area of each inherited shape.
    void (*PrintInfo) (Shape*); //Output information of each inherited shape.
};

//Virtual Function to be matched with each shape derived from the class with its own implementation.
double GetArea(Shape* shape)
{
    //Call the function for specific object derived from the base class.
    shape->vtable->GetArea(shape);
}

//Virtual Function to be matched with each shape derived from the class with its own implementation.
void PrintInfo(Shape* shape)
{
    //Call the function for specific object derived from the base class.
    shape->vtable->PrintInfo(shape);
}

/*================================================================================================*/

//Derived class from Shape Interface.
struct Circle
{
    Shape parent;   //Object from Shape Interface to be able to access its functions.
    int radius;     //radius of circle
    double area;    //area of circle
};

//Double function to calculate area of circle. Also, Overriding Function implements the virtual function (GetArea) in the interface.
double CircleArea(Circle* circle)
{
    //Area of Circle = PI * radius * radius
    circle->area = M_PI* (circle->radius*circle->radius);
    return circle->area;
}

//Void Function to print radius of circle. Also, Overriding Function implements the virtual function (PrintInfo) in the interface.
void PrintCircle(Circle* circle)
{
    cout<<"The Radius of Circle is "<< circle->radius<<endl; //Print radius of Circle.
    //cout<<"The Area of Circle is "<<circle->area<<endl;
}

//Object of struct ShapeVtable to convert derived object to base object which is called up cast.
ShapeVtable circle_vtable=
        {
                (void(*) (Shape*)) CircleArea,  //Typecasting Circle object to Shape.
                (void(*) (Shape*)) PrintCircle  //Typecasting Circle object to Shape.
        };

//Constructor of derived class Circle to initialize its attributes.
void CircleInitialize(Circle* circle, int radius)
{
    circle->parent.vtable = &circle_vtable;  //assign address of circle's vtable to vtable of Shape (Parent).
    circle->radius = radius;    //Initialize radius.
}

/*================================================================================================*/

//Derived class Rectangle from Shape Interface.
struct Rectangle
{
    Shape parent;    //Object from Shape Interface to be able to access its functions.
    int height;     //height of Rectangle.
    int width;      //Width of Rectangle.
    double area;    //Area of Rectangle.
};

//Double function to calculate area of rectangle. Also, Overriding Function implements the virtual function (GetArea) in the interface.
double RectangleArea(Rectangle* rectangle )
{
    //Area of rectangle = height*width.
    rectangle->area = rectangle->height * rectangle->width;
    return rectangle->area;
}

//Void Function to print Width and Height of rectangle. Also, Overriding Function implements the virtual function (PrintInfo) in the interface.
void PrintRectangle(Rectangle* rectangle)
{
    //print rectangle's info.
    cout<<"The Height and Width of Rectangle are "<< rectangle->height
        << " , "<<rectangle->width<<endl;
    //cout<<"The Area of Rectangle is "<<rectangle->area<<endl;
}

//Object of struct ShapeVtable to convert derived object to base object which is called up cast.
ShapeVtable rectangle_vtable=
        {
                (void(*) (Shape*)) RectangleArea,   //Typecasting rectangle object to Shape.
                (void(*) (Shape*)) PrintRectangle   //Typecasting rectangle object to Shape.
        };

//Constructor of derived class Rectangle to initialize its attributes.
void RectangleInitialize(Rectangle* rectangle, int height, int width)
{
    rectangle->parent.vtable = &rectangle_vtable;   //assign address of rectangle's vtable to vtable of Shape (Parent).
    rectangle->height = height;     //Initialize height of rectangle.
    rectangle->width = width;       //Initialize width of rectangle.
}

/*================================================================================================*/

//Derived class Ellipse from Shape Interface.
struct Ellipse
{
    Shape parent;   //Object from Shape Interface to be able to access its functions.
    int r1;         //First radius of Ellipse.
    int r2;         //Second radius of Ellipse.
    double area;    //Area of Ellipse.
};

//Double function to calculate area of ellipse. Also, Overriding Function implements the virtual function (GetArea) in the interface.
double EllipseArea(Ellipse* ellipse )
{
    //Area of Ellipse = Radius1 * Radius2.
    ellipse->area = ellipse->r1 * ellipse->r2;
    return ellipse->area;
}

//Void Function to print first and second radius of ellipse. Also, Overriding Function implements the virtual function (PrintInfo) in the interface.
void PrintEllipse(Ellipse* ellipse)
{
    //Print Info of Ellipse.
    cout<<"The Radius of Ellipse is "<< ellipse->r1
        << " and "<<ellipse->r2<<endl;
    //cout<<"The Area of Ellipse is "<<ellipse->area<<endl;
}

//Object of struct ShapeVtable to convert derived object to base object which is called up cast.
ShapeVtable ellipse_vtable=
        {
                (void(*) (Shape*)) EllipseArea,     //Typecasting ellipse object to Shape.
                (void(*) (Shape*)) PrintEllipse     //Typecasting ellipse object to Shape.
        };

//Constructor of derived class Ellipse to initialize its attributes.
void EllipseInitialize(Ellipse* ellipse, int r1, int r2)
{
    ellipse->parent.vtable = &ellipse_vtable;   //assign address of ellipse's vtable to vtable of Shape (Parent).
    ellipse->r1 = r1;   //Initialize first radius.
    ellipse->r2 = r2;   //Initialize second radius.
}

/*================================================================================================*/

int main()
{
    Circle circle;
    CircleInitialize(&circle, 10); // circle with radius 10
    Rectangle rectangle;
    RectangleInitialize(&rectangle, 3, 5); // rectangle with width 3 and height 5
    Ellipse ellipse;
    EllipseInitialize(&ellipse, 10, 12); // ellipse with radius 10, 12
    Shape* shapes[3];
    shapes[0]=(Shape*)&circle ;
    shapes[1]=(Shape*)&rectangle ;
    shapes[2]=(Shape*)&ellipse ;
    double total_area=0;
    int i;
    for(i=0;i<3;i++)
    {
        double d=GetArea(shapes[i]);
        total_area+=d;
        PrintInfo(shapes[i]); // prints (cout) the radius if circle, width and height if rectangle, ... etc
    }

    cout<<total_area<<endl; // check if the value is correct
    return 0;
}
