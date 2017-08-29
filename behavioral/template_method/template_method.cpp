//This file is part of Design-patterns.
//
//    Design-patterns is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    Design-patterns is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public License
//    along with Design-patterns.  If not, see <http://www.gnu.org/licenses/>.

// example of template method desing pattern


class AbstractClass {
    public:
        // defines basic (not concrete) way to compute algorythm
        int TemplateMethod(int a, int b) {
            return PrimitiveOperation1(a) + PrimitiveOperation2(b) + DoHook();
        }
    protected:
        // defines primitive operations that must be rewriten
        virtual int PrimitiveOperation1(int) = 0;
        virtual int PrimitiveOperation2(int) = 0;
        // or hook operations that can be rewriten
        virtual int DoHook () { return 0; }
};

class ConcreteClass1 : public AbstractClass {
    // adds steps to algorythm
    virtual int PrimitiveOperation1 ( int a ) { return a; }
    virtual int PrimitiveOperation2 ( int b ) { return b; }
};


class ConcreteClass2 : public AbstractClass {
    virtual int PrimitiveOperation1 ( int a ) { return 2*a; }
    virtual int PrimitiveOperation2 ( int b ) { return 2*b; }
    // posibly rewrites hook operations
    virtual int DoHook () { return 1; }
};


//////////////////////////// demo /////////////

#include <iostream>

int main ( ) {
    ConcreteClass1 CC1;
    ConcreteClass2 CC2;

    std::cout << "CC1: " << CC1.TemplateMethod(1,1) << std::endl;
    std::cout << "CC1: " << CC2.TemplateMethod(1,1) << std::endl;


    return 0;
}



