#include "tests.h"

#include <conio.h>

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  auto result = RUN_ALL_TESTS();

  if (result)
  {
	  _getch();
  }

  return result;
}


