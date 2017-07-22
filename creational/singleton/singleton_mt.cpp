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

// It behaves like non-thread safe variant.
// Only difference is that threre is 
//   only one call to constructor in multithreaded aplications.
// 
// After constor call there is no difference between standart implementation!

#include <mutex>
#include <memory>

class Singleton {
    public:
        // get instance
        static Singleton* Instance();
    protected:
        // constructor
        Singleton();
        ~Singleton();
    private:
        static Singleton* get_first ();
        static Singleton* get_after ();

        static Singleton* (*act_behavior) ();

        // location of maximum one instance (nullptr otherwise)
        static std::unique_ptr<Singleton> _instance;

        // mutex for get_first
        static std::mutex mtx;

        friend struct std::default_delete<Singleton>;
};

std::unique_ptr<Singleton>  Singleton::_instance = std::unique_ptr<Singleton>(nullptr);
Singleton*  (*Singleton::act_behavior) () = &Singleton::get_first;
std::mutex  Singleton::mtx; 

// thread safe construction
Singleton* Singleton::get_first () {
    // get instance for first few acesses
    std::lock_guard<std::mutex> lck (Singleton::mtx);

    if ( _instance == nullptr ) {
        _instance = std::unique_ptr<Singleton>(new Singleton);
        act_behavior = &get_after;
    }
    return _instance.get();
}

// get instance without condition
Singleton* Singleton::get_after () {
    // get instance after first initialization
    return _instance.get();
}

// get instance
Singleton* Singleton::Instance() {
    return (*act_behavior)();
}



/////////////////////// demo ///////////////////////

#include <iostream>

// constructor
Singleton::Singleton () {
    std::cout << "Singleton::Singleton()" << std::endl;
}
Singleton::~Singleton () {
    std::cout << "Singleton::~Singleton()" << std::endl;
}

int main () {
    Singleton::Instance();
    Singleton::Instance();
    Singleton::Instance();
    Singleton::Instance();
}
