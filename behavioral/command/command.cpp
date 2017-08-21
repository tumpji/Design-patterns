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
#include <deque>
#include <stack>

class Command {
    public:
        Command ( int* result ) : result_ptr(result), log_output(std::cerr) {}

        virtual void Execute () = 0;
        virtual void UnExecute () = 0;

    protected:
        int*            result_ptr;
        std::ostream&   log_output;
};


class Command_add : public Command {
    public:
        Command_add ( int* result, int value ) : Command(result), value(value) {}

        virtual void Execute () {
            log_output << "changing " << *result_ptr << " to ";
            *result_ptr += value;
            log_output << *result_ptr << "\t(add " << value << ")" << "\n";
        }
        virtual void UnExecute () {
            log_output << "unchanging " << *result_ptr << " to ";
            *result_ptr -= value;
            log_output << *result_ptr << "\t(add " << value << ")" << "\n";
        }
    protected:
        int value;
};

class Command_mul : public Command {
    public:
        Command_mul ( int* result, int value ) : Command(result), value(value) {}

        virtual void Execute () {
            log_output << "changing " << *result_ptr << " to ";
            *result_ptr *= value;
            log_output << *result_ptr << "\t(mul by " << value << ")" << "\n";
        }
        virtual void UnExecute () {
            log_output << "unchanging " << *result_ptr << " to ";
            *result_ptr /= value;
            log_output << *result_ptr << "\t(mul by " << value << ")" << "\n";
        }
    protected:
        int value;
};

template<class T, class ...Args>
std::shared_ptr<Command> make_command ( Args... args ) {
    return std::make_shared<T>(args...);
}

class Application {
    public:
        void add_command ( std::shared_ptr<Command> c ) {
            command_queue.push_back(c);
        }

        void redo () {
            auto c = command_queue.front();
            command_queue.pop_front();
            command_queue_undo.push_front(c);

            c->Execute();
        }
        void undo () {
            auto c = command_queue_undo.front();
            command_queue_undo.pop_front();
            command_queue.push_front(c);

            c->UnExecute();
        }

    protected:
        std::deque<std::shared_ptr<Command>> command_queue;
        std::deque<std::shared_ptr<Command>> command_queue_undo;
};

///////////// demo ?//////////////////


int main () { 
    int value = 0;
    Application a;

    a.add_command( make_command<Command_add>(&value, 2) );
    a.add_command( make_command<Command_mul>(&value, 3) );
    a.add_command( make_command<Command_add>(&value, 4) );
    a.add_command( make_command<Command_mul>(&value, 5) );

    a.redo();
    a.redo();
    a.redo();
    a.redo();

    a.undo();
    a.undo();
    a.undo();
    a.undo();
}


