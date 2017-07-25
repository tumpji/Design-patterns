
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

// normal builder implementation (without synchronization)


/* defines interface for all concrete builders
 * defines implicit implementation (nothing)
 */

#include <string>

class Builder {
public:
    virtual void text        ( std::string ) { }
    virtual void next_level  ( ) { }
};

class ConcreteBuilder_textonly : public Builder {
public:
    ConcreteBuilder_textonly () {}

    virtual void text        ( std::string x ) { result += x; }
    // next level  nothing

    std::string get_result () { return result; }
private:
    std::string     result;
}; 

class ConcreteBuilder_number_level : public Builder {
public:
    ConcreteBuilder_number_level () { level = 0; }

    // text - nothing
    virtual void next_level ( ) { level += 1; }

    int get_result () { return level; }
private:
    int level;
};

class Director {
public:
    Director () { }

    void Construct ( std::string src, Builder * builder ) {
        // construction of complex object
        for ( unsigned int i = 0; i < src.size(); ++i ) {
            if ( src[i] == '>' )
                builder->next_level();
            else {
                char ret [2] = { src[i], 0x00 };
                builder->text( std::string(ret) );
            }
        }
    }

};


///////////////// demo /////////////////
#include <iostream>

int main () {
    std::string str = "a>bcd>e";

    auto director = Director();

    {
        auto builder = new ConcreteBuilder_textonly;
        director.Construct( str, builder );
        auto v = builder->get_result();

        std::cout << v  << std::endl;
    }
    {
        auto builder = new ConcreteBuilder_number_level;
        director.Construct( str, builder );
        auto v = builder->get_result();

        std::cout << v  << std::endl;
    }
}


