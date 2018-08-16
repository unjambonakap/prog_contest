/*
 * Invoke for NT test.
 *   outcome = success
 *   exit_code = 0
 *   memory_consumed \in [10M..12M]
 */
const int size = 10 * 1024 * 1024;
char a[size];

int main() {
    for (int i = 0; i < size; i++) {
        a[i] = '\001';
    }

    int sum = 0;
    for (int j = 0; j < size; j++) {
        sum += a[j];
    }
    return sum == 0;
}
