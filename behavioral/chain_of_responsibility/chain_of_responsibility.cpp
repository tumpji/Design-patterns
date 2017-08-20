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

// example of chain of responsibility desing pattern

#include <iostream>

class Handler {
public:
    Handler () : successor(nullptr) {}
    virtual ~Handler () {};

    virtual void HandleRequest() = 0;


    void set_succesor ( Handler * succ ) { successor = succ; };

protected:
    Handler* successor;
};


class ConcreteHandler1 : public Handler {
public:
    virtual void HandleRequest () { 
        std::cout << "ConcreteHandler1 handle" << std::endl;
        if ( successor != nullptr ) { 
            successor->HandleRequest();
        } else {
            std::cout << "End ConcreteHandler1" << std::endl;
        }
    }
};

class ConcreteHandler2 : public Handler {
public:
    virtual void HandleRequest () { 
        std::cout << "ConcreteHandler2 handle" << std::endl;
        if ( successor != nullptr ) {
            successor->HandleRequest();
        } else {
            std::cout << "End ConcreteHandler2" << std::endl;
        }
    }
};


/////////////////////// demo ////////////////////

int main () {
    Handler   *a = new ConcreteHandler1,
              *b = new ConcreteHandler2,
              *c = new ConcreteHandler1,
              *d = new ConcreteHandler1;

    a->HandleRequest();

    std::cout << std::endl;
    a->set_succesor(b);
    a->HandleRequest();

    std::cout << std::endl;
    b->set_succesor(c);
    a->HandleRequest();

    std::cout << std::endl;
    c->set_succesor(d);
    a->HandleRequest();


    delete a;
    delete b;
    delete c;
    delete d;
}


