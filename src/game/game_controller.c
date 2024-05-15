#include "../../header/game/game_controller.h"
#include "../../assets/games/spaceship/blader.h"
#include "../../assets/games/bullet/bullet_lv1.h"
#include "../../assets/games/background.h"
#include "../../assets/games/alient/alient_1.h"
#include "../utils/randomNum.h"
#include "../../header/uart.h"



void init_background(GameController *game_controller) {
    draw_image_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, epd_bitmap_background_allArray[0]);
}

// Initialize the spaceship object
void init_spaceship(GameController *game_controller) {
    Spaceship your_spaceship;
    // init_background(game_controller);

    // Spaceship's size
    your_spaceship.size.width = 124;
    your_spaceship.size.height = 128;

    // Initial position of the spaceship
    your_spaceship.position.x = (SCREEN_WIDTH - your_spaceship.size.width) / 2;
    your_spaceship.position.y = SCREEN_HEIGHT - your_spaceship.size.height;

    // Image of the spaceship
    your_spaceship.sprite = epd_bitmap_spaceship_allArray[0];
    game_controller->spaceship = your_spaceship;

    draw_spaceship(game_controller);
    // draw_alien(game_controller);
}

void init_bullet(GameController *game_controller) {
    Bullet bullet;
    bullet.position.x = game_controller->spaceship.position.x + (game_controller->spaceship.size.width - 12) / 2;
    bullet.position.y = game_controller->spaceship.position.y - 48 - 20;
    bullet.sprite = epd_bitmap_bullet_allArray[0];
    game_controller->spaceship.bullet = bullet;
    draw_bullet(game_controller);
}

void init_alien(GameController *game_controller) {
    init_seed();
    Alien alien;
    alien.position.x = randomNum() % 450;
    alien.position.y = randomNum() % 450;
    uart_puts("alien x: ");
    uart_puts(itoa(alien.position.x));
    uart_puts("alien y: ");
    uart_puts(itoa(alien.position.y));
    alien.sprite = epd_bitmap_alient_allArray[0];
    game_controller->alien = alien;
    draw_alien(game_controller);
}
// Draw the spaceship on the screen
void draw_spaceship(GameController *game_controller) {
    // draw_image_object(game_controller->spaceship.position.x, game_controller->spaceship.position.y, game_controller->spaceship.size.width, game_controller->spaceship.size.height, game_controller->spaceship.sprite, epd_bitmap_background_allArray[0]);
    draw_image_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, epd_bitmap_background_allArray[0]);
}

void draw_alien(GameController *game_controller) {
    draw_image_object(game_controller->alien.position.x, game_controller->alien.position.y, 130, 109,epd_bitmap_alient_allArray[0], epd_bitmap_background_allArray[0]);
}
// Draw the bullet on the screen
void draw_bullet(GameController *game_controller) {
    draw_image_object(game_controller->spaceship.bullet.position.x, game_controller->spaceship.bullet.position.y, 12, 48, game_controller->spaceship.bullet.sprite, epd_bitmap_background_allArray[0]);
}

void move_spaceship(GameController *game_controller, int x_dir, int y_dir) {
    Spaceship *spaceship = &game_controller->spaceship;
    clear_image(spaceship->position.x, spaceship->position.y, spaceship->size.width, spaceship->size.height, epd_bitmap_background_allArray[0]);

    // Now you can modify the bitmap data
    //repl_bitmap_background[spaceship->position.y * SCREEN_WIDTH + spaceship->position.x] = 0;

    //draw_image(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,epd_bitmap_background_allArray[0]);

    if (spaceship->position.x + x_dir * STEP >= 0 &&
        spaceship->position.x + x_dir * STEP <= SCREEN_WIDTH - spaceship->size.width) {
        spaceship->position.x += x_dir * STEP;
    }

    if (spaceship->position.y + y_dir * STEP >= 0 &&
        spaceship->position.y + y_dir * STEP <= SCREEN_HEIGHT - spaceship->size.height) {
        spaceship->position.y += y_dir * STEP;
    }
    draw_spaceship(game_controller);
}

void move_bullet(GameController *game_controller, int x_dir, int y_dir) {
    Spaceship *spaceship = &game_controller->spaceship;
    Bullet *bullet = &spaceship->bullet;
    clear_image(bullet->position.x, bullet->position.y, 12, 48, epd_bitmap_background_allArray[0]);
    //draw_image(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,epd_bitmap_background_allArray[0]);

    if (bullet->position.x + x_dir * 48 >= 0 &&
        bullet->position.x + x_dir * 48 <= SCREEN_WIDTH - 12) {
        bullet->position.x += x_dir * 48;
    }

    if (bullet->position.y + y_dir * 48 >= 0 &&
        bullet->position.y + y_dir * 48 <= SCREEN_HEIGHT - 48) {
        bullet->position.y += y_dir * 48;
    }

    draw_bullet(game_controller);
    wait_msec(8000);
}

void send_serial(char *message) {
    while (*message) {
        uart_puts(*message++); // uart_write is a hypothetical function to send a character over UART
    }
}

char* itoa(int num) {
    static char str[12];  // Large enough for an integer, includes space for negative sign and null terminator
    int i = 0;
    int isNegative = 0;

    // Handle 0 explicitly, otherwise, an empty string is printed for 0
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // In standard itoa(), negative numbers are handled only with base 10
    // Otherwise, numbers are considered unsigned
    if (num < 0) {
        isNegative = 1;
        num = -num;
    }

    // Process individual digits
    while (num != 0) {
        int rem = num % 10;
        str[i++] = rem + '0';  // Convert int to char
        num = num / 10;
    }

    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';

    str[i] = '\0';  // Append string terminator

    // Reverse the string
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }

    return str;
}