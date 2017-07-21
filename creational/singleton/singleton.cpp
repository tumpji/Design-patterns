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

// normal singleton implementation

#include <iostream>

#include <memory>

class Singleton {
    public:
        // get instance
        static Singleton* Instance();
        ~Singleton ();
    protected:
        // constructor
        Singleton();
    private:
        // location of maximum one instance (nullptr otherwise)
        static std::shared_ptr<Singleton> _instance;
};

std::shared_ptr<Singleton> Singleton::_instance ( nullptr );

// get instance
Singleton* Singleton::Instance() {
    if ( _instance.get() == nullptr ) {
        _instance = std::shared_ptr<Singleton>(new Singleton);
    }
    return _instance.get();
}

// constructor
Singleton::Singleton () {
    std::cout << "Singleton::Singleton()" << std::endl;
}

Singleton::~Singleton () {
    std::cout << "Singleton::~Singleton()" << std::endl;
}


///////////////////// demo ////////////////

int main () {
    Singleton::Instance();
    Singleton::Instance();
    Singleton::Instance();
}
