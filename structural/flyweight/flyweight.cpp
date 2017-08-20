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

// example of flyweight 

#include <vector>
#include <map>

class ExcentricState {
    // depens on flyweight context 
};

class Flyweight {
public:
    virtual void Operation ( ExcentricState ) = 0;
};

class ConcreteFlyweight : public Flyweight {
public:
    virtual void Operation ( ExcentricState es ) { (void)es; };
    
protected:
    // stored in flyweight
    int intristicState;
    //int _character_code;
    //int _style_index;
};

class UnscharedConcreteFlyweight : public Flyweight {
public:
    virtual void Operation ( ExcentricState es ) { (void)es; };

protected:
    // usual state
    int allState;
};



// 
class FlyweightFactory {
public:
    Flyweight* GetFlyweight ( int key ) {
        auto s = flyweightPool.find( key );
        if ( s == flyweightPool.end() ) {
            auto cfw = new ConcreteFlyweight;
            flyweightPool[key] = cfw;
            return cfw;
        }
        else return s->second;
    }
protected:
    std::map<int, Flyweight*> flyweightPool; // or map ...
};
    


