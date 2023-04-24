#include <map>
#include <ostream>
#include <set>
#include <string>
#include <vector> 

template<typename F>
class Monomial;

template<typename F>
Monomial<F> operator + (const Monomial<F>& lhs, const Monomial<F>& rhs);

template<typename F>
Monomial<F> operator * (const Monomial<F>& lhs, const Monomial<F>& rhs);

template<typename F>
bool similar(const Monomial<F>& lhs, const Monomial<F>& rhs);

template<typename F>
bool operator < (const Monomial<F>& lhs, const Monomial<F>& rhs);

template<typename F>
bool operator == (const Monomial<F>& lhs, const Monomial<F>& rhs);

template<typename F>
std::ostream& operator<<(std::ostream&, const Monomial<F>&);

template<typename F>
class Monomial {
    F coef;
    std::map<std::string, int> deg;  //maps variable to its degree

public:
    Monomial() {
        coef = 0;
    }

    Monomial(const F& coef = 1, const std::vector<std::pair<std::string, int>>& degrees = {}) : coef(coef) {
        for (const auto& [variable, degree] : degrees) {
            if (degree) {
                deg[variable] = degree;
            }
        }
        if (coef == 0) {
            deg.clear();
        }
    }

    int Degree() const;
    int VarDeg(const std::string& var) const {
        if (deg.find(var) == deg.end()) {
            return 0;
        } else {
            return deg.at(var);
        }
    }

    friend Monomial operator + <> (const Monomial&, const Monomial&);
    friend Monomial operator * <> (const Monomial&, const Monomial&);
    friend std::ostream& operator<< <> (std::ostream&, const Monomial&);
    friend bool similar <> (const Monomial&, const Monomial&);
    friend bool operator < <> (const Monomial&, const Monomial&);
};

template<typename F>
int Monomial<F>::Degree() const {
    int res = 0;
    for (const auto& [variable, degree] : deg) {
        res += degree;
    }
    return res;
}

template<typename F>
int deg(const Monomial<F>& m) {
    return m.Degree();
}

template<typename F>
Monomial<F> operator + (const Monomial<F>& lhs, const Monomial<F>& rhs) {
    if (!similar(lhs, rhs) || lhs.coef == -rhs.coef) {
        return Monomial<F>();
    } else {
        Monomial<F> res = lhs;
        res.coef += rhs.coef;
        return res;
    }
}

template<typename F>
Monomial<F> operator * (const Monomial<F>& lhs, const Monomial<F>& rhs) {
    Monomial<F> res;
    res.coef = lhs.coef * rhs.coef;
    if (res.coef) {
        for (const auto& [var, deg] : lhs.deg) {
            res.deg[var] += deg;
        }
        for (const auto& [var, deg] : rhs.deg) {
            res.deg[var] += deg;
            if (!res.deg[var]) {
                res.deg.erase(var);
            }
        }
    }
    return res;
}

template<typename F>
bool similar(const Monomial<F>& lhs, const Monomial<F>& rhs) {
    std::set<std::string> variables;
    for (const auto& [variable, degree] : lhs.deg) {
        variables.insert(variable);
    }
    for (const auto& [variable, degree] : rhs.deg) {
        variables.insert(variable);
    }

    bool res = true;
    for (const auto& variable : variables) {
         if (lhs.deg.find(variable) == lhs.deg.end()) {
            res = false;
        } else if (rhs.deg.find(variable) == rhs.deg.end()) {
            res = false;
        } else if (lhs.deg.at(variable) < rhs.deg.at(variable)) {
            res = false;
        } else if (lhs.deg.at(variable) > rhs.deg.at(variable)) {
            res = false;
        }  
    }
    return res;  
}

template<typename F>
bool operator < (const Monomial<F>& lhs, const Monomial<F>& rhs) {
    std::set<std::string> variables;
    for (const auto& [variable, degree] : lhs.deg) {
        variables.insert(variable);
    }
    for (const auto& [variable, degree] : rhs.deg) {
        variables.insert(variable);
    }

    int similarity = 0;
    for (const auto& variable : variables) {
        if (lhs.deg.find(variable) == lhs.deg.end()) {
            similarity = -1;
        } else if (rhs.deg.find(variable) == rhs.deg.end()) {
            similarity = 1;
        } else if (lhs.deg.at(variable) < rhs.deg.at(variable)) {
            similarity = -1;
        } else if (lhs.deg.at(variable) > rhs.deg.at(variable)) {
            similarity = 1;
        }
        if (similarity) {
            break;
        }
    }
    if (similarity == -1
            || similarity == 0 && lhs.coef < rhs.coef) {
        return true;
    }
    return false;
}

template<typename F>
std::ostream& operator<<(std::ostream& os, const Monomial<F>& m) {
    os << m.coef;
    for (const auto& [var, deg] : m.deg) {
        if (deg) {
            os << " * " << var << '^' << deg;
        }
    }
    return os;
}
