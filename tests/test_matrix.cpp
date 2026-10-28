#include <gtest/gtest.h>

#include <stdexcept>

#include "matrix.h"

TEST(MatrixTest, CreateMatrix) {
  Matrix A = create_matrix(3, 4);
  EXPECT_EQ(A.rows, 3);
  EXPECT_EQ(A.cols, 4);
  EXPECT_NE(A.data, nullptr);
  free_matrix(A);
}

TEST(MatrixTest, VStack_SameColumns) {
  Matrix A = create_matrix(2, 3);
  Matrix B = create_matrix(3, 3);

  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 3; j++) A.data[i][j] = i * 3 + j + 1;

  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++) B.data[i][j] = (i + 2) * 3 + j + 1;

  Matrix C = matrix_vstack(A, B);

  EXPECT_EQ(C.rows, 5);
  EXPECT_EQ(C.cols, 3);
  EXPECT_DOUBLE_EQ(C.data[0][0], 1.0);
  EXPECT_DOUBLE_EQ(C.data[4][2], 15.0);

  free_matrix(A);
  free_matrix(B);
  free_matrix(C);
}

TEST(MatrixTest, VStack_DifferentColumns_Throws) {
  Matrix A = create_matrix(2, 3);
  Matrix B = create_matrix(2, 4);

  EXPECT_THROW(matrix_vstack(A, B), std::invalid_argument);

  free_matrix(A);
  free_matrix(B);
}

TEST(MatrixTest, Addition) {
  Matrix A = create_matrix(2, 2);
  Matrix B = create_matrix(2, 2);

  A.data[0][0] = 1;
  A.data[0][1] = 2;
  A.data[1][0] = 3;
  A.data[1][1] = 4;
  B.data[0][0] = 5;
  B.data[0][1] = 6;
  B.data[1][0] = 7;
  B.data[1][1] = 8;

  Matrix C = matrix_add(A, B);

  EXPECT_DOUBLE_EQ(C.data[0][0], 6.0);
  EXPECT_DOUBLE_EQ(C.data[1][1], 12.0);

  free_matrix(A);
  free_matrix(B);
  free_matrix(C);
}

TEST(MatrixTest, Multiplication) {
  Matrix A = create_matrix(2, 2);
  Matrix B = create_matrix(2, 2);

  A.data[0][0] = 1;
  A.data[0][1] = 2;
  A.data[1][0] = 3;
  A.data[1][1] = 4;
  B.data[0][0] = 5;
  B.data[0][1] = 6;
  B.data[1][0] = 7;
  B.data[1][1] = 8;

  Matrix C = matrix_multiply(A, B);

  EXPECT_DOUBLE_EQ(C.data[0][0], 19.0);
  EXPECT_DOUBLE_EQ(C.data[1][1], 50.0);

  free_matrix(A);
  free_matrix(B);
  free_matrix(C);
}