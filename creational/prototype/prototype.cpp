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

// normal prototype implementation (without synchronization)
// threre isn't need for it
//

#include <memory>

class PrototypeA {
public:
    virtual std::shared_ptr<PrototypeA> clone () = 0;
    virtual void operation () = 0;
};

class ConcretePrototypeA1 : public PrototypeA {
public:
    ConcretePrototypeA1 () {}
    ConcretePrototypeA1 ( const ConcretePrototypeA1& ) {};

    virtual std::shared_ptr<PrototypeA> clone () { 
        return std::make_shared<ConcretePrototypeA1>(*this);
    }
    virtual void operation ();
};

class ConcretePrototypeA2 : public PrototypeA {
public:
    ConcretePrototypeA2 () {};
    ConcretePrototypeA2 ( const ConcretePrototypeA2& ) {};

    virtual std::shared_ptr<PrototypeA> clone () { 
        return std::make_shared<ConcretePrototypeA2>(*this); 
    }
    virtual void operation ();
};


class PrototypeB {
public:
    virtual std::shared_ptr<PrototypeB> clone () = 0;
    virtual void operation () = 0;
};

class ConcretePrototypeB1 : public PrototypeB {
public:
    ConcretePrototypeB1 () {}
    ConcretePrototypeB1 ( const ConcretePrototypeB1& ) {};

    virtual std::shared_ptr<PrototypeB> clone () { 
        return std::make_shared<ConcretePrototypeB1>(*this); 
    }
    virtual void operation ();
};

class ConcretePrototypeB2 : public PrototypeB {
public:
    ConcretePrototypeB2 () {}
    ConcretePrototypeB2 ( const ConcretePrototypeB2& ) {};

    virtual std::shared_ptr<PrototypeB> clone () { 
        return std::make_shared<ConcretePrototypeB2>(*this); 
    }
    virtual void operation ();
};

class Factory {
public:
    Factory (std::shared_ptr<PrototypeA> a, std::shared_ptr<PrototypeB> b) {
        this->a = a; this->b = b;
    }

    virtual std::shared_ptr<PrototypeA> MakeA () { return a->clone(); }
    virtual std::shared_ptr<PrototypeB> MakeB () { return b->clone(); }
    // ...
    
protected:
    std::shared_ptr<PrototypeA> a;
    std::shared_ptr<PrototypeB> b;
};





/////////// demo /////////////

#include <iostream>

void ConcretePrototypeA1::operation() {
    std::cout << "A1" << std::endl;
}
void ConcretePrototypeA2::operation() {
    std::cout << "A2" << std::endl;
}
void ConcretePrototypeB1::operation() {
    std::cout << "B1" << std::endl;
}
void ConcretePrototypeB2::operation() {
    std::cout << "B2" << std::endl;
}



int main () {
    std::cout << "Example 1: (A1, B2)" << std::endl;
    Factory factory ( 
            std::make_shared<ConcretePrototypeA1>(/* args ... */), 
            std::make_shared<ConcretePrototypeB2>() 
            );
    factory.MakeA()->operation();
    factory.MakeB()->operation();

    std::cout << "Example 2: (A1, B2)" << std::endl;
    Factory factory2 ( 
            std::make_shared<ConcretePrototypeA2>(), 
            std::make_shared<ConcretePrototypeB1>() 
            );
    factory2.MakeA()->operation();
    factory2.MakeB()->operation();

}
