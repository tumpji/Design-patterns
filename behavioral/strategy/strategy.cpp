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

// example of strategy desing pattern

#include <iostream>
#include <memory>
#include <cstring>

class Strategy {
    // strategy - declare interface - in this case I add all array members
    public:
        virtual int Algorithminterface (const int[8]) = 0;
};

class StrategySerial : public Strategy {
    // strategy regular adding
    public:
        virtual int Algorithminterface (const int vec[8]) {
            int result = 0;
            for ( int off = 0; off < 8; off += 1 )
                result += vec[off];
            return result;
        }

        static StrategySerial& Instance () { return singleton; }
    private:
        static StrategySerial singleton;
};

class StrategyBinary : public Strategy {
    // strategy - binary add
    public:
        virtual int Algorithminterface (const int vec[8]) {
            int cpy[8];
            memcpy(cpy, vec, sizeof(cpy));

            for ( int off = 1; off < 8; off *= 2 )
                for ( int i = 0; i < 8; i += 2*off ) 
                    cpy[i] += cpy[i+off];
            return cpy[0];
        }

        static StrategyBinary& Instance () { return singleton; }
    private:
        static StrategyBinary singleton;
};


StrategyBinary StrategyBinary::singleton = StrategyBinary();
StrategySerial StrategySerial::singleton = StrategySerial();


class Context {
    // defines client interface (he provides choosen strategy)
    public:
        Context ( Strategy& s ) : strategy(&s) {}

        int ContextInterface () { return strategy->Algorithminterface(data); }

    private:
        static int data[8];
        Strategy* strategy;
};

int Context::data[8] = {0,1,2,3,4,5,6,7};

///////////////////  demo //////////////////////
 
int main () {
    Context bin ( StrategyBinary::Instance() );
    std::cout << "StrategyBinary : " << bin.ContextInterface() << std::endl;

    bin = Context( StrategySerial::Instance() );
    std::cout << "StrategySerial : " << bin.ContextInterface() << std::endl;

    return 0;
}

