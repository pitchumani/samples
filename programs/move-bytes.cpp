
// "number" of bytes located at the src address location should
// be at the dest address location after executing moveBytes
void moveBytes(char * src, char * dest, int number)
{
    if (src == dest) return;
    if (src == nullptr) return;
    if (dest == nullptr) return;

    bool reverse = false;
    if (src < dest) {
        if ((src + number) >= dest) {
            // there is a overlap, copy from the rear
            reverse = true;
        }
    } else if (src > dest) {
        if ((dest + number) >= src) {
            // there is a overlap
            reverse = true;
        }
    }

    if (reverse == false) {
        for (int idx = 0; idx < number; ++idx) {
            *(dest + idx) = *(src + idx);
        }
    } else {
        for (int idx = number - 1; idx >= 0; --idx) {
            *(dest + idx) = *(src + idx);
        }
    }

}
