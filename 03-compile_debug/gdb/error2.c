void func(int i) {
    func(i+1);
}
int main() {
    func(1);
}