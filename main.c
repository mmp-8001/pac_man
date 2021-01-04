#include "common/pac_common.h"
#include "objects/pacman.h"

int main(int argc, char *argv[]) {
    if (!app_init()) {
        printf("Failed to initialize the app!\n");
        return 1;
    }
    printf("we create window");
    PACMAN pacMan;
    PACMAN_init(&pacMan, 10, 10);
    return 0;
}