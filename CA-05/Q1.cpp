#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iterator>
#include <limits>

using namespace std;

namespace kasra {

void pad_matrix(vector<vector<int>>& matrix) {
    size_t i_size = matrix.size();
    size_t j_size = matrix[0].size();

    if (i_size > j_size) {
        for (auto& vec : matrix) {
            vec.resize(i_size, numeric_limits<int>::max());
        }
    } 
    else if (i_size < j_size) {
        while (matrix.size() < j_size) {
            matrix.push_back(vector<int>(j_size, numeric_limits<int>::max()));
        }
    }
}

void find_smallest(int& minval, const vector<vector<int>>& matrix,
                   const vector<int>& RowCover, const vector<int>& ColCover) {
    for (int r = 0; r < matrix.size(); r++) {
        for (int c = 0; c < matrix.size(); c++) {
            if (RowCover[r] == 0 && ColCover[c] == 0) {
                if (minval > matrix[r][c]) {
                    minval = matrix[r][c];
                }
            }
        }
    }
}

void col_finder(int c, int& r, const vector<vector<int>>& M) {
    r = -1;
    for (int i = 0; i < M.size(); i++) {
        if (M[i][c] == 1) {
            r = i;
        }
    }
}

void row_finder_2(int r, int& c, const vector<vector<int>>& M) {
    for (int j = 0; j < M.size(); j++) {
        if (M[r][j] == 2) {
            c = j;
        }
    }
}

void augmenting_path(vector<vector<int>>& path, int path_count, vector<vector<int>>& M) {
    for (int p = 0; p < path_count; p++) {
        if (M[path[p][0]][path[p][1]] == 1) {
            M[path[p][0]][path[p][1]] = 0;
        } 
        else {
            M[path[p][0]][path[p][1]] = 1;
        }
    }
}

bool star_in_row(int row, const vector<vector<int>>& M) {
    bool tmp = false;
    for (int c = 0; c < M.size(); c++) {
        if (M[row][c] == 1) {
            tmp = true;
        }
    }
    return tmp;
}

void row_finder(int row, int& col, const vector<vector<int>>& M) {
    col = -1;
    for (int c = 0; c < M.size(); c++) {
        if (M[row][c] == 1) {
            col = c;
        }
    }
}

void zero_finder(int& row, int& col, const vector<vector<int>>& matrix,
                 const vector<int>& RowCover, const vector<int>& ColCover) {
    int r = 0;
    int c = 0;
    int sz = matrix.size();
    bool done = false;
    row = -1;
    col = -1;

    while (!done) {
        c = 0;
        while (true) {
            if (matrix[r][c] == 0 && RowCover[r] == 0 && ColCover[c] == 0) {
                row = r;
                col = c;
                done = true;
            }
            c += 1;
            if (c >= sz || done) {
                break;
            }
        }
        r += 1;
        if (r >= sz) {
            done = true;
        }
    }
}

void f1(vector<vector<int>>& matrix, int& step) {
    for (auto& row : matrix) {
        auto smallest = *min_element(row.begin(), row.end());
        if (smallest > 0) {
            for (auto& n : row) {
                n -= smallest;
            }
        }
    }

    int sz = matrix.size();
    for (int j = 0; j < sz; j++) {
        int minval = numeric_limits<int>::max();
        for (int i = 0; i < sz; i++) {
            minval = min(minval, matrix[i][j]);
        }

        if (minval > 0) {
            for (int i = 0; i < sz; i++) {
                matrix[i][j] -= minval;
            }
        }
    }

    step = 2;
}

void f2(const vector<vector<int>>& matrix, vector<vector<int>>& M,
           vector<int>& RowCover, vector<int>& ColCover, int& step) {
    int sz = matrix.size();

    for (int r = 0; r < sz; r++) {
        for (int c = 0; c < sz; c++) {
            if (matrix[r][c] == 0) {
                if (RowCover[r] == 0 && ColCover[c] == 0) {
                    M[r][c] = 1;
                    RowCover[r] = 1;
                    ColCover[c] = 1;
                }
            }
        }
    }

    for (auto& n : RowCover) {
        n = 0;
    }

    for (auto& n : ColCover) {
        n = 0;
    }

    step = 3;
}

void f3(const vector<vector<int>>& M, vector<int>& ColCover, int& step) {
    int sz = M.size();
    int colcount = 0;

    for (int r = 0; r < sz; r++) {
        for (int c = 0; c < sz; c++) {
            if (M[r][c] == 1) {
                ColCover[c] = 1;
            }
        }
    }

    for (auto& n : ColCover) {
        if (n == 1) {
            colcount++;
        }
    }

    if (colcount >= sz) {
        step = 7;
    } 
    else {
        step = 4;
    }
}

void f4(const vector<vector<int>>& matrix, vector<vector<int>>& M,
           vector<int>& RowCover, vector<int>& ColCover, int& path_row_0, int& path_col_0,
           int& step) {
    int row = -1;
    int col = -1;
    bool done = false;

    while (!done) {
        zero_finder(row, col, matrix, RowCover, ColCover);

        if (row == -1) {
            done = true;
            step = 6;
        } 
        else {
            M[row][col] = 2;
            if (star_in_row(row, M)) {
                row_finder(row, col, M);
                RowCover[row] = 1;
                ColCover[col] = 0;
            } 
            else {
                done = true;
                step = 5;
                path_row_0 = row;
                path_col_0 = col;
            }
        }
    }
}

void f5(vector<vector<int>>& path, int path_row_0, int path_col_0,
           vector<vector<int>>& M, vector<int>& RowCover, vector<int>& ColCover,
           int& step) {
    int r = -1;
    int c = -1;
    int path_count = 1;

    path[path_count - 1][0] = path_row_0;
    path[path_count - 1][1] = path_col_0;

    bool done = false;
    while (!done) {
        col_finder(path[path_count - 1][1], r, M);
        if (r > -1) {
            path_count += 1;
            path[path_count - 1][0] = r;
            path[path_count - 1][1] = path[path_count - 2][1];
        } 
        else {
            done = true;
        }

        if (!done) {
            row_finder_2(path[path_count - 1][0], c, M);
            path_count += 1;
            path[path_count - 1][0] = path[path_count - 2][0];
            path[path_count - 1][1] = c;
        }
    }

    augmenting_path(path, path_count, M);

    for (auto& n : RowCover) {
        n = 0;
    }

    for (auto& n : ColCover) {
        n = 0;
    }

    for (auto& row : M) {
        for (auto& val : row) {
            if (val == 2) {
                val = 0;
            }
        }
    }

    step = 3;
}

void f6(vector<vector<int>>& matrix, const vector<int>& RowCover,
           const vector<int>& ColCover, int& step) {
    int minval = numeric_limits<int>::max();
    find_smallest(minval, matrix, RowCover, ColCover);

    int sz = matrix.size();
    for (int r = 0; r < sz; r++) {
        for (int c = 0; c < sz; c++) {
            if (RowCover[r] == 1) {
                matrix[r][c] += minval;
            }
            if (ColCover[c] == 0) {
                matrix[r][c] -= minval;
            }
        }
    }

    step = 4;
}

int solve(const vector<vector<int>>& original, bool allow_negatives = true) {
    vector<vector<int>> matrix(original.size(), vector<int>(original.begin()->size()));

    auto it = original.begin();
    for (auto& vec : matrix) {
        copy(it->begin(), it->end(), vec.begin());
        it = next(it);
    }

    pad_matrix(matrix);
    size_t sz = matrix.size();

    vector<vector<int>> M(sz, vector<int>(sz, 0));

    vector<int> RowCover(sz, 0);
    vector<int> ColCover(sz, 0);

    int path_row_0, path_col_0;

    vector<vector<int>> path(sz + 1, vector<int>(2, 0));

    bool done = false;
    int step = 1;

    while (!done) {
        switch (step) {
        case 1:
            f1(matrix, step);
            break;
        case 2:
            f2(matrix, M, RowCover, ColCover, step);
            break;
        case 3:
            f3(M, ColCover, step);
            break;
        case 4:
            f4(matrix, M, RowCover, ColCover, path_row_0, path_col_0, step);
            break;
        case 5:
            f5(path, path_row_0, path_col_0, M, RowCover, ColCover, step);
            break;
        case 6:
            f6(matrix, RowCover, ColCover, step);
            break;
        case 7:
            for (auto& vec : M) {
                vec.resize(original.begin()->size());
            }
            M.resize(original.size());
            done = true;
            break;
        default:
            done = true;
            break;
        }
    }

    int res = 0;
    for (int j = 0; j < original.begin()->size(); j++) {
        for (int i = 0; i < original.size(); i++) {
            if (M[i][j]) {
                auto it1 = original.begin();
                advance(it1, i);
                auto it2 = it1->begin();
                advance(it2, j);
                res += *it2;
                continue;
            }
        }
    }

    return res;
}

} 

int main() {

    using namespace kasra;

    int number_of_employees, temp;
    cin >> number_of_employees;

    vector<vector<int>> salary;

    for (int i = 0; i < number_of_employees; i++) {
        vector<int> temp_vec;

        for (int j = 0; j < number_of_employees; j++) {
            cin >> temp;
            temp_vec.push_back(temp);
        }
        salary.push_back(temp_vec);
    }

    int res = solve(salary);
    cout << res << endl;

}