#include "BaseObject.h"
#include "Bullet.h"
#include "CommonFunction.h"
#include "Enemy.h"
#include "map.h"
#include "stdafx.h"
#include "Timer.h"
#include "Player.h"
#include "Text.h"

BaseObject game_background, game_menu_screen;
TTF_Font* font = NULL;

bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0)
    {
        return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    game_window = SDL_CreateWindow(
        "Contro",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);

    if (game_window == NULL)
    {
        success = false;
    }
    else
    {
        game_screen = SDL_CreateRenderer(game_window, -1, SDL_RENDERER_ACCELERATED);
        if (game_screen == NULL)
        {
            success = false;
        }
        else
        {
            SDL_SetRenderDrawColor(game_screen, 255, 255, 255, 255);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags)) 
            {
                success = false;
            }
        }

        if (TTF_Init() == -1)
        {
            success = false;
        }

        font = TTF_OpenFont("font//font3.ttf", 20);
        if (font == NULL)
        {
            success = false;
        }
    }
    return success;
}

bool loadBackground()
{
    bool ret = game_background.LoadImg("image//universe1.png", game_screen);
    if (ret == false)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void close()
{
    game_background.Free();

    SDL_DestroyRenderer(game_screen);
    game_screen = NULL;

    SDL_DestroyWindow(game_window);
    game_window = NULL;

    IMG_Quit();
    SDL_Quit();
}

std::vector<Enemy*> MakeEnemy()
{
    std::vector<Enemy*> list_enemys;

    Enemy* enemy = new Enemy[30];
    for (int i = 0; i < 30; i++)
    {
        Enemy* p_enemy = (enemy + i);
        if (p_enemy != NULL)
        {
            p_enemy->LoadImg("image//enemy_left.png", game_screen);
            p_enemy->set_clip();
            p_enemy->set_type_move(Enemy::MOVE_IN_SPACE_ENEMY);
            p_enemy->set_x_now(1100 + i * 800);
            p_enemy->set_y_now(100);

            int left = p_enemy->get_x_now() - 100;
            int right = p_enemy->get_x_now() + 100; 
            p_enemy->set_animation(left, right);

            Bullet* bullet = new Bullet();
            p_enemy->InitBullet(bullet, game_screen);

            list_enemys.push_back(p_enemy);
        }
    }

    return list_enemys;
}

int main (int argc, char* argv[]) {

    Timer fps;

    if (InitData() == false)
    {
        return -1;
    }

    if (loadBackground() == false)
    {
        return -1;
    }

    Player p_player;
    p_player.LoadImg("image//right.png", game_screen);
    p_player.set_clip();

    std::vector<Enemy*> enemy_list = MakeEnemy();

    GameMap game_map;
    game_map.LoadMap("map//tile.map");
    game_map.LoadTiles(game_screen);

    BaseObject StartButton[2];
    BaseObject ExitButton[2];

    game_menu_screen.LoadImg("image//universe1.png", game_screen);
    StartButton[0].LoadImg("image//menu//StartButtomUp.png", game_screen);
    StartButton[1].LoadImg("image//menu//StartButtomDown.png", game_screen);
    ExitButton[0].LoadImg("image//menu//ExitButtomUp.png", game_screen);
    ExitButton[1].LoadImg("image//menu//ExitButtomDown.png", game_screen);

    SDL_Rect Button = StartButton[0].GetRect();
    StartButton[0].SetRect(SCREEN_WIDTH / 2 - Button.w / 2, SCREEN_HEIGHT / 2);
    StartButton[1].SetRect(SCREEN_WIDTH / 2 - Button.w / 2, SCREEN_HEIGHT / 2);

    Button = ExitButton[0].GetRect();
    ExitButton[0].SetRect(SCREEN_WIDTH / 2 - Button.w / 2, SCREEN_HEIGHT / 2 + Button.h * 1.5);
    ExitButton[1].SetRect(SCREEN_WIDTH / 2 - Button.w / 2, SCREEN_HEIGHT / 2 + Button.h * 1.5);

    int MousePosX = 0;
    int MousePosY = 0;

    bool is_quit = false;
    bool menu_quit = false;

    int hit_point = 5;

    // Hien thi text
    Text time_game;
    time_game.SetColor(Text::WHITE_TEXT);

    Text point;
    point.SetColor(Text::WHITE_TEXT);
    UINT point_value = 0;

    Text money;
    money.SetColor(Text::WHITE_TEXT);

    Text HP;
    HP.SetColor(Text::WHITE_TEXT);

    Text press_f;
    press_f.SetColor(Text::RED_TEXT);

    Text how_to_win;
    how_to_win.SetColor(Text::RED_TEXT);

    while (!menu_quit)
    {
        SDL_RenderClear(game_screen);
        game_menu_screen.Render(game_screen, NULL);
        while (SDL_PollEvent(&game_event) != 0)
        {
            if (game_event.type == SDL_MOUSEMOTION)
            {
                MousePosX = game_event.motion.x;
                MousePosY = game_event.motion.y;
            }
            if (game_event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (game_event.button.button == SDL_BUTTON_LEFT)
                {
                    if (SDLCommonFunction::CheckMousePos(MousePosX, MousePosY, StartButton[0].GetRect()) == true)
                    {
                        menu_quit = true;
                    }
                    if (SDLCommonFunction::CheckMousePos(MousePosX, MousePosY, ExitButton[0].GetRect()) == true)
                    {
                        menu_quit = true;
                        is_quit = true;
                    }
                }
            }
        }
        if (SDLCommonFunction::CheckMousePos(MousePosX, MousePosY, StartButton[0].GetRect()) == true)
        {
            StartButton[1].Render(game_screen);
        }
        else
        {
            StartButton[0].Render(game_screen);
        }
        if (SDLCommonFunction::CheckMousePos(MousePosX, MousePosY, ExitButton[0].GetRect()) == true)
        {
            ExitButton[1].Render(game_screen);
        }
        else
        {
            ExitButton[0].Render(game_screen);
        }
        SDL_RenderPresent(game_screen);
        SDL_Delay(100);
    }

    while (!is_quit)
    {
        fps.start();

        while (SDL_PollEvent(&game_event) != 0)
        {
            if (game_event.type == SDL_QUIT)
            {
                is_quit = true;
            }

            p_player.KeyBoard(game_event, game_screen);
        }

        SDL_SetRenderDrawColor(game_screen, 255, 255, 255, 255);
        SDL_RenderClear(game_screen);

        game_background.Render(game_screen, NULL);

        Map map_data = game_map.getMap();

        p_player.HandleBullet(game_screen);
        p_player.SetMapXY(map_data.start_x, map_data.start_y);
        p_player.DoPlayer(map_data);
        p_player.Show(game_screen);

        game_map.SetMap(map_data);
        game_map.DrawMap(game_screen);

        for (int i = 0; i < enemy_list.size(); i++)
        {
            Enemy* p_enemy = enemy_list.at(i);
            if (p_enemy != NULL)
            {
                p_enemy->SetMapXY(map_data.start_x, map_data.start_y);               
                p_enemy->ImpMoveType(game_screen);
                p_enemy->DoPlayer(map_data);
                p_enemy->MakeBullet(game_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
                p_enemy->Show(game_screen);

                SDL_Rect rect_player = p_player.GetRectFrame();
                bool bullet_impact_player = false; // va cham vua nhan vat va bullet
                std::vector<Bullet*> enemy_bullet_list = p_enemy->get_bullet_list();
                for (int j = 0; j < enemy_bullet_list.size(); j++)
                {
                    Bullet* enemy_bullet = enemy_bullet_list.at(j);
                    if (enemy_bullet)
                    {
                        SDL_Rect rect_bullet = enemy_bullet->GetRect();
                        bullet_impact_player = SDLCommonFunction::CheckImpact(rect_bullet, rect_player);
                    }
                }

                SDL_Rect rect_enemy = p_enemy->GetRectFrame();
                bool player_impact_enemy = SDLCommonFunction::CheckImpact(rect_player, rect_enemy); // va cham giua nhan vat va enemy

                if (bullet_impact_player || player_impact_enemy)
                { 
                    hit_point--;
                    if (hit_point > 0)
                    {
                        p_player.SetRect(0, 0);
                        p_player.set_comeback_time(1);
                        SDL_Delay(1000);
                    }
                    else
                    {
                        if (MessageBox(NULL, L"GAME OVER", L"Thong Bao", MB_OK | MB_ICONSTOP) == IDOK)
                        {
                            p_enemy->Free();
                            close();
                            SDL_Quit();
                            return 0;
                        }
                    }
                }
            }
        }

        std::vector<Bullet*> bullet_arr = p_player.get_bullet_list();
        for (int i = 0; i < bullet_arr.size(); i++)
        {
            Bullet* bullet = bullet_arr.at(i);
            if (bullet != NULL)
            {
                for (int j = 0; j < enemy_list.size(); j++)
                {
                    Enemy* enemy = enemy_list.at(j);
                    if (enemy != NULL)
                    {
                        SDL_Rect enemy_rect;
                        enemy_rect.x = enemy->GetRect().x;
                        enemy_rect.y = enemy->GetRect().y;
                        enemy_rect.w = enemy->get_width_frame();
                        enemy_rect.h = enemy->get_height_frame();

                        SDL_Rect bullet_rect = bullet->GetRect();
                        bool bullet_impact_enemy = SDLCommonFunction::CheckImpact(bullet_rect, enemy_rect);  // Va cham giua enemy va bullet

                        if (bullet_impact_enemy)
                        {
                            point_value++;
                            p_player.RemoveBullet(i);
                            enemy->Free();
                            enemy_list.erase(enemy_list.begin() + j);
                        }
                    }
                }
            }
        }

        // Show game time
        std::string string_text_time = "Time: ";
        Uint32 second = SDL_GetTicks() / 1000;
        Uint32 value_time = 200 - second;
        if (value_time < 0)
        {
            if (MessageBox(NULL, L"GAME OVER", L"Thong Bao", MB_OK | MB_ICONSTOP) == IDOK)
            {
                is_quit = true;
                break;
            }
        }
        else
        {
            std::string string_time = std::to_string(value_time);
            string_text_time += string_time;

            time_game.SetText(string_text_time);
            time_game.LoadFromRenderText(font, game_screen);
            time_game.RenderText(game_screen, SCREEN_WIDTH - 130, 10);
        }

        // Show game point
        std::string string_point = std::to_string(point_value);
        std::string string_text_point = "Point: ";
        string_text_point += string_point;

        point.SetText(string_text_point);
        point.LoadFromRenderText(font, game_screen);
        point.RenderText(game_screen, SCREEN_WIDTH * 0.6, 5);

        // Show game money
        int money_count = p_player.GetMoneyCount();
        std::string string_money = std::to_string(money_count);
        std::string string_text_money = "Money: ";
        string_text_money += string_money;

        money.SetText(string_text_money);
        money.LoadFromRenderText(font, game_screen);
        money.RenderText(game_screen, SCREEN_WIDTH * 0.3 - 20, 5);

        if (point_value == 30)
        {
            if (MessageBox(NULL, L"YOU WIN!!!", L"Thong Bao", MB_OK | MB_ICONSTOP) == IDOK)
            {
                is_quit = true;
                break;
            }
        }

        // Show hit point
        std::string string_hp = std::to_string(hit_point);
        std::string string_text_hp = "HP: ";
        string_text_hp += string_hp;

        HP.SetText(string_text_hp);
        HP.LoadFromRenderText(font, game_screen);
        HP.RenderText(game_screen, 30, 5);

        // Show press f
        std::string string_text_press_f = "Press F to shoot";
        press_f.SetText(string_text_press_f);
        press_f.LoadFromRenderText(font, game_screen);
        press_f.RenderText(game_screen, 30, 45);

        // Show how to win
        std::string string_text_how_to_win = "Clear all enemy to win";
        press_f.SetText(string_text_how_to_win);
        press_f.LoadFromRenderText(font, game_screen);
        press_f.RenderText(game_screen, 30, 85);

        SDL_RenderPresent(game_screen);

        int real_time = fps.get_tick();
        int time_one_frame = 1000 / FRAME_PER_SECOND;

        if (real_time < time_one_frame)
        {
            int delay_time = time_one_frame - real_time;
            if (delay_time >= 0)
            {
                SDL_Delay(delay_time);
            }
        }
    }
    
    for (int i = 0; i < enemy_list.size(); i++)
    {
        Enemy* enemy = enemy_list.at(i);
        if (enemy)
        {
            enemy->Free();
            enemy = NULL;
        }
    }

    enemy_list.clear();

    close();
    return 0;
}