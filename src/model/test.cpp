#include <gtest/gtest.h>

#include "data.h"
#include "parser.h"
#include "transformer.h"

TEST(Testing_parser, parsing_test_1) {
  s21::Data *our_data = s21::Parser::obtainData("view/objects/cube.obj");

  vector<array<double, 3>> correct_numbers = {
      {-0.5, -0.5, -0.5}, {-0.5, -0.5, 0.5}, {-0.5, 0.5, -0.5},
      {-0.5, 0.5, 0.5},   {0.5, -0.5, -0.5}, {0.5, -0.5, 0.5},
      {0.5, 0.5, -0.5},   {0.5, 0.5, 0.5}};

  for (int i = 0; i < correct_numbers.size(); i++) {
    for (int j = 0; j < correct_numbers.at(i).size(); j++) {
      EXPECT_DOUBLE_EQ(our_data->getVertices()->at(i).at(j),
                       correct_numbers.at(i).at(j));
    }
  }
}

TEST(Testing_parser, parsing_test_2) {
  s21::Data *our_data = s21::Parser::obtainData("view/objects/cube.obj");

  EXPECT_EQ(our_data->getVertices()->size(), 8);
}

TEST(Testing_parser, parsing_test_3) {
  s21::Data *our_data = s21::Parser::obtainData("view/objects/cube.obj");

  EXPECT_EQ(our_data->getFacets()->size(), 4);
}

TEST(Testing_parser, parsing_test_4) {
  s21::Data *our_data = s21::Parser::obtainData("view/objects/cube.obj");

  vector<vector<int>> correct_numbers = {
      {1, 2, 4, 3}, {1, 3, 7, 5}, {7, 5, 6, 8}, {6, 2, 4, 8}};

  for (int i = 0; i < correct_numbers.size(); i++) {
    for (int j = 0; j < correct_numbers.at(i).size(); j++) {
      EXPECT_EQ(our_data->getFacets()->at(i).at(j),
                correct_numbers.at(i).at(j));
    }
  }
}

TEST(Testing_parser, transorm_scale_test_1) {
  s21::Data *our_data = s21::Parser::obtainData("view/objects/cube.obj");
  s21::Transformer::scale(our_data, 2);

  vector<array<double, 3>> correct_numbers = {
      {-1, -1, -1}, {-1, -1, 1}, {-1, 1, -1}, {-1, 1, 1},
      {1, -1, -1},  {1, -1, 1},  {1, 1, -1},  {1, 1, 1}};

  for (int i = 0; i < correct_numbers.size(); i++) {
    for (int j = 0; j < correct_numbers.at(i).size(); j++) {
      EXPECT_EQ(our_data->getVertices()->at(i).at(j),
                correct_numbers.at(i).at(j));
    }
  }
}
TEST(Testing_parser, transorm_rotate_test_1) {
  s21::Data *our_data = s21::Parser::obtainData("view/objects/cube.obj");
  s21::Transformer::rotate(our_data, 150, s21::kX);

  vector<array<double, 3>> correct_numbers = {
      {-0.5, 0.683013, 0.183013},  {-0.5, 0.183013, -0.683013},
      {-0.5, -0.183013, 0.683013}, {-0.5, -0.683013, -0.183013},
      {0.5, 0.683013, 0.183013},   {0.5, 0.183013, -0.683013},
      {0.5, -0.183013, 0.683013},  {0.5, -0.683013, -0.183013}};

  for (int i = 0; i < correct_numbers.size(); i++) {
    for (int j = 0; j < correct_numbers.at(i).size(); j++) {
      EXPECT_NEAR(our_data->getVertices()->at(i).at(j),
                  correct_numbers.at(i).at(j), 0.000001);
    }
  }
}

TEST(Testing_parser, transorm_rotate_test_2) {
  s21::Data *our_data = s21::Parser::obtainData("view/objects/cube.obj");
  s21::Transformer::rotate(our_data, 125, s21::kY);

  vector<array<double, 3>> correct_numbers = {
      {-0.123, -0.5, 0.696}, {0.696, -0.5, 0.123},   {-0.123, 0.5, 0.696},
      {0.696, 0.5, 0.123},   {-0.696, -0.5, -0.123}, {0.123, -0.5, -0.696},
      {-0.696, 0.5, -0.123}, {0.123, 0.5, -0.696}};

  for (int i = 0; i < correct_numbers.size(); i++) {
    for (int j = 0; j < correct_numbers.at(i).size(); j++) {
      EXPECT_NEAR(our_data->getVertices()->at(i).at(j),
                  correct_numbers.at(i).at(j), 0.001);
    }
  }
}

TEST(Testing_parser, transorm_rotate_test_3) {
  s21::Data *our_data = s21::Parser::obtainData("view/objects/cube.obj");
  s21::Transformer::rotate(our_data, 270, s21::kZ);

  vector<array<double, 3>> correct_numbers = {
      {-0.5, 0.5, -0.5}, {-0.5, 0.5, 0.5},   {0.5, 0.5, -0.5},
      {0.5, 0.5, 0.5},   {-0.5, -0.5, -0.5}, {-0.5, -0.5, 0.5},
      {0.5, -0.5, -0.5}, {0.5, -0.5, 0.5}};

  for (int i = 0; i < correct_numbers.size(); i++) {
    for (int j = 0; j < correct_numbers.at(i).size(); j++) {
      EXPECT_NEAR(our_data->getVertices()->at(i).at(j),
                  correct_numbers.at(i).at(j), 0.001);
    }
  }
}

TEST(Testing_parser, transorm_move_test_1) {
  s21::Data *our_data = s21::Parser::obtainData("view/objects/cube.obj");
  s21::Transformer::move(our_data, 3, s21::kX);

  vector<array<double, 3>> correct_numbers = {
      {2.5, -0.5, -0.5}, {2.5, -0.5, 0.5}, {2.5, 0.5, -0.5}, {2.5, 0.5, 0.5},
      {3.5, -0.5, -0.5}, {3.5, -0.5, 0.5}, {3.5, 0.5, -0.5}, {3.5, 0.5, 0.5}};

  for (int i = 0; i < correct_numbers.size(); i++) {
    for (int j = 0; j < correct_numbers.at(i).size(); j++) {
      EXPECT_NEAR(our_data->getVertices()->at(i).at(j),
                  correct_numbers.at(i).at(j), 0.001);
    }
  }
}

TEST(Testing_parser, transorm_move_test_2) {
  s21::Data *our_data = s21::Parser::obtainData("view/objects/cube.obj");
  s21::Transformer::move(our_data, -3, s21::kY);

  vector<array<double, 3>> correct_numbers = {
      {-0.5, -3.5, -0.5}, {-0.5, -3.5, 0.5}, {-0.5, -2.5, -0.5},
      {-0.5, -2.5, 0.5},  {0.5, -3.5, -0.5}, {0.5, -3.5, 0.5},
      {0.5, -2.5, -0.5},  {0.5, -2.5, 0.5}};

  for (int i = 0; i < correct_numbers.size(); i++) {
    for (int j = 0; j < correct_numbers.at(i).size(); j++) {
      EXPECT_NEAR(our_data->getVertices()->at(i).at(j),
                  correct_numbers.at(i).at(j), 0.001);
    }
  }
}

TEST(Testing_parser, transorm_move_test_3) {
  s21::Data *our_data = s21::Parser::obtainData("view/objects/cube.obj");
  s21::Transformer::move(our_data, 13, s21::kZ);

  vector<array<double, 3>> correct_numbers = {
      {-0.5, -0.5, 12.5}, {-0.5, -0.5, 13.5}, {-0.5, 0.5, 12.5},
      {-0.5, 0.5, 13.5},  {0.5, -0.5, 12.5},  {0.5, -0.5, 13.5},
      {0.5, 0.5, 12.5},   {0.5, 0.5, 13.5}};

  for (int i = 0; i < correct_numbers.size(); i++) {
    for (int j = 0; j < correct_numbers.at(i).size(); j++) {
      EXPECT_NEAR(our_data->getVertices()->at(i).at(j),
                  correct_numbers.at(i).at(j), 0.001);
    }
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
