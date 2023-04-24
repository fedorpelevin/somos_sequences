#include <algorithm>
#include <vector>

size_t factorial(size_t n) {
    size_t res = 1;
    for (size_t i = 1; i <= n; ++i) {
        res *= i;
    }
    return res;
}

template<typename F>
class Matrix {
    /*
     *  Useful constructor for M_0 and M_1 sequences` matrixes.
     *  
     *
     *
     *  Rank computation (both classical and GM or weak rank)
     *  Determinant (both classical and d-det)
     *
     *  Useful taking minor from (m1, m2, ..., mk), (n1, n2, ..., nk)
     *
     * */
    std::vector<std::vector<F>> data;
public:
    Matrix() = default;

    Matrix(const std::vector<std::vector<F>>& data) : data(data) {
    }

    Matrix(const std::vector<std::vector<F>>& d, const std::vector<size_t> rows, const std::vector<size_t> cols) {
        data = std::vector<std::vector<F>>(rows.size(), std::vector<F>(cols.size()));
        for (int i = 0; i < rows.size(); ++i) {
            for (int j = 0; j < cols.size(); ++j) {
                data[i][j] = data[rows[i]][cols[j]];
            }
        }
    }
 
    Matrix(const Matrix& m, const std::vector<size_t> rows, const std::vector<size_t> cols) {
        data = std::vector<std::vector<F>>(rows.size(), std::vector<F>(cols.size()));
        for (int i = 0; i < rows.size(); ++i) {
            for (int j = 0; j < cols.size(); ++j) {
                data[i][j] = m.data[rows[i]][cols[j]];
            }
        }
    }


    Matrix(const std::vector<F>& sequence, size_t first_l, size_t first_r, size_t second_l, size_t second_r) {
        data = std::vector<std::vector<F>>(first_r - first_l + 1, std::vector<F>(second_r - second_l + 1));
        for (size_t i = first_l; i <= first_r; ++i) {
            for (int j = second_l; j <= second_r; ++j) {
                data[i - first_l][j - second_l] = sequence[i + j] * sequence[i - j];
            }
        }
    }

    Matrix(const std::vector<F>& sequence, const std::vector<int>& rows, const std::vector<int>& cols) {
        data = std::vector<std::vector<F>>(rows.size(), std::vector<F>(cols.size()));
        for (int i = 0; i < rows.size(); ++i) {
            for (int j = 0; j < cols.size(); ++j) {
                data[i][j] = sequence[rows[i] + cols[j]][rows[i] - cols[j]];
            }
        }
    }

    bool IsSingular() const {
        std::vector<size_t> perm(data.size());
        for (size_t i = 0; i < perm.size(); ++i) {
            perm[i] = i + 1;
        }

        size_t perm_num = factorial(data.size());
        F pos_det = F();
        F neg_det = F();
        for (size_t i = 0; i < perm_num; ++i) {
            int inv_cnt = 0;
            for (int i = 0; i < perm.size(); ++i) {
                for (int j = i + 1; j < perm.size(); ++j) {
                    if (perm[i] > perm[j]) {
                        ++inv_cnt;
                    }
                }
            }

            F mul = data[0][perm[0] - 1];
            for (size_t i = 1; i < data.size(); ++i) {
                mul = mul * data[i][perm[i] - 1];
            }

            if (inv_cnt % 2 == 0) {
                pos_det = pos_det + mul;
            } else {
                neg_det = neg_det + mul;
            }
            std::next_permutation(perm.begin(), perm.end());
        }
        //std::cout << pos_det << '\t' << neg_det << '\n';
        return neg_det == pos_det;
    }
};
