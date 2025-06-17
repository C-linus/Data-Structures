#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdlib>

#define DEFAULT_SPARSITY_THRESHOLD 0.5f

struct Coordinates {
    unsigned int row;
    unsigned int col;
    int value;
};

class SparseMatrix {
private:
    unsigned int m, n;
    std::vector<Coordinates> coordinates;

    SparseMatrix(unsigned int rows, unsigned int cols)
        : m(rows), n(cols) {}

    bool isSparse(float threshold) const {
        return static_cast<float>(coordinates.size()) / (m * n) < threshold;
    }

    bool isValidCoordinate(unsigned int row, unsigned int col, int value) const {
        if (value == 0) {
            std::cout << "\nValue cannot be zero in a sparse matrix.\n";
            return false;
        }

        if (row >= m || col >= n) {
            std::cout << "\nInvalid row/column index. Must be within matrix bounds.\n";
            return false;
        }

        for (const auto& c : coordinates) {
            if (c.row == row && c.col == col) {
                std::cout << "\nDuplicate position (" << row << "," << col << ") is not allowed.\n";
                return false;
            }
        }

        return true;
    }

    void sortCoordinates() {
        for (size_t i = 0; i < coordinates.size() - 1; ++i) {
            for (size_t j = 0; j < coordinates.size() - i - 1; ++j) {
                if (coordinates[j].row > coordinates[j + 1].row ||
                    (coordinates[j].row == coordinates[j + 1].row && coordinates[j].col > coordinates[j + 1].col)) {
                    std::swap(coordinates[j], coordinates[j + 1]);
                }
            }
        }
    }

public:



    SparseMatrix() {
        do {
            std::cout << "Enter the Dimension(m): ";
            std::cin >> m;
        } while (m == 0);

        do {
            std::cout << "Enter the Dimension(n): ";
            std::cin >> n;
        } while (n == 0);

        unsigned int count;
        do {
            std::cout << "Enter number of non-zero elements: ";
            std::cin >> count;
            coordinates.reserve(count);
            if (!isSparse(DEFAULT_SPARSITY_THRESHOLD)) {
                std::cout << "Sparsity Error: (Minimum sparsity should be " << DEFAULT_SPARSITY_THRESHOLD * 100 << "%)\n";
            }
        } while (!isSparse(DEFAULT_SPARSITY_THRESHOLD));

        std::cout << "Enter all non-zero elements:\n";
        for (unsigned int i = 0; i < count; ++i) {
            while (true) {
                unsigned int row, col;
                int value;
                std::cout << "Enter the row of element-" << i + 1 << ": ";
                std::cin >> row;
                std::cout << "Enter the col of element-" << i + 1 << ": ";
                std::cin >> col;
                std::cout << "Enter the value of element-" << i + 1 << ": ";
                std::cin >> value;

                if (isValidCoordinate(row, col, value)) {
                    coordinates.push_back({row, col, value});
                    break;
                } else {
                    std::cout << "Invalid entry. Please re-enter element-" << i + 1 << ".\n";
                }
            }
        }

        sortCoordinates();
    }

    void display() const {
        size_t k = 0;
        for (unsigned int i = 0; i < m; ++i) {
            for (unsigned int j = 0; j < n; ++j) {
                if (k < coordinates.size() && coordinates[k].row == i && coordinates[k].col == j) {
                    std::cout << std::setw(6) << coordinates[k++].value;
                } else {
                    std::cout << std::setw(6) << 0;
                }
            }
            std::cout << '\n';
        }
    }

    SparseMatrix add(const SparseMatrix& other) const {
        if (m != other.m || n != other.n) {
            std::cerr << "Addition Error: Matrices with different dimensions can't be added!\n";
            std::exit(EXIT_FAILURE);
        }

        SparseMatrix result(m, n); 

        size_t i = 0, j = 0;
        while (i < coordinates.size() && j < other.coordinates.size()) {
            const Coordinates& a = coordinates[i];
            const Coordinates& b = other.coordinates[j];

            if ((a.row < b.row) || (a.row == b.row && a.col < b.col)) {
                result.coordinates.push_back(a);
                i++;
            } else if ((a.row > b.row) || (a.row == b.row && a.col > b.col)) {
                result.coordinates.push_back(b);
                j++;
            } else {
                int sum = a.value + b.value;
                if (sum != 0) {
                    result.coordinates.push_back({ a.row, a.col, sum });
                }
                i++;
                j++;
            }
        }

        // Append remaining entries
        while (i < coordinates.size()) result.coordinates.push_back(coordinates[i++]);
        while (j < other.coordinates.size()) result.coordinates.push_back(other.coordinates[j++]);

        return result;
    }


    friend int main();
};

int main() {
    SparseMatrix matrix1;
    matrix1.display();

    SparseMatrix matrix2;
    matrix2.display();

    SparseMatrix result = matrix1.add(matrix2);
    std::cout << "\nResult:\n";
    result.display();

    return EXIT_SUCCESS;
}
