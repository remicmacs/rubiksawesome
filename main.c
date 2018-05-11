#include "src/view/view.h"

int main(int argc, char **argv) {
  setWindow();

  rubikview mainView = generateView();

  while (1) {
    update(&(mainView.mainCamera), mainView.cubes);
  }

  closeWindow();
  return 0;
}
