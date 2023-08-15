//
//  basicGeometric.hpp
//  chess
//
//  Created by pardo jérémie on 10/08/2023.
//

#ifndef basicGeometric_hpp
#define basicGeometric_hpp

#include <stdio.h>
#include <cstdint>
#include <memory>

//*****************
//**    POINT    **
//*****************
class Point {
public:
    Point(int32_t x, int32_t y) : _x(x), _y(y) {}
    Point(const Point&) = default;
    Point(Point&&) = default;
    Point & operator=( const Point&) = default;
    Point& operator=(Point&&) = default;
    ~Point(){}
    
    void updatePosition(int32_t x, int32_t y) {
        _x=x;
        _y=y;
    }
    int32_t getX() const { return _x; }
    int32_t getY() const { return _y; }

private:
    int32_t _x;
    int32_t _y;
};

inline bool operator==(const Point& a,const Point& b)
{
    return a.getX() == b.getX() && a.getY() == b.getY();
}

//*****************
//**    ZONES    **
//*****************
class Zone {
public:
    Zone(){};
    ~Zone(){};
   virtual bool inZone(const Point& point) const = 0;
};

class RectangleZone : public Zone {
public:
    RectangleZone( uint16_t w, uint16_t l, Point& point) : _w(w), _l(l), _leftMostPoint(point) {}
    RectangleZone( uint16_t w, uint16_t l) : _w(w), _l(l), _leftMostPoint(Point(0,0)) {}
    RectangleZone(const RectangleZone& other) : _w(other._w), _l(other._l), _leftMostPoint(other._leftMostPoint) {}
    RectangleZone(RectangleZone&&) = delete;
    RectangleZone & operator=( const RectangleZone & other ) {
        _w = other._w;
        _l = other._l;
        _leftMostPoint = other._leftMostPoint;
        return *this;
    }
    RectangleZone& operator=(RectangleZone&&) = delete;
    ~RectangleZone() {}

    // if _w = 0 or _l = 0, the zone cannot contain any Point
    bool inZone(const Point& point) const {
        return _leftMostPoint.getY() >= point.getY()  && (_leftMostPoint.getY()+ _w - 1) <= point.getY() && _leftMostPoint.getX() >= point.getX()  && (_leftMostPoint.getX() + _l - 1) <= point.getX();
    }
private:
    uint16_t _w; // width
    uint16_t _l; // length
    Point _leftMostPoint;
};
#endif /* basicGeometric_hpp */
