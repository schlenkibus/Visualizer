
#include <SFML/System/Clock.hpp>

template <class T>
class TimedObject {
public:
    TimedObject<T>(T&& t, sf::Time delay) : m_delay(delay) {
        myObj = t;
    }

    void checkIfDelete() {
        static sf::Clock clk;
        if(clk.getElapsedTime() >= m_delay) {
            delete this;
        }
    }

    T *operator*(void) const
    {
        return myObj;
    }

    ~TimedObject() {
        delete myObj;
    }
protected:
    T* myObj;
    sf::Time m_delay;
};