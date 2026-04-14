struct add {
  int x, y;
  int operator()(int x, int y) { return x + y; }
};

int main() {

  add a;
  int sum = a(4, 5);
  return 0;
}