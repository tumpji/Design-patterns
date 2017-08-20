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

// example of Proxy (virtual) implementation 

#include <iostream>
#include <memory>


class Subject {
    // defines common interface for proxy and real subject
public:
    virtual void Request () = 0;
};


class RealSubject : public Subject {
public:
    RealSubject () { 
        std::cout << "Created Real Subject" << std::endl;
    }
    virtual void Request () { 
        std::cout << "Real request" << std::endl;
    }
};


class Proxy : public Subject {
public:
    Proxy () {
        std::cout << "Created proxy" << std::endl;
    }
    virtual void Request () {
        std::cout << "Proxy request" << std::endl;

        if ( ptr.get() == nullptr ) {
            ptr = std::make_shared<RealSubject>();
        }
        ptr->Request();
    }

private:
    std::shared_ptr<RealSubject> ptr;
};


/////////////////// demo ///////////////////

int main () {
    Proxy proxy;

    std::cout << "\n\tfirst call .Request()" << std::endl;
    proxy.Request ();

    std::cout << "\n\tsecond call .Request()" << std::endl;
    proxy.Request ();
}

