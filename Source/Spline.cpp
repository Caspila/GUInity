//
//  Spline.cpp
//  GUInity_MacOS
//
//  Created by Guilherme Cunha on 2015-06-07.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#include "Spline.hpp"

double Spline::factorialLookup[] =
{
    1.0,
    1.0,
    2.0,
    6.0,
    24.0,
    120.0,
    720.0,
    5040.0,
    40320.0,
    362880.0,
    3628800.0,
    39916800.0,
    479001600.0,
    6227020800.0,
    87178291200.0,
    1307674368000.0,
    20922789888000.0,
    355687428096000.0,
    6402373705728000.0,
    121645100408832000.0,
    2432902008176640000.0,
    51090942171709440000.0,
    1124000727777607680000.0,
    25852016738884976640000.0,
    620448401733239439360000.0,
    15511210043330985984000000.0,
    403291461126605635584000000.0,
    10888869450418352160768000000.0,
    304888344611713860501504000000.0,
    8841761993739701954543616000000.0,
    265252859812191058636308480000000.0,
    8222838654177922817725562880000000.0,
    263130836933693530167218012160000000.0

};

double Spline::factorial(int n)
{
    if(n < 0 || n > 32)
    {
        std::cout << "Error: Trying to get factorial bigger or lesser than 0-32" << std::endl;
        return 0.0f;
    }
    
    return factorialLookup[n]; /* returns the value n! as a SUMORealing point number */
}

double Spline::Ni(int n, int i)
{

        double ni;
        double a1 = factorial(n);
        double a2 = factorial(i);
        double a3 = factorial(n - i);
        ni =  a1/ (a2 * a3);
        return ni;

}

double Spline::bernstein(int n, int i, double t)
{
    double basis;
    double ti; /* t^i */
    double tni; /* (1 - t)^i */
    
    /* Prevent problems with pow */
    
    if (t == 0.0 && i == 0)
        ti = 1.0;
    else
        ti = pow(t,i);
//        ti = Math.Pow(t, i);
    
    if (n == i && t == 1.0)
        tni = 1.0;
    else
                tni = pow((1-t),(n-i));
//        tni = Math.Pow((1 - t), (n - i));
    
    //Bernstein basis
    basis = Ni(n, i) * ti * tni;
    return basis;
}

glm::vec3 Spline::evaluate3D(float t)
{
    
    glm::dvec3 point;
    
    for (int i = 0; i != points.size(); i++)
    {
        double basis = bernstein(points.size() - 1, i, t);
        
        point += points.at(i) * basis;
    }
    return point;
}

glm::vec2 Spline::evaluate2D(float t)
{
    glm::vec3 point = evaluate3D(t);
    return glm::vec2(point.x,point.y);
}

double Spline::evaluate(float t)
{
    return evaluate3D(t).x;
}