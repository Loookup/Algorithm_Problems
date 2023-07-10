#include <iostream>
#include <memory>
using namespace std;

class Rectangle {
    private:
        int width, height;
    public:
        Rectangle(int width, int height): width(width), height(height){}            /*if(width > 0 && width <= 1000 && height >0 && height <= 2000){
                width = width; 
                height = height;}
                
        }*/
        int get_width() const {
            return width;
        }
        int get_height() const {
            return height;
        }
        void set_width(int width) {
            if(width > 0 && width <= 1000)
                (this->width) = width;
            else
                (this->width) = (this->width);
        }
        void set_height(int height) {
            if(height > 0 && height <= 2000)
                (this->height) = height;
            else
                (this->height) = (this->height);
        }
        int area() const {
             auto parea = unique_ptr <int> (new int);
            *parea = width * height;
            return *parea;
        }
        int perimeter() const {
            auto pperimeter = unique_ptr <int> (new int);
            *pperimeter = 2*width + 2*height;
            return *pperimeter;
        }
        bool is_square() const {
            if(width == height)
                return true;
            else
                return false;
        }
};
