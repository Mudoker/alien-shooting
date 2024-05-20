#include "../../header/game/game_controller.h"
#include "../../assets/games/spaceship/blader.h"
#include "../../assets/games/bullet/bullet_lv1.h"
#include "../../assets/games/background.h"
#include "../../assets/games/stages.h"
#include "../../assets/games/health.h"

void init_controller(GameController *game_controller)
{
    // game_controller->stage_level = 1;
    // init_background(game_controller);
    init_spaceship(game_controller);
    //init_bullet(game_controller);
    init_stages(game_controller);
}


// Initialize the spaceship object
void init_spaceship(GameController *game_controller)
{
    Spaceship your_spaceship;
    // Spaceship's size
    your_spaceship.size.width = 124;
    your_spaceship.size.height = 128;

    // Initial position of the spaceship
    // your_spaceship.position.x = (SCREEN_WIDTH - your_spaceship.size.width) / 2;
    // your_spaceship.position.y = SCREEN_HEIGHT - your_spaceship.size.height;

    // Image of the spaceship
    your_spaceship.sprite = epd_bitmap_spaceship_allArray[0];
    game_controller->spaceship = your_spaceship;

    // draw_spaceship(game_controller);
}

void init_bullet(GameController *game_controller)
{
    Bullet bullet;
    bullet.position.x = game_controller->spaceship.position.x + (game_controller->spaceship.size.width - 12) / 2;
    bullet.position.y = game_controller->spaceship.position.y - 48 - 20;
    bullet.sprite = epd_bitmap_bullet_allArray[0];
    game_controller->spaceship.bullet = bullet;
    draw_bullet(game_controller);
}

void init_stages(GameController *game_controller)
{
    for (int i = 0; i < 9; i++) {
        Stage stage;
        stage.level = i + 1;
        strcpy(stage.name, "Stage ");
        strcat(stage.name, int_to_string(i + 1));
        game_controller->stages[i] = stage;
    }
    game_controller->stage_level = 1;
    // draw_stages(game_controller);
}

void init_game(GameController *game_controller)
{
    game_controller->spaceship.health = 100;
    game_controller->spaceship.position.x = (SCREEN_WIDTH - game_controller->spaceship.size.width) / 2;
    game_controller->spaceship.position.y = SCREEN_HEIGHT - game_controller->spaceship.size.height;
}


// Draw the bullet on the screen
void draw_bullet(GameController *game_controller)
{
    draw_image_object(game_controller->spaceship.bullet.position.x, game_controller->spaceship.bullet.position.y, 12, 48, game_controller->spaceship.bullet.sprite, epd_bitmap_background_allArray[0]);
}

void draw_spaceship(GameController *game_controller)
{
    draw_image_object(game_controller->spaceship.position.x, game_controller->spaceship.position.y, game_controller->spaceship.size.width, game_controller->spaceship.size.height, game_controller->spaceship.sprite, epd_bitmap_background_allArray[0]);
}


void draw_stages(GameController *game_controller)
{
    for (int i = 0; i < 9; i++) {
        if (game_controller->stages[i].level == game_controller->stage_level) {
            draw_button(SCREEN_WIDTH / 2 - 150, 100 + i * 80, 300, 40, game_controller->stages[i].name, 1);
        } else {
            draw_button(SCREEN_WIDTH / 2 - 150, 100 + i * 80, 300, 40, game_controller->stages[i].name, 0);
        }
    }
}

void draw_background()
{
    draw_image_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, epd_bitmap_background_allArray[0]);
}

void draw_health_bar(GameController *game_controller)
{
    draw_image_object(0, SCREEN_HEIGHT - 80, 448, 79, epd_bitmap_health_bar_allArray[0], epd_bitmap_background_allArray[0]);
    
    // Replace epd_bitmap_health_bar_allArray[0] that have "0x002a2e47" with red color
    for (int i = 0; i < 448 * 79; i++) {
        if (epd_bitmap_health_bar_allArray[0][i] >= 0x002a2e40 && epd_bitmap_health_bar_allArray[0][i] <= 0x002a2e49 ) {
            draw_pixelARGB32(i % 448, i / 448 + SCREEN_HEIGHT - 80, 0x00AA0000);
        }
    }

}



void move_spaceship(GameController *game_controller, int x_dir, int y_dir)
{
    Spaceship *spaceship = &game_controller->spaceship;
    clear_image(spaceship->position.x, spaceship->position.y, spaceship->size.width, spaceship->size.height, epd_bitmap_background_allArray[0]);

    // Now you can modify the bitmap data
    // repl_bitmap_background[spaceship->position.y * SCREEN_WIDTH + spaceship->position.x] = 0;

    // draw_image(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,epd_bitmap_background_allArray[0]);

    if (spaceship->position.x + x_dir * STEP >= 0 &&
        spaceship->position.x + x_dir * STEP <= SCREEN_WIDTH - spaceship->size.width)
    {
        spaceship->position.x += x_dir * STEP;
    }

    if (spaceship->position.y + y_dir * STEP >= 0 &&
        spaceship->position.y + y_dir * STEP <= SCREEN_HEIGHT - spaceship->size.height)
    {
        spaceship->position.y += y_dir * STEP;
    }
    draw_spaceship(game_controller);
}

void move_bullet(GameController *game_controller, int x_dir, int y_dir)
{
    Spaceship *spaceship = &game_controller->spaceship;
    Bullet *bullet = &spaceship->bullet;
    clear_image(bullet->position.x, bullet->position.y, 12, 48, epd_bitmap_background_allArray[0]);
    // draw_image(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,epd_bitmap_background_allArray[0]);

    if (bullet->position.x + x_dir * 48 >= 0 &&
        bullet->position.x + x_dir * 48 <= SCREEN_WIDTH - 12)
    {
        bullet->position.x += x_dir * 48;
    }

    if (bullet->position.y + y_dir * 48 >= 0 &&
        bullet->position.y + y_dir * 48 <= SCREEN_HEIGHT - 48)
    {
        bullet->position.y += y_dir * 48;
    }

    draw_bullet(game_controller);
    wait_msec(8000);
}


void change_stage(GameController *game_controller, int diff)
{
    draw_button(SCREEN_WIDTH / 2 - 150, 100 + (game_controller->stage_level - 1) * 80, 300, 40, game_controller->stages[game_controller->stage_level - 1].name, 0);
    game_controller->stage_level += diff;
    if (game_controller->stage_level < 1)
    {
        game_controller->stage_level = 9;
    }
    else if (game_controller->stage_level > 9)
    {
        game_controller->stage_level = 1;
    }
    draw_button(SCREEN_WIDTH / 2 - 150, 100 + (game_controller->stage_level - 1) * 80, 300, 40, game_controller->stages[game_controller->stage_level - 1].name, 1);
}