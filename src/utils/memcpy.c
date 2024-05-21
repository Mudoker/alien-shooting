void *my_memcpy(void *dest, const void *src, int n) {
    char *dp = dest;
    const char *sp = src;
    while (n--) {
        *dp++ = *sp++;
    }
    return dest;
}
