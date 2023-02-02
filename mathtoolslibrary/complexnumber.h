#ifndef COMPLEXNUMBER_H
#define COMPLEXNUMBER_H
#include <stdio.h>
#include <math.h>
#define PI acos(-1)
class complexnumber
{
public:
    double Re;
    double Im;
    double r;     //[0,+infinity)
    double theta; //(-PI,PI]
    complexnumber();
    complexnumber(const long double x, const long double y, int opt);
    void print(int opt)
    {
        switch (opt)
        {
        case 0:
            printf("(%lf+%lfi)", this->Re, this->Im);
            break;
        case 1:
            printf("(%lf*e^i%lf)", this->r, this->theta);
            break;
        }
    }
    void fprint(FILE *f, int opt)
    {
        switch (opt)
        {
        case 0:
            fprintf(f, "(%lf+%lfi)", this->Re, this->Im);
            break;
        case 1:
            fprintf(f, "(%lf*e^i%lf)", this->r, this->theta);
            break;
        }
    }
    void scan(int opt)
    {
        switch (opt)
        {
        case 0:
            scanf("%*[^(]");
            scanf("(%lf+%lfi)", &this->Re, &this->Im);
            this->r = sqrt(this->Re * this->Re + this->Im * this->Im);
            this->theta = atan2(this->Im, this->Re);
            break;
        case 1:
            scanf("%*[^(]");
            scanf("(%lf*e^i%lf)", &this->r, &this->theta);
            this->Re = this->r * cos(this->theta);
            this->Im = this->r * sin(this->theta);
            break;
        }
    }
    void fscan(FILE *f, int opt)
    {
        switch (opt)
        {
        case 0:
            fscanf(f, "%*[^(]");
            fscanf(f, "(%lf+%lfi)", &this->Re, &this->Im);
            this->r = sqrt(this->Re * this->Re + this->Im * this->Im);
            this->theta = atan2(this->Im, this->Re);
            break;
        case 1:
            fscanf(f, "%*[^(]");
            fscanf(f, "(%lf*e^i%lf)", &this->r, &this->theta);
            this->Re = this->r * cos(this->theta);
            this->Im = this->r * sin(this->theta);
            break;
        }
    }
};
complexnumber operator+(const complexnumber &a, const complexnumber &b)
{
    complexnumber c;
    c.Re = a.Re + b.Re;
    c.Im = a.Im + b.Im;
    c.r = sqrt(c.Re * c.Re + c.Im * c.Im);
    c.theta = atan2(c.Im, c.Re);
    return c;
}
complexnumber operator-(const complexnumber &a, const complexnumber &b)
{
    complexnumber c;
    c.Re = a.Re - b.Re;
    c.Im = a.Im - b.Im;
    c.r = sqrt(c.Re * c.Re + c.Im * c.Im);
    c.theta = atan2(c.Im, c.Re);
    return c;
}
complexnumber operator*(const complexnumber &a, const complexnumber &b)
{
    complexnumber c;
    c.r = a.r * b.r;
    c.theta = a.theta + b.theta;
    c.theta = c.theta - (ceil(c.theta / (2 * PI)) * (2 * PI)) + (2 * PI);
    if (c.theta > PI)
    {
        c.theta = c.theta - (2 * PI);
    }
    c.Re = c.r * cos(c.theta);
    c.Im = c.r * sin(c.theta);
    return c;
}
complexnumber operator/(const complexnumber &a, const complexnumber &b)
{
    complexnumber c;
    c.r = a.r / b.r;
    c.theta = a.theta - b.theta;
    c.theta = c.theta - (ceil(c.theta / (2 * PI)) * (2 * PI)) + (2 * PI);
    if (c.theta > PI)
    {
        c.theta = c.theta - (2 * PI);
    }
    c.Re = c.r * cos(c.theta);
    c.Im = c.r * sin(c.theta);
    return c;
}
complexnumber operator^(const complexnumber &a, const complexnumber &b)
{
    if (a.r == 0)
    {
        complexnumber ans(0, 0, 0);
        return ans;
    }
    complexnumber c(log(a.r), a.theta, 0);
    complexnumber d = b * c;
    complexnumber ans(exp(d.Re), d.Im, 1);
    return ans;
}
bool operator==(const complexnumber &a, const complexnumber &b)
{
    if ((a - b).r < 1e-7)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
complexnumber::complexnumber()
{
    this->Re = 0;
    this->Im = 0;
    this->r = 0;
    this->theta = 0;
}
complexnumber::complexnumber(const long double x, const long double y, int opt)
{
    switch (opt)
    {
    case 0:
        this->Re = x;
        this->Im = y;
        this->r = sqrt(this->Re * this->Re + this->Im * this->Im);
        this->theta = atan2(this->Im, this->Re);
        break;
    case 1:
        this->r = x;
        this->theta = y;
        this->Re = this->r * cos(this->theta);
        this->Im = this->r * sin(this->theta);
        break;
    }
}
#endif
