#include <iostream>

using namespace std;

class Rectangle
{
private:
    int width;
	int length;
public:
    /**
     * Default Constructor
     */
    Rectangle()
    {
        width = length = 5;
    }
    Rectangle(int w, int l);
    void setValues(int w, int l);
    void setWidth(int w);
    void setLength(int l);
	int getWidth() { return width; }
	int getLength() { return length; }
	int getArea() { return width * length; };
	void grow(int factor);
};
/**
 * @param w width
 * @param l length
 */
Rectangle::Rectangle(int w, int l)  // notice no return type is needed!
{
    setValues(w, l);
}
/**
 * @param w width
 * @param l length
 */
void Rectangle::setValues(int w, int l) {
    width = w;
    length = l;
}
void Rectangle::setWidth(int w)
{
    width = w;
}
void Rectangle::setLength(int l)
{
    length = l;
}
void Rectangle::grow(int factor)
{
    width = width * factor;
    length = length * factor;
}
int main()
{
   Rectangle rect;
   Rectangle * p_rect = &rect;
   cout << p_rect->getWidth() << endl;

   // Rectangle manyRects[5]; // Create an array of 5 objects
   // manyRects[0].setValues(3,2);
   // manyRects[1].setValues(6,4);
   // manyRects[2].setValues(9,8);
   // manyRects[3].setValues(12,16);
   // manyRects[4].setValues(15,32);

   // cout << manyRects[0].getWidth() << " * " << manyRects[0].getLength() << " = ";
   // cout <<  manyRects[0].getArea() << endl;

   // cout << manyRects[1].getWidth() << " * " << manyRects[1].getLength() << " = ";
   // cout <<  manyRects[1].getArea() << endl;

   // cout << manyRects[2].getWidth() << " * " << manyRects[2].getLength() << " = ";
   // cout <<  manyRects[2].getArea() << endl;

   // cout << manyRects[3].getWidth() << " * " << manyRects[3].getLength() << " = ";
   // cout <<  manyRects[3].getArea() << endl;

   // cout << manyRects[4].getWidth() << " * " << manyRects[4].getLength() << " = ";
   // cout <<  manyRects[4].getArea() << endl;

   // Rectangle myRect(6, 8);
   // cout << myRect.getWidth() << " * " << myRect.getLength() << " = ";
   // cout <<  myRect.getArea() << endl;

   // myRect.grow(3);
   // cout << myRect.getWidth() << " * " << myRect.getLength() << " = ";
   // cout <<  myRect.getArea() << endl;

   // Rectangle myRect2; // note that no values are passed for width & length
   // cout << myRect2.getWidth() << " * " << myRect2.getLength() << " = ";
   // cout <<  myRect2.getArea() << endl;

}// Put the function definitions here
