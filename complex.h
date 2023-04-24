#include <cmath>

class Complex {
    double x;
    double y;

public:
    Complex() = default;

    Complex(double a, double b = 0.0): x(a), y(b) {
    }

    double Re() const {
        return x;
    }

    double Im() const {
        return y;
    }

    Complex Conjugate() const {
        return Complex(x, -y);
    }

    Complex operator += (const Complex& rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    Complex operator -= (const Complex& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    bool operator == (const Complex& rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    bool operator != (const Complex& rhs) const {
        return x != rhs.x || y != rhs.y;
    }
};

double Abs(const Complex& c) {
    return sqrt(c.Re() * c.Re() + c.Im() * c.Im());
}

Complex operator + (Complex a) {
    return a;
}

Complex operator - (Complex a) {
    return Complex(-a.Re(), -a.Im());
}

Complex operator + (const Complex& a, const Complex& b) {
    return Complex(a.Re() + b.Re(), a.Im() + b.Im());
}

Complex operator - (const Complex& a, const Complex& b) {
    return Complex(a.Re() - b.Re(), a.Im() - b.Im());
}

Complex operator * (const Complex& a, const Complex& b) {
    return Complex(a.Re() * b.Re() - a.Im() * b.Im(), a.Re() * b.Im() + a.Im() * b.Re());
}

Complex operator / (const Complex& a, const double b) {
    return Complex(a.Re() / b, a.Im() / b);
}

Complex operator / (const Complex& a, const Complex& b) {
    return (a * b.Conjugate()) / ((b * b.Conjugate()).Re());
}

Complex pow(Complex& a, int deg) {
    if (deg == 0) {
        return Complex(1);
    } else if (deg == 1) {
        return a;
    } else if (deg == -1) {
        return 1 / a;
    } else if (deg % 2 == 0) {
        Complex tmp = pow(a, deg / 2);
        return tmp * tmp;
    } else {
        Complex tmp = pow(a, deg / 2);
        return tmp * tmp * a;
    }
}
