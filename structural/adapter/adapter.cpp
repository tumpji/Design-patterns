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

// normal adapter implementation 

#include <memory>

class Target {
    // target interface (abstract)
    public:
        virtual void request () = 0;
};

class Adaptee {
    // source interface
public:
    Adaptee () { };
    void specific_request () {};
};



class Adapter_object : public Target {
    // Adaptrer
public:
    Adapter_object ( std::shared_ptr<Adaptee> obj ) : obj(obj) { }
    virtual void request () {
        obj->specific_request();
    }
private:
    std::shared_ptr<Adaptee> obj;
    // next obj.
};


class Adapter_class : public Target, private Adaptee {
    // Adapter - another implementation
public:
    Adapter_class () {};
    virtual void request () {
        specific_request ();
    }

private:
    /* can be overwrten 
    void specific_request () {
    }
    */
};


/// demo 

int main () { 
    Adapter_object a ( std::make_shared<Adaptee>() );
    Adapter_class  b;

    Target& p = a;
    p.request();

    p = b;
    p.request();
}

