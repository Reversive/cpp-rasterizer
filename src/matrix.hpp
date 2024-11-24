#pragma once

#include <initializer_list>
#include <ostream>
#include <stdexcept>
#include <vector>

template <typename T> class Matrix {
public:
  Matrix() = delete;
  Matrix(int rows, int cols, const std::initializer_list<T> &values)
      : rows(rows), cols(cols), elements(values) {
    if (rows < 0 || cols < 0) {
      throw std::invalid_argument("Matrix dimensions must be positive");
    }
    if (rows * cols != values.size()) {
      throw std::invalid_argument("List size does not match Matrix dimensions");
    }
  }

  T &at(int row, int col) {
    check_bounds(row, col);
    return this->elements[(this->cols * row) + col];
  }

  const T &at(int row, int col) const {
    check_bounds(row, col);
    return this->elements[(this->cols * row) + col];
  }

  T &operator()(int row, int col) { return at(row, col); }
  const T &operator()(int row, int col) const { return at(row, col); }

  Matrix operator+(const Matrix &other) {
    if (this->rows != other.rows || this->cols != other.cols) {
      throw std::invalid_argument("Matrix dimensions must match to sum");
    }

    for (int y = 0; y < this->rows; ++y) {
      for (int x = 0; x < this->cols; ++x) {
        this->at(x, y) += other.at(x, y);
      }
    }

    return this;
  }

  Matrix operator*(const Matrix &other) {
    if (this->cols != other.rows) {
      throw std::invalid_argument(
          "The number of columns of the first Matrix must match the number of "
          "rows of the second Matrix");
    }
    Matrix result{this->rows, other.cols};
    for (int i = 0; i < this->rows; ++i) {
      for (int j = 0; j < other.cols; ++j) {
        T sum{};
        for (int k = 0; k < this->cols; ++k) {
          sum += at(i, k) * other.at(k, j);
        }
        result.at(i, j) = sum;
      }
    }

    return result;
  }

  friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
    for (int i = 0; i < matrix.rows; ++i) {
      os << "[";
      for (int j = 0; j < matrix.cols; ++j) {
        os << matrix.at(i, j);
        if (j < matrix.cols - 1)
          os << " ";
      }
      os << "]\n";
    }
    return os;
  }

private:
  void check_bounds(int row, int col) const {
    if (row < 0 || row >= this->rows || col < 0 || col >= this->cols) {
      throw std::out_of_range("Out of bounds Matrix access");
    }
  }
  Matrix(int rows, int cols) : rows(rows), cols(cols), elements(rows * cols) {}
  int rows, cols;
  std::vector<T> elements;
};
