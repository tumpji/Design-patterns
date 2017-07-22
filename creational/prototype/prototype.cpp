//This file is part of Thread-safe-design-patterns.
//
//    Thread-safe-design-patterns is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    Thread-safe-design-patterns is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public License
//    along with Thread-safe-design-patterns.  If not, see <http://www.gnu.org/licenses/>.

// normal prototype implementation (without synchronization)
// threre isn't need for it

class PrototypeA {
public:
    virtual PrototypeA* clone () = 0;
    virtual void who () = 0;
};

class ConcretePrototypeA1 : public PrototypeA {
    ConcretePrototypeA1 ( const ConcretePrototypeA1& ) {};
public:
    ConcretePrototypeA1 () {}
    virtual PrototypeA* clone () { return new ConcretePrototypeA1(*this); }
    virtual void who ();
};

class ConcretePrototypeA2 : public PrototypeA {
    ConcretePrototypeA2 ( const ConcretePrototypeA2& ) {};
public:
    ConcretePrototypeA2 () {};
    virtual PrototypeA* clone () { return new ConcretePrototypeA2(*this); }
    virtual void who ();
};


class PrototypeB {
public:
    virtual PrototypeB* clone () = 0;
    virtual void who () = 0;
};

class ConcretePrototypeB1 : public PrototypeB {
    ConcretePrototypeB1 ( const ConcretePrototypeB1& ) {};
public:
    ConcretePrototypeB1 () {}
    virtual PrototypeB* clone () { return new ConcretePrototypeB1(*this); }
    virtual void who ();
};

class ConcretePrototypeB2 : public PrototypeB {
    ConcretePrototypeB2 ( const ConcretePrototypeB2& ) {};
public:
    ConcretePrototypeB2 () {}
    virtual PrototypeB* clone () { return new ConcretePrototypeB2(*this); }
    virtual void who ();
};

class Factory {
public:
    Factory (PrototypeA* a, PrototypeB* b) {
        this->a = a; this->b = b;
    }

    virtual PrototypeA* MakeA () { return a->clone(); }
    virtual PrototypeB* MakeB () { return b->clone(); }
    
protected:
    PrototypeA* a;
    PrototypeB* b;
};





/////////// demo /////////////

#include <iostream>

void ConcretePrototypeA1::who() {
    std::cout << "A1" << std::endl;
}
void ConcretePrototypeA2::who() {
    std::cout << "A2" << std::endl;
}
void ConcretePrototypeB1::who() {
    std::cout << "B1" << std::endl;
}
void ConcretePrototypeB2::who() {
    std::cout << "B2" << std::endl;
}



int main () {
    // memory leak !!!
    Factory factory ( new ConcretePrototypeA1(/* args ... */), new ConcretePrototypeB2() );
    factory.MakeA()->who();
    factory.MakeB()->who();

    Factory factory2 ( new ConcretePrototypeA2(), new ConcretePrototypeB1() );
    factory2.MakeA()->who();
    factory2.MakeB()->who();

}
