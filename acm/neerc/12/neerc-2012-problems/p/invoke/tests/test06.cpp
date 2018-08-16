/*
 * Invoke for NT test.
 *   outcome = crash
 */
char a[1];

int main() {
    for (int i = 0; i + 1; i++) a[i] = '!';
    return 0;
}
