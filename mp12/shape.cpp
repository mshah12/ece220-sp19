#include "shape.hpp"
/* This program creates different shapes and allows them to be created. Given a base class 'shape', four classes are
dertived from it: 'rectangle', 'circle', 'sphere', and 'rectangular prism'. Each of these four classes have their
respective values, such a width, height, length, and/or radius. Given these values, this program can caluculate and
return a shape's area, volume, and if that shape is added or subtracted by another shape of its class. This program
incoporates many of the same functions for each class, such as getArea() and getVolume, but each have their own
unique expression.

partners: ipatel28 */


//Base class
//Please implement Shape's member functions
//constructor, getName()
//
//Base class' constructor should be called in derived classes'
//constructor to initizlize Shape's private variable

//creates the constructor for the shape base class
Shape::Shape(string name)
{
  //assigns the inputted name to the private variable of the shape
  name_ = name;
}

//returns the name of the shape
string Shape::getName()
{
  return name_;
}


//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

//Creates the costructor for the rectangle derived class with shape as its base class
Rectangle::Rectangle(double width, double length):Shape("Rectangle")
{
  //assigns inputted variables to the private variables of the rectangle
  width_ = width;
  length_ = length;
}

//caluclates and returns the area of the rectangle
double Rectangle::getArea()const
{
  return (width_ * length_);
}

//returns the volume of the rectangle
double Rectangle::getVolume()const
{
  return 0;
}

//given two rectangles, returns a rectangle whose width and length is the sum of the two
Rectangle Rectangle::operator + (const Rectangle& rec)
{
  //returns a rectangle with the sum width and sum length
  return Rectangle(width_+ rec.getWidth(), length_ + rec.getLength());
}

//given two rectangles, returns a rectangle whose width and length is the difference of the two
Rectangle Rectangle::operator - (const Rectangle& rec)
{
  //intializes and declares variables with their respective values
  //checks for negative values, returns a 0 if difference is negative
  double negativeWidth, negativeLength = 0;
  double widthDifference = (width_ - rec.getWidth());
  double lengthDifference = (length_ - rec.getLength());

  //if width difference positive, negativeWidth equals width difference
  if(widthDifference > 0)
  {
    negativeWidth = widthDifference;
  }

  //if length difference is positive, negativeLength equals length difference
  if(lengthDifference > 0)
  {
    negativeLength = lengthDifference;
  }

  //return a rectangle whose width and length are the differences of the given values
  return Rectangle(negativeWidth, negativeLength);
}

double Rectangle::getWidth()const{return width_;}
double Rectangle::getLength()const{return length_;}



//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

//creates the constructor for the circle derived class with shape as its base class
Circle::Circle(double radius):Shape("Circle")
{
  //assigns inputted value to private variable of circle
  radius_ = radius;
}

//calculates and returns the area of the circle
double Circle::getArea()const
{
  return (radius_ * radius_ * M_PI);
}

//returns the volume of the circle
double Circle::getVolume()const
{
  return 0;
}

//given two circles, returns a circle who radius is the same of the two
Circle Circle::operator + (const Circle& cir)
{
  //returns a circle with a radius of r1 + r2
  return Circle(radius_ + cir.getRadius());
}

//given two circles, returns a circle who radius is the difference of the two
Circle Circle::operator - (const Circle& cir)
{
  //checks if the difference of radius is negative, and then returns the respective value
  double negRadius = (radius_ - cir.getRadius() > 0 ? radius_ - cir.getRadius() : 0);
	return Circle(negRadius);
}

double Circle::getRadius()const{return radius_;}

//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

//creates the constructor for the sphere derived class whose base class is shape
Sphere::Sphere(double radius):Shape("Sphere")
{
  //sets the radius of the sphere to the inputted value
  radius_ = radius;
}

//calculates and returns the area of the sphere
double Sphere::getArea()const
{
  //returns the area
  return (4.0 * M_PI * radius_ * radius_);
}

//calculates and returns the volume of the sphere
double Sphere::getVolume()const
{
  //returns the volume
  return ((4.0/3.0) * M_PI * radius_ * radius_ * radius_);
}

//returns a sphere whose radius is the sum of the two given spheres
Sphere Sphere::operator + (const Sphere& sph)
{
  //returns a sphere of r1 + r1
  return Sphere(radius_ + sph.getRadius());
}

//returns a sphere whose raidus is the difference of the two given spheres
Sphere Sphere::operator - (const Sphere& sph)
{
  //checks if the difference of the radius is negative, then returns the repsective value
  double negRadius = (((radius_ - sph.getRadius()) < 0) ? 0: radius_ - sph.getRadius());
	return Sphere(negRadius);
}

double Sphere::getRadius()const{return radius_;}

//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

//creates a constructor for the rectprism derived class with shape as its base class
RectPrism::RectPrism(double width, double length, double height):Shape("RectPrism")
{
  //intializes the variables of the shape to the inputted variables
  width_ = width;
  length_ = length;
  height_ = height;
}

//calculates and returns the area of a rectangular prism
double RectPrism::getArea()const
{
  //returns the area of the rectangular prism
  return 2*(width_*length_ + width_*height_ + length_*height_);
}

//calculates and returns the volume of a rectangular prism
double RectPrism::getVolume()const
{
  //returns the area of the rectangular prism
  return (length_ * width_ * height_);
}

//given two rectangular prisms, returns a rectangular prism whose width, length, and height are the sum
RectPrism RectPrism::operator + (const RectPrism& rectp)
{
  //returns a rectangular prism whose sum is of the two given rectangular prisms
  return RectPrism(width_ + rectp.getWidth(), length_ + rectp.getLength(), height_ + rectp.getHeight());
}

//given two rectangular prisms, returns a rectangular prism whose width, length, and height are the difference
RectPrism RectPrism::operator - (const RectPrism& rectp)
{
  //sets the shape's variables to the difference or to zero depending on if the value is negative
  int negativeW = width_ - rectp.getWidth() <= 0 ? 0 : width_ - rectp.getWidth();
  int negativeL = length_ - rectp.getLength() <= 0 ? 0 : length_ - rectp.getLength();
  int negativeH = height_ - rectp.getHeight() <= 0 ? 0 : height_ - rectp.getHeight();

  //returns a rectangular prism that is the difference of the two given rectangular prism
  return RectPrism(negativeW, negativeL, negativeH);
}

double RectPrism::getWidth()const{return width_;}
double RectPrism::getHeight()const{return height_;}
double RectPrism::getLength()const{return length_;}



// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects
vector<Shape*> CreateShapes(char* file_name){
	//@@Insert your code here

//intializes and sets temporary variables to be sent to the constructor
  string name;
  double radius, length, width, height, number;

  //reads the given file
  std::vector<Shape*> givenShapes;
  ifstream ifs (file_name, std::ifstream::in);

  //checks which shape is being read and intializes a new version of that shape
  ifs >> number;
  while (number > 0)
  {
      //creates a new circle with a given radius
      Shape* shape_ptr;
      ifs >> name;
      if (name == "Circle")
      {
          ifs >> radius;
          shape_ptr = new Circle(radius);
      }
      //creates a new rectangle with given width and length
      if (name == "Rectangle")
      {
          ifs >> width >> length;
          shape_ptr = new Rectangle(width, length);
      }
      //creates a new rectangular prism with given width, length, and height
      if (name == "RectPrism")
      {
          ifs >> width >> length >> height;
          shape_ptr = new RectPrism(width, length, height);
      }
      //creates a new sphere with a given radius
      if (name == "Sphere")
      {
          ifs >> radius;
          shape_ptr = new Sphere(radius);
      }

      //checks next line for a new shaoe
      number--;
      givenShapes.push_back(shape_ptr);
  }

  //closes file and returns vector pointer
  ifs.close();
  return vector<Shape*>(givenShapes); // please remeber to modify this line to return the correct value
}

// call getArea() of each object
// return the max area
double MaxArea(vector<Shape*> shapes){
	double max_area = 0;
	//@@Insert your code here

  //traverses through every shape
	for(unsigned i = 0; i < shapes.size(); i++)
  {
    //gets the area of every shape
		if(shapes[i]->getArea() > max_area)
    {
      //sets max_area to the maximum area found
			max_area = shapes[i]->getArea();
		}
	}
  //returns the max area of an object
	return max_area;
}


// call getVolume() of each object
// return the max volume
double MaxVolume(vector<Shape*> shapes){
	double max_volume = 0;
	//@@Insert your code here

  //traverses through every shape
  for(unsigned i = 0; i < shapes.size(); i++)
  {
		if(shapes[i]->getVolume() > max_volume)
    {
      //sets max_volume to the maximum volume found
			max_volume = shapes[i]->getVolume();
		}
	}
  //returns the max volume of an object
	return max_volume;
}
