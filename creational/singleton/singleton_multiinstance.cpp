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

// thread UNsafe singleton implementation
// only C++14 +  (template varargs)
// instance accepts Singleton::IID - it's 'Instance ID'
// for each ID creates it's own singleton based on ID


#include <map>
#include <tuple>
#include <memory>

#define THREAD_SAFE

#ifdef THREAD_SAFE
    #include <mutex>
#endif

template<class ...IID>
class Singleton {
    public:
        // get instance of specific IID
        static Singleton<IID...>* Instance (IID...);

        ~Singleton();
    protected:
        // constructor
        Singleton(IID...);
    private:
        // maps IID to memory location
        using _TypeID  = std::tuple<IID...>;
        using _TypePtr = std::shared_ptr<Singleton<IID...>>;

        static std::map<_TypeID, _TypePtr> _registry; 

#ifdef THREAD_SAFE
        static std::mutex mtx;
#endif
};

template<class ...IID> 
    std::map< 
        typename Singleton<IID...>::_TypeID, 
        typename Singleton<IID...>::_TypePtr 
            >   Singleton<IID...>::_registry;

#ifdef THREAD_SAFE
template<class ...IID>
    std::mutex Singleton<IID...>::mtx;
#endif


// get instance
template<class ...IID>
Singleton<IID...>* Singleton<IID...>::Instance(IID ... args) {
    #ifdef THREAD_SAFE
    std::lock_guard<std::mutex> lck ( Singleton<IID...>::mtx );
    #endif
    auto regptr = _registry.find(std::make_tuple(args...));

    if ( regptr != _registry.end() ) // already exists
        return regptr->second.get();
    else {
        // create one
        auto i = Singleton<IID...>::_TypePtr(new Singleton(args...));
        auto g = std::pair< Singleton<IID...>::_TypeID, Singleton<IID...>::_TypePtr >
                    ( std::make_tuple(args...), i );
        _registry.insert( g );
        return i.get();
    }
}



/////////////// demo //////////////

#include <iostream>

template<class First>
void print_all (std::ostream& output, First frst) {
    output << " " << frst << " ";
}

template<class First, class ...Others>
void print_all (std::ostream& output, First frst, Others... tail) {
    output << " " << std::forward<First>(frst) << ",";
    print_all<Others...>(output, tail...);
}


// constructor
template<class ...IID>
Singleton<IID...>::Singleton (IID... args) {
    std::cout << "Singleton::Singleton(";
    print_all<IID...>( std::cout , args... );
    std::cout << ")" << std::endl;
}

template<class ...IID>
Singleton<IID...>::~Singleton () {
    std::cout << "Singleton::~Singleton()" << std::endl;
}


int main () {
    Singleton<int, float>::Instance(1,1.5);
    Singleton<int, float>::Instance(1,1.5);
    Singleton<int, float>::Instance(2,2.5);
    Singleton<int, float>::Instance(1,1.5);
    Singleton<int, double>::Instance(2,2.5);
}


