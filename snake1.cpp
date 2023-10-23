#include<iostream>
#include<curses.h>
#include<vector>
#include<string.h>
#include<unistd.h>
#include<ctime>
#include<map>
#include<fstream>
#include "snake1.h"
using namespace std;
int ma_x = 0, ma_y = 160;// lay toa do cua man hinh hien tai
void Body::set_body(int x_demo, int y_demo, char c_demo)
{
    this->x = x_demo;
    this->y = y_demo;
    this->c = c_demo;
}
void food::set_food(int x_demo, int y_demo, char c_demo)
{
    this->x = x_demo;
    this->y = y_demo;
    this->c = c_demo;
}
void food::ramdom_food()
{
    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);
    this->x = (rand()) % (max_x - 1);
    this->y = (rand()) % (max_y - 1);
    mvprintw(this->y, this->x, "%c", this->c);
    refresh();
}
void food::ramdom_food(int x0, int y0, int x1, int y1)
{
    this->x = x0 + rand() % (x1 - x0 - 1);
    this->y = y0 + rand() % (y1 - y0 - 1);
    mvprintw(this->y, this->x, "%c", this->c);
    refresh();
}
void food::ramdom_food(int x0, int y0, int x1, int y1, int x0m, int y0m, int x1m, int y1m)
{
    this->x = x0 + rand() % (x1 - x0 - 1);
    this->y = y0 + rand() % (y1 - y0 - 1);
    if(this->x == x0m) this->x = this->x - 2;
    if(this->x == x1m) this->x = this->x + 2;
    if(this->y == y0m) this->y = this->y + 2;
    if(this->y == y1m) this->y = this->y - 2;
    mvprintw(this->y, this->x, "%c", this->c);
    refresh();
}
void food::ramdom_best_food()
{
    this->vtri_x = (rand()) % (ma_x - 6);
    this->vtri_y = 4 + (rand()) % (ma_y - 8);
    for(int i = 0; i < best_food.size(); i++)
    { 
	for(int j = 0; j < best_food[i].size(); j++)
	{
            mvprintw(this->vtri_y + i, this->vtri_x + j, "%c", best_food[i][j]);
	    refresh();
	}
    }
}
void food::ramdom_best_food(int x0, int y0, int x1, int y1)// phu thuoc vao tuong hoac khong tuong
{
    this->vtri_x = (rand()) % (x1 - x0 - 1);
    this->vtri_y = 4 + (rand()) % (y1 - y0 - 4);
    for(int i = 0; i < best_food.size(); i++)
    {
        for(int j = 0; j < best_food[i].size(); j++)
        {
            mvprintw(this->vtri_y + i, this->vtri_x + j, "%c", best_food[i][j]);
            refresh();
        }
    }
}
void food::delete_best_food()
{
    for(int i = 0; i < best_food.size(); i++)
    {
        for(int j = 0; j < best_food[i].size(); j++)
        {
            mvprintw(this->vtri_y + i, this->vtri_x + j, " ");
            refresh();
        }
    }
}
gun::gun()
{
    x = ma_x / 2; y = ma_y / 2; c = 'V';
    tmp_x = 1; tmp_y = 0;
}
void gun::set_gun(int x0, int y0, int tmp_x0, int tmp_y0, char c0)
{
    x = x0; y = y0; tmp_x = tmp_x0; tmp_y = tmp_y0; c = c0;
}
void gun::print_gun()
{
    mvprintw(y + tmp_y, x + tmp_x, "%c", c); refresh();
}
void gun::delete_gun()
{
    mvprintw(y + tmp_y, x + tmp_x, " "); refresh();
}
void highscore::get_highscore(int diem0, char name[100], int hoi)
{
    if(hoi == 1)
    {
    fstream file;
    file.open("diem_one.txt", ios::in | ios::out);
    if (file.is_open())
    {
        file.seekg(0, std::ios::end); // Di chuyển con trỏ đến cuối file
        std::streampos fileSize = file.tellg(); // Lấy vị trí hiện tại của con trỏ (kích thước file)
        if (fileSize == 0)
        {
            file << diem0 << " " << name;
        }
        else
        {
            int num;
	    file.seekg(0, ios::beg); // Di chuyển con trỏ ghi về đầu file
            file >> num;
            if(num < diem0)
	    { 
		file.seekg(0, ios::beg);
	        file << max(num, diem0) << " " << name;
	    }
        }

        file.close();
    }
    }
    else if(hoi == 2)
    {
    fstream file;
    file.open("diem_two.txt", ios::in | ios::out);
    if (file.is_open())
    {
        file.seekg(0, std::ios::end); // Di chuyển con trỏ đến cuối file
        std::streampos fileSize = file.tellg(); // Lấy vị trí hiện tại của con trỏ (kích thước file)
        if (fileSize == 0)
        {
            file << diem0 << " " << name;
        }
        else
        {
            int num;
            file.seekg(0, ios::beg); // Di chuyển con trỏ ghi về đầu file
            file >> num;
            if(num < diem0)
            {
                file.seekg(0, ios::beg);
                file << max(num, diem0) << " " << name;
            }
        }

        file.close();
    }
    }

}
highscore hs;///// check diem cao
wall::wall(){x0 = 0; y0 = 3; x1 = ma_x; y1 = ma_y; ktu = '#';}
void wall::set_wall(int x00, int y00, int x11, int y11, char ktu1)
{
    x0 = x00; y0 = y00; x1 = x11; y1 = y11; ktu = ktu1;
}
void wall::print_wall()
{
    for(int i = x0; i <= x1; i++)
    {
        mvprintw(y0, i, "%c", ktu); refresh();
	mvprintw(y1, i, "%c", ktu); refresh();
    }
    for(int i = y0 + 1; i < y1; i++)
    {
        mvprintw(i, x0, "%c", ktu); refresh();
	mvprintw(i, x1, "%c", ktu); refresh();
    }
}
void wall::print_wallx()
{
    for(int i = 2 * (x1 - x0 + 1) / 3 + 1; i < 3 * (x1 - x0 + 1) / 3; i++)
    {
        mvprintw(y0, i, " "); refresh();
	mvprintw(y1, i, " "); refresh();
    }
    for(int i = 2 * (y1 - y0 + 1) / 3 + 1; i < 3 * (y1 - y0 + 1) / 3; i++)
    {
        mvprintw(i, x0, " "); refresh();
	mvprintw(i, x1, " "); refresh();
    }
}
hole::hole()
{
    x = ma_x - 15; y = ma_y - 4;
}
void hole::print_hole()
{
    for(int i = 0; i < hd.size(); i++)
    {
        for(int j = 0; j < hd[i].size(); j++)
	{
	    mvprintw(y + i, x + j, "%c", hd[i][j]);
	}
    }
}

// RAN O MAP 2
// RAN O MAP 1
bool check_map0 = true;
bool check_map1 = false;
snake0::snake0()
{
    diem0.a1 = 0; check_snake0 = true; char_body0 = 'O'; tuong0.set_wall(1, 3, ma_x - 1, ma_y -1, '#');
    tuong01.set_wall((tuong0.x1 - tuong0.x0 + 1) / 5, (tuong0.y1 - tuong0.y0 + 1) / 5, 4 * (tuong0.x1 - tuong0.x0 + 1) / 5, 4 * (tuong0.y1 - tuong0.y0) / 5, '#');
    for(int i = 0; i <= 3; i++)
    {
        Body b0; b0.set_body(25 + i, 10, char_body0);
	snake_run0.push_back(b0);
    }
}
void snake0::print_snake0()
{
    for(int i = 0; i < snake_run0.size(); i++)
    {
        mvprintw(snake_run0[i].y, snake_run0[i].x, "%c", snake_run0[i].c);//usleep(50000);
        refresh();
    }
}
void snake0::delete_snake0()
{
    for(int i = 0; i < snake_run0.size(); i++)
    {
        mvprintw(snake_run0[i].y, snake_run0[i].x," ");
        refresh();
    }
}
bool snake0::attack0(food place_food)
{
    if(place_food.x == snake_run0[snake_run0.size() - 1].x && place_food.y == snake_run0[snake_run0.size() - 1].y)
    {
        mvprintw(place_food.y, place_food.x, " ");
        return true;
    }
    return false;
}
bool snake0::attack_best0(food place_food)
{
    if((place_food.vtri_x + 1 <= snake_run0[snake_run0.size() - 1].x && snake_run0[snake_run0.size() - 1].x <= place_food.vtri_x + 3 && place_food.vtri_y == snake_run0[snake_run0.size() - 1].y) ||
       (place_food.vtri_x + 1 <= snake_run0[snake_run0.size() - 1].x && snake_run0[snake_run0.size() - 1].x <= place_food.vtri_x + 3 && place_food.vtri_y + 2 == snake_run0[snake_run0.size() - 1].y) ||
       (place_food.vtri_x == snake_run0[snake_run0.size() - 1].x && place_food.vtri_y + 1 == snake_run0[snake_run0.size() - 1].y) ||
       (place_food.vtri_x + 4 == snake_run0[snake_run0.size() - 1].x && place_food.vtri_y + 1 == snake_run0[snake_run0.size() - 1].y)
      )
    {
        return true;
    }
    return false;
}
bool snake0::attack_wall0()
{
    if((snake_run0[snake_run0.size() - 1].x >= tuong0.x0 && snake_run0[snake_run0.size() - 1].x <= tuong0.x1 && (snake_run0[snake_run0.size() - 1].y == tuong0.y0 || snake_run0[snake_run0.size() - 1].y == tuong0.y1)) ||
       (snake_run0[snake_run0.size() - 1].y >= tuong0.y0 && snake_run0[snake_run0.size() - 1].y <= tuong0.y1 && (snake_run0[snake_run0.size() - 1].x == tuong0.x0 || snake_run0[snake_run0.size() - 1].x == tuong0.x1)) )
    {
        return true;
    }
    return false;
}
bool snake0::attack_wall01()
{
    if(snake_run0[snake_run0.size() - 1].x == tuong01.x0 && (snake_run0[snake_run0.size() - 1].y >= tuong01.y0 && snake_run0[snake_run0.size() - 1].y <= tuong01.y0 + (tuong01.y1 - tuong01.y0 + 1) / 3))
    {
        return true;
    }
    if(snake_run0[snake_run0.size() - 1].x == tuong01.x1 && (snake_run0[snake_run0.size() - 1].y >= tuong01.y0  && snake_run0[snake_run0.size() - 1].y <= tuong01.y0 + (tuong01.y1 - tuong01.y0 + 1) / 3))
    {
        return true;
    }
    if(snake_run0[snake_run0.size() - 1].x == tuong01.x0 && snake_run0[snake_run0.size() - 1].y <= tuong01.y1 && snake_run0[snake_run0.size() - 1].y >= tuong01.y1 - (tuong01.y1 - tuong01.y0 + 1) / 3)
    {
        return true;
    }
    if(snake_run0[snake_run0.size() - 1].x == tuong01.x1 && snake_run0[snake_run0.size() - 1].y <= tuong01.y1 && snake_run0[snake_run0.size() - 1].y >= tuong01.y1 - (tuong01.y1 - tuong01.y0 + 1) / 3)
    {
        return true;
    }
    if(snake_run0[snake_run0.size() - 1].y == tuong01.y0 && (snake_run0[snake_run0.size() - 1].x >= tuong01.x0 && snake_run0[snake_run0.size() - 1].x <= tuong01.x0 + (tuong01.x1 - tuong01.x0 + 1) / 3))
    {
        return true;
    }
    if(snake_run0[snake_run0.size() - 1].y == tuong01.y1 && (snake_run0[snake_run0.size() - 1].x >= tuong01.x0 && snake_run0[snake_run0.size() - 1].x <= tuong01.x0 + (tuong01.x1 - tuong01.x0 + 1) / 3))
    {
        return true;
    }
    if(snake_run0[snake_run0.size() - 1].y == tuong01.y0 && snake_run0[snake_run0.size() - 1].x <= tuong01.x1 && snake_run0[snake_run0.size() - 1].x >= tuong01.x1 - (tuong01.x1 - tuong01.x0 + 1) / 3)
    {
        return true;
    }
    if(snake_run0[snake_run0.size() - 1].y == tuong01.y1 && snake_run0[snake_run0.size() - 1].x <= tuong01.x1 && snake_run0[snake_run0.size() - 1].x >= tuong01.x1 - (tuong01.x1 - tuong01.x0 + 1) / 3)
    {
        return true;
    }
    return false;

}

void snake0::no_wall0()// di xuyen tuong
{
    if(snake_run0[snake_run0.size() - 1].y <= tuong0.y0) snake_run0[snake_run0.size() - 1].y = tuong0.y1 - 2;
    if(snake_run0[snake_run0.size() - 1].x <= tuong0.x0) snake_run0[snake_run0.size() - 1].x = tuong0.x1 - 2;
    if(snake_run0[snake_run0.size() - 1].x >= tuong0.x1 - 1) snake_run0[snake_run0.size() - 1].x = tuong0.x0 + 1;
    if(snake_run0[snake_run0.size() - 1].y >= tuong0.y1 - 1) snake_run0[snake_run0.size() - 1].y = tuong0.y0 + 1;
}
void snake0::print_score0()
{
    mvprintw(tuong0.y0 - 1, tuong0.x1 - 10, "SCORE: %d", diem0.a1);
    refresh();
    mvprintw(tuong0.y0 - 1, tuong0.x0 + 1, "LEVEL: %d", level);
    refresh();
}
bool snake0::attack_hole1()
{
    if(snake_run0[snake_run0.size() - 1].x >= den1.x && snake_run0[snake_run0.size() - 1].x <= den1.x + 10 && (snake_run0[snake_run0.size() - 1].y == den1.y || snake_run0[snake_run0.size() - 1].y == den1.y + 2))
    {
        return true;
    }
    if(snake_run0[snake_run0.size() - 1].y >= den1.y && snake_run0[snake_run0.size() - 1].y <= den1.y + 2 && (snake_run0[snake_run0.size() - 1].x == den1.x || snake_run0[snake_run0.size() - 1].x == den1.x + 10))
    {
        return true;
    }
    return false;
}
void snake0::setup_data0()
{
    diem0.a1 = 0; char_body0 = 'O';
    snake_run0.erase(snake_run0.begin(), snake_run0.end());
    for(int i = 0; i <= 3; i++)
    {
        Body b0; b0.set_body(25 + i, 10, char_body0);
        snake_run0.push_back(b0);
    }
}
void snake0::end_game0()
{
    check_snake0 = false;
    usleep(18000000);
}
void snake0::Run0(char name[100])
{
    if(check_map0 == false) return;
    nodelay(stdscr, TRUE);// tat che do cho cua ham getch;
    tuong0.print_wall();
    tuong01.print_wall(); tuong01.print_wallx();
    bool attack_h = false;// kiem tra ho den vu tru
    print_score0();
    int tmp1 = 0, tmp2 = 0;
    bool check_food = false;
    bool check_best_food = false;
    noecho(); curs_set(0);// tat nhap hien ki tu va con tro nhay
    food place_food; int cnt = 0; int lev = 0;
    while(check_snake0 == true)
    {
        if(check_food == false)
        {
            place_food.ramdom_food(tuong0.x0 + 1, tuong0.y0 + 5, tuong0.x1 - 2, tuong0.y1 - 2, tuong01.x0, tuong01.y0, tuong01.x1, tuong01.y1);// map1
            check_food = true;
        }
        if(check_best_food == false && cnt == 3)
        {
            place_food.ramdom_best_food(tuong0.x0 + 1, tuong0.y0 + 5, tuong0.x1 - 8, tuong0.y1 - 5);// map1
	    cnt = 0; kho -= 5000;
            check_best_food = true;
        }
	if(attack_h == true)
	{
	    den1.print_hole();
	    if(this->attack_hole1() == true)
	    {
		clear();
		check_map1 = true; check_map0 = false;
		snake1 ran1; ran1.diem1.a1 = diem0.a1; ran1.Run1(name);
	    }// kiem tra va cham voi ho den

	}
        char c = getch();
        if(c == 's')
        {
            tmp1 = 0; tmp2 = 1;
        }
        if(c == 'w')
        {
            tmp1 = 0; tmp2 = -1;
        }
        if(c == 'a')
        {
            tmp1 = -1; tmp2 = 0;
        }
        if(c == 'd')
        {
            tmp1 = 1; tmp2 = 0;
        }
        if(c == 'q')
        {
            //print_snake();
            nodelay(stdscr, FALSE);
	    clear();
	    cha x; x.menu2(diem0.a1, name, 1);
	    clear();
	    tuong0.print_wall(); tuong01.print_wall(); tuong01.print_wallx();
	    check_food = false;
	    nodelay(stdscr, TRUE);
            //break;
        }
        Body new_body(snake_run0[snake_run0.size() - 1].x, snake_run0[snake_run0.size() - 1].y, char_body0);
        this->no_wall0();// di xuyen tuong
        new_body.set_body(snake_run0[snake_run0.size() - 1].x + 1 * tmp1, snake_run0[snake_run0.size() - 1].y + 1 * tmp2, char_body0);
        if(tmp1 == 0 && tmp2 == 0)
        {
            print_snake0();
            // kiem tra va cham
            /*if(this->attack0(place_food) == true)
            {
                // tao moi moi
                check_food = false;
                diem0.a1++;// tang diem
                cnt++;
                // them 1 body tang do dai cho ran
                Body new_body1; new_body1.set_body(snake_run0[0].x - 1, snake_run0[0].y, char_body0);// can kiem tra xem chieu di cua body cuoi khong ????
                snake_run0.insert(snake_run0.begin(), new_body1);
            }
            if(this->attack_best0(place_food) == true)
            {
                // tao moi dac biet moi
                check_best_food = false;
                diem0.a1 += 10; 
                place_food.delete_best_food();
            }*/
            usleep(difficult);
            delete_snake0();
        }   
        else
        {
            snake_run0.push_back(new_body);
            snake_run0.erase(snake_run0.begin());
            print_snake0();
            // kiem tra va cham
            if(this->attack0(place_food) == true)
            {
                // tao moi moi
                check_food = false;
                diem0.a1++;// tang diem
		limit_score++;
		lev++;// tang level
		if(limit_score == 4)// kiem tra du diem chua de mo ho den
		{
		    attack_h = true;
		}
		cnt++;
                // them 1 body tang do dai cho ran
                Body new_body1; new_body1.set_body(snake_run0[0].x - 1, snake_run0[0].y, char_body0);// can kiem tra xem chieu di cua body cuoi khong ????
                snake_run0.insert(snake_run0.begin(), new_body1);
            }
            /*if(this->attack_best0(place_food) == true)
            {
                // tao moi dac biet moi
                check_best_food = false;
                diem0.a1 += 10;
                place_food.delete_best_food();
            }*/
            if(this->attack_wall0() == true)
            {
		this->no_wall0();
	        tuong0.print_wall();
            }
	    if(this->attack_wall01() == true)
	    {
	        hs.get_highscore(diem0.a1, name, 1);
                nodelay(stdscr, FALSE);
                cha x; x.menu1();
	    }
            usleep(difficult);
            delete_snake0();
        }
	if(lev >= 5)
	{
	    if(level < 5)
	    {
	        level++;
	        lev = 0;
	        difficult = difficult * 4; difficult /= 5;
	    }
	}
	print_score0();
    }
    nodelay(stdscr, FALSE);
}
// RAN O MAP 2
snake1::snake1()
{
    diem1.a1 = 0; check_snake1 = true; char_body1 = 'O'; tuong1.set_wall(1, ma_y / 10, ma_x - 1, ma_y -1, '#');
    tuong11.set_wall(ma_x / 4, ma_y / 10 + ma_y / 3, 3 * ma_x / 4, ma_y / 3 + ma_y / 7, '#');
    tuong111.set_wall(ma_x / 4, ma_y / 10 + 2 * ma_y / 3, 3 * ma_x / 4, 2 * ma_y / 3 + ma_y / 7, '#');
    for(int i = 0; i <= 3; i++)
    {
        Body b1; b1.set_body(25 + i, 10, char_body1);
        snake_run1.push_back(b1);
    }
}
void snake1::print_snake1()
{
    for(int i = 0; i < snake_run1.size(); i++)
    {
        mvprintw(snake_run1[i].y, snake_run1[i].x, "%c", snake_run1[i].c);//usleep(50000);
        refresh();
    }
}
void snake1::delete_snake1()
{
    for(int i = 0; i < snake_run1.size(); i++)
    {
        mvprintw(snake_run1[i].y, snake_run1[i].x," ");
        refresh();
    }
}
bool snake1::attack1(food place_food)
{
    if(place_food.x == snake_run1[snake_run1.size() - 1].x && place_food.y == snake_run1[snake_run1.size() - 1].y)
    {
        mvprintw(place_food.y, place_food.x, " ");
        return true;
    }
    return false;
}
bool snake1::attack_best1(food place_food)
{
    if((place_food.vtri_x + 1 <= snake_run1[snake_run1.size() - 1].x && snake_run1[snake_run1.size() - 1].x <= place_food.vtri_x + 3 && place_food.vtri_y == snake_run1[snake_run1.size() - 1].y) ||
       (place_food.vtri_x + 1 <= snake_run1[snake_run1.size() - 1].x && snake_run1[snake_run1.size() - 1].x <= place_food.vtri_x + 3 && place_food.vtri_y + 2 == snake_run1[snake_run1.size() - 1].y) ||
       (place_food.vtri_x == snake_run1[snake_run1.size() - 1].x && place_food.vtri_y + 1 == snake_run1[snake_run1.size() - 1].y) ||
       (place_food.vtri_x + 4 == snake_run1[snake_run1.size() - 1].x && place_food.vtri_y + 1 == snake_run1[snake_run1.size() - 1].y)
      )
    {
        return true;
    }
    return false;
}
bool snake1::attack_wall1()
{
    if((snake_run1[snake_run1.size() - 1].x >= tuong1.x0 && snake_run1[snake_run1.size() - 1].x <= tuong1.x1 && (snake_run1[snake_run1.size() - 1].y == tuong1.y0 || snake_run1[snake_run1.size() - 1].y == tuong1.y1)) ||
       (snake_run1[snake_run1.size() - 1].y >= tuong1.y0 && snake_run1[snake_run1.size() - 1].y <= tuong1.y1 && (snake_run1[snake_run1.size() - 1].x == tuong1.x0 || snake_run1[snake_run1.size() - 1].x == tuong1.x1)) )
    {
        return true;
    }
    if((snake_run1[snake_run1.size() - 1].x >= tuong11.x0 && snake_run1[snake_run1.size() - 1].x <= tuong11.x1 && (snake_run1[snake_run1.size() - 1].y == tuong11.y0 || snake_run1[snake_run1.size() - 1].y == tuong11.y1)) ||
       (snake_run1[snake_run1.size() - 1].y >= tuong11.y0 && snake_run1[snake_run1.size() - 1].y <= tuong11.y1 && (snake_run1[snake_run1.size() - 1].x == tuong11.x0 || snake_run1[snake_run1.size() - 1].x == tuong11.x1)) )
    {
        return true;
    }
    if((snake_run1[snake_run1.size() - 1].x >= tuong111.x0 && snake_run1[snake_run1.size() - 1].x <= tuong111.x1 && (snake_run1[snake_run1.size() - 1].y == tuong111.y0 || snake_run1[snake_run1.size() - 1].y == tuong111.y1)) ||
       (snake_run1[snake_run1.size() - 1].y >= tuong111.y0 && snake_run1[snake_run1.size() - 1].y <= tuong111.y1 && (snake_run1[snake_run1.size() - 1].x == tuong111.x0 || snake_run1[snake_run1.size() - 1].x == tuong111.x1)) )
    {
        return true;
    }
    return false;
}
//bool snake1::attack_hole1()
//{
//    if(snake_run1[snake_run1.size() - 1].x >= den1.x && snake_run1[snake_run1.size() - 1].x <= den1.x + 10 && (snake_run1[snake_run1.size() - 1].y == den1.y || snake_run1[snake_run1.size() - 1].y == den1.y + 2))
//    {
//        return true;
//    }
//    if(snake_run1[snake_run1.size() - 1].y >= den1.y && snake_run1[snake_run1.size() - 1].y <= den1.y + 2 && (snake_run1[snake_run1.size() - 1].x == den1.x || snake_run1[snake_run1.size() - 1].x == den1.x + 10))
//    {
//        return true;
//    }
//    return false;
//}
void snake1::print_score1()
{
    mvprintw(tuong1.y0 - 1, tuong1.x1 - 10, "SCORE: %d", diem1.a1);
    refresh();
    mvprintw(tuong1.y0 - 1, tuong1.x0 + 1, "LEVEL: %d", level);
    refresh();
}
void snake1::setup_data1()
{
    diem1.a1 = 0; char_body1 = 'O';
    snake_run1.erase(snake_run1.begin(), snake_run1.end());
    for(int i = 0; i <= 3; i++)
    {
        Body b1; b1.set_body(25 + i, 10, char_body1);
        snake_run1.push_back(b1);
    }
}
void snake1::end_game1()
{
    check_snake1 = false;
    usleep(18000000);
}
void snake1::Run1(char name[100])
{
    if(check_map1 == false) return;
    nodelay(stdscr, TRUE);// tat che do cho cua ham getch;
    tuong1.print_wall();
    tuong11.print_wall();
    tuong111.print_wall();
    print_score1();
    int tmp1 = 0, tmp2 = 0;
    bool check_food = false;
    bool check_best_food = false;
    noecho(); curs_set(0);// tat nhap hien ki tu va con tro nhay
    food place_food; int cnt = 0; int lev = 0;
    vector<food> foo(5);
    vector<bool> check_foo(5);
    for(int i = 0; i < 5; i++) check_foo[i] = false;
    while(check_snake1 == true)
    {
	for(int i = 0; i < 5; i++)
	{
	    if(check_foo[i] == false)
	    {
	        if(i == 0){ foo[i].ramdom_food(tuong1.x0 + 2, tuong1.y0 + 5, tuong11.x0 - 2, tuong1.y1 - 5); check_foo[i] = true;}
		else if(i == 1){foo[i].ramdom_food(tuong11.x0 + 2, tuong1.y0 + 5, tuong11.x1 - 2, tuong11.y0 - 2); check_foo[i] = true;}
		else if(i == 2){foo[i].ramdom_food(tuong11.x1 + 2, tuong1.y0 + 5, tuong1.x1 - 2, tuong1.y1 - 5); check_foo[i] = true;}
		else if(i == 3){foo[i].ramdom_food(tuong111.x0 + 2, tuong111.y1 + 2, tuong111.x1 - 2, tuong1.y1 - 2); check_foo[i] = true;}
                else if(i == 4){foo[i].ramdom_food(tuong11.x0 + 2, tuong11.y1 + 2, tuong11.x1 - 1, tuong111.y0 -2); check_foo[i] = true;}
	    }
	}
        if(check_food == false)
        {
            place_food.ramdom_food(tuong1.x0 + 1, tuong1.y0 + 5, tuong1.x1 - 2, tuong1.y1 - 5);// map1
            check_food = true;
        }
        /*if(check_best_food == false && cnt == 3)
        {
            place_food.ramdom_best_food(tuong1.x0 + 1, tuong1.y0 + 5, tuong1.x1 - 8, tuong1.y1 - 5);// map1
            cnt = 0; kho += -5000;
            check_best_food = true;
        }*/
        char c = getch();
        if(c == 's')
        {
            tmp1 = 0; tmp2 = 1;
        }
        if(c == 'w')
        {
            tmp1 = 0; tmp2 = -1;
        }
        if(c == 'a')
        {
            tmp1 = -1; tmp2 = 0;
        }
        if(c == 'd')
        {
            tmp1 = 1; tmp2 = 0;
        }
        if(c == 'q')
        {
            nodelay(stdscr, FALSE);
            clear();
            cha x; x.menu2(diem1.a1, name, 1);
            clear();
            tuong1.print_wall();tuong11.print_wall(); tuong111.print_wall();
            check_food = false;
	    for(int i = 0; i < 5; i++) check_foo[i] = false;
            nodelay(stdscr, TRUE);
        }
        Body new_body(snake_run1[snake_run1.size() - 1].x, snake_run1[snake_run1.size() - 1].y, char_body1);
        //this->no_wall0();// di xuyen tuong
        new_body.set_body(snake_run1[snake_run1.size() - 1].x + 1 * tmp1, snake_run1[snake_run1.size() - 1].y + 1 * tmp2, char_body1);
        if(tmp1 == 0 && tmp2 == 0)
        {
            print_snake1();
            // kiem tra va cham
            //if(this->attack1(place_food) == true)
            //{
            //    // tao moi moi
            //    check_food = false;
            //    diem1.a1++;// tang diem
            //    cnt++;
            //    // them 1 body tang do dai cho ran
            //    Body new_body1; new_body1.set_body(snake_run1[0].x - 1, snake_run1[0].y, char_body1);// can kiem tra xem chieu di cua body cuoi khong ????
            //    snake_run1.insert(snake_run1.begin(), new_body1);
            //}
                // tao moi dac biet moi
            usleep(90000 + kho);
            delete_snake1();
        }
        else
        {
            snake_run1.push_back(new_body);
            snake_run1.erase(snake_run1.begin());
            print_snake1();
            // kiem tra va cham
            if(this->attack1(place_food) == true)
	    {                // tao moi moi
                check_food = false;
                diem1.a1++;// tang diem
                cnt++; lev++;
                // them 1 body tang do dai cho ran
                Body new_body1; new_body1.set_body(snake_run1[0].x - 1, snake_run1[0].y, char_body1);// can kiem tra xem chieu di cua body cuoi khong ????
                snake_run1.insert(snake_run1.begin(), new_body1);
            }
	    for(int i = 0; i < 5; i++)
	    {
	        if(this->attack1(foo[i]) == true)
		{
		    check_foo[i] = false;
		    diem1.a1++;// tang diem
		    cnt++; lev++;
		    // them 1 body tang do fai cho ran
		    Body new_body1; new_body1.set_body(snake_run1[0].x - 1, snake_run1[0].y, char_body1);// can kiem tra xem chieu di cua body cuoi khong ????
                    snake_run1.insert(snake_run1.begin(), new_body1);
		}
	    }
            /*if(this->attack_best1(place_food) == true)
            {
                // tao moi dac biet moi
                check_best_food = false;
                diem1.a1 += 10;
                place_food.delete_best_food();
            }*/
            if(this->attack_wall1() == true)
            {
	        hs.get_highscore(diem1.a1, name, 1);
		nodelay(stdscr, FALSE);
                cha x; x.menu1();
            }
            usleep(difficult);
            delete_snake1();
        }
	if(lev >= 5)
	{
	    if(level < 5)
	    {
	         difficult *= 4; difficult /= 5; level++; lev = 0;
	    }
	}
        print_score1();
    }
    nodelay(stdscr, FALSE);
}
// 2 nguoi choi
snake2::snake2()
{
    diem2.a1 = 0; diem2.a2 = 0; check_snake2 = true; check_snake22 = true; char_body2 = 'O'; char_body22 = 'X'; tuong2.set_wall(1, 3, ma_x - 1, ma_y -1, '#');
    tuong22.set_wall((tuong2.x1 - tuong2.x0 + 1) / 5, (tuong2.y1 - tuong2.y0 + 1) / 5, 4 * (tuong2.x1 - tuong2.x0 + 1) / 5, 4 * (tuong2.y1 - tuong2.y0) / 5, '#');
    for(int i = 0; i <= 3; i++)
    {
        Body b2, b22; b2.set_body(125 + i, 10, char_body2);
	b22.set_body(125 + i, 20, char_body22);
	snake_run2.push_back(b2);
        snake_run22.push_back(b22);
    }
    //gun danx1; danx1.set_gun(snake_run2[snake_run2.size() - 1].x, snake_run2[snake_run2.size() - 1].y, 1, 0, 'V'); n1.push_back(danx1);
    //gun danx2; danx2.set_gun(snake_run22[snake_run22.size() - 1].x, snake_run22[snake_run22.size() - 1].y, 1, 0, 'V'); n2.push_back(danx2);
}
void snake2::print_snake2()
{
    for(int i = 0; i < snake_run2.size(); i++)
    {
        mvprintw(snake_run2[i].y, snake_run2[i].x, "%c", snake_run2[i].c);//usleep(50000);
        refresh();
    }
}
void snake2::print_snake22()
{
    for(int i = 0; i < snake_run22.size(); i++)
    {
        mvprintw(snake_run22[i].y, snake_run22[i].x, "%c", snake_run22[i].c);//usleep(50000);
        refresh();
    }
}
void snake2::delete_snake2()
{
    for(int i = 0; i < snake_run2.size(); i++)
    {
        mvprintw(snake_run2[i].y, snake_run2[i].x," ");
        refresh();
    }
}
void snake2::delete_snake22()
{
    for(int i = 0; i < snake_run22.size(); i++)
    {
        mvprintw(snake_run22[i].y, snake_run22[i].x," ");
        refresh();
    }
}
bool snake2::attack2(food place_food)
{
    if(place_food.x == snake_run2[snake_run2.size() - 1].x && place_food.y == snake_run2[snake_run2.size() - 1].y)
    {
        mvprintw(place_food.y, place_food.x, " ");
        return true;
    }
    return false;
}
bool snake2::attack22(food place_food)
{
    if(place_food.x == snake_run22[snake_run22.size() - 1].x && place_food.y == snake_run22[snake_run22.size() - 1].y)
    {
        mvprintw(place_food.y, place_food.x, " ");
        return true;
    }
    return false;
}
bool snake2::attack_wall2()
{
    if((snake_run2[snake_run2.size() - 1].x >= tuong2.x0 && snake_run2[snake_run2.size() - 1].x <= tuong2.x1 && (snake_run2[snake_run2.size() - 1].y == tuong2.y0 || snake_run2[snake_run2.size() - 1].y == tuong2.y1)) ||
       (snake_run2[snake_run2.size() - 1].y >= tuong2.y0 && snake_run2[snake_run2.size() - 1].y <= tuong2.y1 && (snake_run2[snake_run2.size() - 1].x == tuong2.x0 || snake_run2[snake_run2.size() - 1].x == tuong2.x1)) )
    {
        return true;
    }
    return false;
}
bool snake2::attack_wall22()
{
    if((snake_run22[snake_run22.size() - 1].x >= tuong2.x0 && snake_run22[snake_run22.size() - 1].x <= tuong2.x1 && (snake_run22[snake_run22.size() - 1].y == tuong2.y0 || snake_run22[snake_run22.size() - 1].y == tuong2.y1)) ||
       (snake_run22[snake_run22.size() - 1].y >= tuong2.y0 && snake_run22[snake_run22.size() - 1].y <= tuong2.y1 && (snake_run22[snake_run22.size() - 1].x == tuong2.x0 || snake_run22[snake_run22.size() - 1].x == tuong2.x1)) )
    {
        return true;
    }
    return false;
}
bool snake2::attack_wall23()
{
    if(snake_run2[snake_run2.size() - 1].x == tuong22.x0 && (snake_run2[snake_run2.size() - 1].y >= tuong22.y0 && snake_run2[snake_run2.size() - 1].y <= tuong22.y0 + (tuong22.y1 - tuong22.y0 + 1) / 3))
    {
        return true;
    }
    if(snake_run2[snake_run2.size() - 1].x == tuong22.x1 && (snake_run2[snake_run2.size() - 1].y >= tuong22.y0  && snake_run2[snake_run2.size() - 1].y <= tuong22.y0 + (tuong22.y1 - tuong22.y0 + 1) / 3))
    {
        return true;
    }
    if(snake_run2[snake_run2.size() - 1].x == tuong22.x0 && snake_run2[snake_run2.size() - 1].y <= tuong22.y1 && snake_run2[snake_run2.size() - 1].y >= tuong22.y1 - (tuong22.y1 - tuong22.y0 + 1) / 3)
    {
        return true;
    }
    if(snake_run2[snake_run2.size() - 1].x == tuong22.x1 && snake_run2[snake_run2.size() - 1].y <= tuong22.y1 && snake_run2[snake_run2.size() - 1].y >= tuong22.y1 - (tuong22.y1 - tuong22.y0 + 1) / 3)
    {
        return true;
    }
    if(snake_run2[snake_run2.size() - 1].y == tuong22.y0 && (snake_run2[snake_run2.size() - 1].x >= tuong22.x0 && snake_run2[snake_run2.size() - 1].x <= tuong22.x0 + (tuong22.x1 - tuong22.x0 + 1) / 3))
    {
        return true;
    }
    if(snake_run2[snake_run2.size() - 1].y == tuong22.y1 && (snake_run2[snake_run2.size() - 1].x >= tuong22.x0 && snake_run2[snake_run2.size() - 1].x <= tuong22.x0 + (tuong22.x1 - tuong22.x0 + 1) / 3))
    {
        return true;
    }
    if(snake_run2[snake_run2.size() - 1].y == tuong22.y0 && snake_run2[snake_run2.size() - 1].x <= tuong22.x1 && snake_run2[snake_run2.size() - 1].x >= tuong22.x1 - (tuong22.x1 - tuong22.x0 + 1) / 3)
    {
        return true;
    }
    if(snake_run2[snake_run2.size() - 1].y == tuong22.y1 && snake_run2[snake_run2.size() - 1].x <= tuong22.x1 && snake_run2[snake_run2.size() - 1].x >= tuong22.x1 - (tuong22.x1 - tuong22.x0 + 1) / 3)
    {
        return true;
    }
    return false;

}
bool snake2::attack_wall233()
{
    if(snake_run22[snake_run22.size() - 1].x == tuong22.x0 && (snake_run22[snake_run22.size() - 1].y >= tuong22.y0 && snake_run22[snake_run22.size() - 1].y <= tuong22.y0 + (tuong22.y1 - tuong22.y0 + 1) / 3))
    {
        return true;
    }
    if(snake_run22[snake_run22.size() - 1].x == tuong22.x1 && (snake_run22[snake_run22.size() - 1].y >= tuong22.y0  && snake_run22[snake_run22.size() - 1].y <= tuong22.y0 + (tuong22.y1 - tuong22.y0 + 1) / 3))
    {
        return true;
    }
    if(snake_run22[snake_run22.size() - 1].x == tuong22.x0 && snake_run22[snake_run22.size() - 1].y <= tuong22.y1 && snake_run22[snake_run22.size() - 1].y >= tuong22.y1 - (tuong22.y1 - tuong22.y0 + 1) / 3)
    {
        return true;
    }
    if(snake_run22[snake_run22.size() - 1].x == tuong22.x1 && snake_run22[snake_run22.size() - 1].y <= tuong22.y1 && snake_run22[snake_run22.size() - 1].y >= tuong22.y1 - (tuong22.y1 - tuong22.y0 + 1) / 3)
    {
        return true;
    }
    if(snake_run22[snake_run22.size() - 1].y == tuong22.y0 && (snake_run22[snake_run22.size() - 1].x >= tuong22.x0 && snake_run22[snake_run22.size() - 1].x <= tuong22.x0 + (tuong22.x1 - tuong22.x0 + 1) / 3))
    {
        return true;
    }
    if(snake_run22[snake_run22.size() - 1].y == tuong22.y1 && (snake_run22[snake_run22.size() - 1].x >= tuong22.x0 && snake_run22[snake_run22.size() - 1].x <= tuong22.x0 + (tuong22.x1 - tuong22.x0 + 1) / 3))
    {
        return true;
    }
    if(snake_run22[snake_run22.size() - 1].y == tuong22.y0 && snake_run22[snake_run22.size() - 1].x <= tuong22.x1 && snake_run22[snake_run22.size() - 1].x >= tuong22.x1 - (tuong22.x1 - tuong22.x0 + 1) / 3)
    {
        return true;
    }
    if(snake_run22[snake_run22.size() - 1].y == tuong22.y1 && snake_run22[snake_run22.size() - 1].x <= tuong22.x1 && snake_run22[snake_run22.size() - 1].x >= tuong22.x1 - (tuong22.x1 - tuong22.x0 + 1) / 3)
    {
        return true;
    }
    return false;
}
bool snake2::attack_wall_gun1(gun a)// va cham vao tuong ngoai thi tu bien mat va xoa dan do ra khoi vector
{
    if((a.x + a.tmp_x > tuong2.x0 && a.x + a.tmp_x < tuong2.x1 && (a.y + a.tmp_y == tuong2.y0 + 1 || a.y + a.tmp_y == tuong2.y1 - 1)) ||
       (a.y + a.tmp_y > tuong2.y0 && a.y + a.tmp_y < tuong2.y1 && (a.x + a.tmp_x == tuong2.x0 + 1 || a.x + a.tmp_x == tuong2.x1 - 1)) )
    {
	//dan1.erase(dan1.begin() + vtri);
        return true;
    }
    return false;

}
bool snake2::attack_wall_gun2(gun a)// va cham vao tuong ngoai thi tu bien mat va xoa dan do ra khoi vector
{
    if(a.x + a.tmp_x == tuong22.x0 + 1 && (a.y + a.tmp_y >= tuong22.y0 && a.y + a.tmp_y <= tuong22.y0 + (tuong22.y1 - tuong22.y0 + 1) / 3))
    {
        return true;
    }
    if(a.x + a.tmp_x == tuong22.x1 - 1 && (a.y + a.tmp_y >= tuong22.y0  && a.y + a.tmp_y <= tuong22.y0 + (tuong22.y1 - tuong22.y0 + 1) / 3))
    {
        return true;
    }
    if(a.x + a.tmp_x == tuong22.x0 + 1 && a.y + a.tmp_y <= tuong22.y1 && a.y + a.tmp_y >= tuong22.y1 - (tuong22.y1 - tuong22.y0 + 1) / 3)
    {
        return true;
    }
    if(a.x + a.tmp_x == tuong22.x1 - 1 && a.y + a.tmp_y <= tuong22.y1 && a.y + a.tmp_y >= tuong22.y1 - (tuong22.y1 - tuong22.y0 + 1) / 3)
    {
        return true;
    }
    if(a.y + a.tmp_y == tuong22.y0 + 1 && (a.x + a.tmp_x >= tuong22.x0 && a.x + a.tmp_x <= tuong22.x0 + (tuong22.x1 - tuong22.x0 + 1) / 3))
    {
        return true;
    }
    if(a.y + a.tmp_y == tuong22.y1 - 1 && (a.x + a.tmp_x >= tuong22.x0 && a.x + a.tmp_x <= tuong22.x0 + (tuong22.x1 - tuong22.x0 + 1) / 3))
    {
        return true;
    }
    if(a.y + a.tmp_y == tuong22.y0 + 1 && a.x + a.tmp_x <= tuong22.x1 && a.x + a.tmp_x >= tuong22.x1 - (tuong22.x1 - tuong22.x0 + 1) / 3)
    {
        return true;
    }
    if(a.y + a.tmp_y == tuong22.y1 - 1 && a.x + a.tmp_x <= tuong22.x1 && a.x + a.tmp_x >= tuong22.x1 - (tuong22.x1 - tuong22.x0 + 1) / 3)
    {
        return true;
    }
    return false;
}
bool snake2::attack_gun1(gun a)// ran 2 va cham voi 1 thanh vien trong ran1 hay khong
{
    for(int i = 0; i < snake_run22.size(); i++)
    {
        if(snake_run22[i].x == a.x && snake_run22[i].y == a.y) return true;
    }
    return false;
}
bool snake2::attack_gun2(gun a)// ran 1 va cham voi 1 thanh vien trong ran2 hay khong
{
    for(int i = 0; i < snake_run2.size(); i++)
    {
        if(snake_run2[i].x == a.x && snake_run2[i].y == a.y) return true;
    }
    return false;
}
void snake2::no_wall2()// di xuyen tuong
{
    if(snake_run2[snake_run2.size() - 1].y <= tuong2.y0) snake_run2[snake_run2.size() - 1].y = tuong2.y1 - 2;
    if(snake_run2[snake_run2.size() - 1].x <= tuong2.x0) snake_run2[snake_run2.size() - 1].x = tuong2.x1 - 2;
    if(snake_run2[snake_run2.size() - 1].x >= tuong2.x1 - 1) snake_run2[snake_run2.size() - 1].x = tuong2.x0 + 1;
    if(snake_run2[snake_run2.size() - 1].y >= tuong2.y1 - 1) snake_run2[snake_run2.size() - 1].y = tuong2.y0 + 1;
}
void snake2::no_wall22()// di xuyen tuong
{
    if(snake_run22[snake_run22.size() - 1].y <= tuong2.y0) snake_run22[snake_run22.size() - 1].y = tuong2.y1 - 2;
    if(snake_run22[snake_run22.size() - 1].x <= tuong2.x0) snake_run22[snake_run22.size() - 1].x = tuong2.x1 - 2;
    if(snake_run22[snake_run22.size() - 1].x >= tuong2.x1 - 1) snake_run22[snake_run22.size() - 1].x = tuong2.x0 + 1;
    if(snake_run22[snake_run22.size() - 1].y >= tuong2.y1 - 1) snake_run22[snake_run22.size() - 1].y = tuong2.y0 + 1;
}
bool snake2::attack_two()
{
    for(int i = 0; i < snake_run2.size(); i++)
    {
        for(int j = 0; j < snake_run22.size(); j++)
	{
	    if(snake_run2[i].x == snake_run22[j].x && snake_run2[i].y == snake_run22[j].y) return true;
	}
    }
    return false;
}
void snake2::print_score2()
{
    mvprintw(tuong2.y0 - 1, tuong2.x0, "SCORE1: %d", diem2.a1);
    refresh();
}
void snake2::print_score22()
{
    mvprintw(tuong2.y0 - 1, tuong2.x1 - 10, "SCORE2: %d", diem2.a2);
    refresh();
}
void snake2::Run2(char name1[100], char name2[100])
{
    nodelay(stdscr, TRUE);// tat che do cho cua ham getch;
    tuong2.print_wall();
    tuong22.print_wall();
    tuong22.print_wallx();
    print_score2(); print_score22();
    int tmp1 = 0, tmp2 = 0;
    //print_snake2(); print_snake22();
    int tmp11 = 0, tmp22 = 0;
    noecho(); curs_set(0);// tat nhap hien ki tu va con tro nhay
    vector<food> foo(5); bool kimtra1 = false, kimtra2 = false;
    vector<int> check_foo(5);
    for(int i = 0; i < 5; i++) check_foo[i] = 0;
    while(check_snake2 == true)
    {
        for(int i = 0; i < 5; i++)
        {
            if(check_foo[i] == 0)
            {
                if(i == 0){ foo[i].ramdom_food(tuong22.x0 + 1, tuong22.y0 + 1, tuong22.x1 - 1, tuong22.y1 - 1); check_foo[i] = 1;}
		else if(i == 1){foo[i].ramdom_food(tuong2.x0 + 1, tuong2.y0 + 1, tuong22.x1 - 1, tuong22.y0 - 1); check_foo[i] = 1;}
		else if(i == 2){foo[i].ramdom_food(tuong22.x1 + 1, tuong2.y0 + 1, tuong2.x1 - 1, tuong22.y1 - 1); check_foo[i] = 1;}
		else if(i == 3){foo[i].ramdom_food(tuong22.x0 + 1, tuong22.y1 + 1, tuong2.x1 - 1, tuong2.y1 - 1); check_foo[i] = 1;}
		else if(i == 4){foo[i].ramdom_food(tuong2.x0 + 1, tuong22.y0 + 1, tuong22.x0 - 1, tuong2.y1 - 1); check_foo[i] = 1;}
            }
        }
	// kiem tra dan va cham voi moi
	//for(int i = 0; i < 5; i++)
	//{
	//    if(check_foo[i] == 1)
	//    {
	//        
	//    }
	//}
        char c = getch();
	// nguoi choi 1
        if(c == 's')
        {
            tmp1 = 0; tmp2 = 1;
        }
        if(c == 'w')
        {
            tmp1 = 0; tmp2 = -1;
        }
        if(c == 'a')
        {
            tmp1 = -1; tmp2 = 0;
        }
        if(c == 'd')
        {
            tmp1 = 1; tmp2 = 0;
        }
	// nguoi choi 2
	if(c == 'k')
        {
            tmp11 = 0; tmp22 = 1;
        }
        if(c == 'i')
        {
            tmp11 = 0; tmp22 = -1;
        }
        if(c == 'j')
        {
            tmp11 = -1; tmp22 = 0;
        }
        if(c == 'l')
        {
            tmp11 = 1; tmp22 = 0;
        }
	if(c == 'f')// nguoi 1 nha dan
	{
            kimtra1 = true;
            gun hahax; hahax.set_gun(snake_run2[snake_run2.size() - 1].x, snake_run2[snake_run2.size() - 1].y, tmp1, tmp2, 'V'); dan1.push_back(hahax);
	}
	if(c == 'p')// nguoi 2 nha dan
        {
	    kimtra2 = true;
	    gun hahax; hahax.set_gun(snake_run22[snake_run22.size() - 1].x, snake_run22[snake_run22.size() - 1].y, tmp11, tmp22, 'V'); dan2.push_back(hahax);
	}
        if(c == 'q')
        {
            nodelay(stdscr, FALSE);
            clear();
	    cha x;
            if(diem2.a1 > diem2.a2) x.menu2(diem2.a1, name1, 2);
	    else x.menu2(diem2.a2, name2, 2);
            clear();
            tuong2.print_wall();tuong22.print_wall(); tuong22.print_wallx();
            for(int i = 0; i < 5; i++) check_foo[i] = 0;
            nodelay(stdscr, TRUE);
        }
        Body new_body;
	Body new_body1x;
        //this->no_wall0();// di xuyen tuong
        new_body.set_body(snake_run2[snake_run2.size() - 1].x + 1 * tmp1, snake_run2[snake_run2.size() - 1].y + 1 * tmp2, char_body2);
	new_body1x.set_body(snake_run22[snake_run22.size() - 1].x + 1 * tmp11, snake_run22[snake_run22.size() - 1].y + 1 * tmp22, char_body22);
        if(tmp1 == 0 && tmp2 == 0 && tmp11 == 0 & tmp22 == 0)
        {
            print_snake2();
	    print_snake22();
            usleep(90000 + kho);
            delete_snake2();
	    delete_snake22();
        }
        else
        {
            snake_run2.push_back(new_body);
	    snake_run22.push_back(new_body1x);
            snake_run2.erase(snake_run2.begin());
	    snake_run22.erase(snake_run22.begin());
            print_snake2();
	    print_snake22();
            for(int i = 0; i < 5; i++)
            {
                if(this->attack2(foo[i]) == true)
                {
                    check_foo[i] = 0;
                    diem2.a1++;// tang diem
                    // them 1 body tang do fai cho ran
                    Body new_body11; new_body11.set_body(snake_run2[0].x - 1, snake_run2[0].y, char_body2);// can kiem tra xem chieu di cua body cuoi khong ????
                    snake_run2.insert(snake_run2.begin(), new_body11);
                }
		if(this->attack22(foo[i]) == true)
		{
		    check_foo[i] = 0;
                    diem2.a2++;// tang diem
                    // them 1 body tang do fai cho ran
                    Body new_body11; new_body11.set_body(snake_run22[0].x - 1, snake_run22[0].y, char_body22);// can kiem tra xem chieu di cua body cuoi khong ????
                    snake_run22.insert(snake_run22.begin(), new_body11);
		}
	
            }
	    if(kimtra1 == true)
	    {
	        for(int i = 0; i < dan1.size(); i++)
		{
	            dan1[i].set_gun(dan1[i].x + dan1[i].tmp_x, dan1[i].y + dan1[i].tmp_y, dan1[i].tmp_x, dan1[i].tmp_y, '1');
		    dan1[i].print_gun();
		}
	    }
	    if(kimtra2 == true)
	    {
	        for(int i = 0; i < dan2.size(); i++)
		{
		    dan2[i].set_gun(dan2[i].x + dan2[i].tmp_x, dan2[i].y + dan2[i].tmp_y, dan2[i].tmp_x, dan2[i].tmp_y, '2');
                    dan2[i].print_gun();
		}
	    }
            if(this->attack_wall2() == true)
            {
                this->no_wall2();
                tuong2.print_wall();
            }
	    if(this->attack_wall22() == true)
	    {
	        this->no_wall22();
		tuong2.print_wall();
	    }
	    //bool dinhdan1 = false; bool dinhdan2 = false;
	    for(int i = 0; i < dan1.size(); i++)
	    {
	        if(this->attack_gun1(dan1[i]) == true)
		{
		    //dinhdan2 = true// tuc nguoi choi 2 bi trung dan cua nguoi choi 1
		    clear();
                    mvprintw(ma_y / 3 + 1, ma_x / 3 + ma_x / 7, "NGUOI CHOI 1 WIN la: %s", name1); refresh(); sleep(2);
                    hs.get_highscore(diem2.a1, name1, 2);
                    nodelay(stdscr, FALSE);
                    cha x; x.menu1();
		}
	    }
	    for(int i = 0; i < dan2.size(); i++)
	    {
	        if(this->attack_gun2(dan2[i]) == true)
		{
		    //dinhdan1 = true;// tuc nguoi choi 1 bi trung dan cua nguoi choi 2
		    clear();
                    mvprintw(ma_y / 3 + 1, ma_x / 3 + ma_x / 7, "NGUOI CHOI 2 WIN la: %s", name2);refresh(); sleep(2);
                    hs.get_highscore(diem2.a2, name2, 2);
                    nodelay(stdscr, FALSE);
		    cha x; x.menu1();

		}
	    }
	    if(this->attack_two() == true)
	    {
		if(snake_run2[0].x == snake_run22[0].x && snake_run2[0].y == snake_run22[0].y)
		{
		    clear();
		    mvprintw(ma_y / 3 + 1, ma_x / 3 + ma_x / 7, "KET QUA HOA"); refresh(); sleep(2);
		    nodelay(stdscr, FALSE);
                    cha x; x.menu1();
		}
		else
		{
		for(int i = 0; i < snake_run22.size(); i++)
		{
		    if(snake_run22[i].x == snake_run2[snake_run2.size() - 1].x && snake_run22[i].y == snake_run2[snake_run2.size() - 1].y)
		    {
			clear();
		        mvprintw(ma_y / 3 + 1, ma_x / 3 + ma_x / 7, "NGUOI CHOI 2 WIN la: %s", name2);refresh(); sleep(2);
			hs.get_highscore(diem2.a2, name2, 2);
                        nodelay(stdscr, FALSE);
                        cha x; x.menu1();
		    }
		}
		for(int i = 0; i < snake_run2.size(); i++)
                {
                    if(snake_run2[i].x == snake_run22[snake_run22.size() - 1].x && snake_run2[i].y == snake_run22[snake_run22.size() - 1].y)
                    {
                        clear();
                        mvprintw(ma_y / 3 + 1, ma_x / 3 + ma_x / 7, "NGUOI CHOI 1 WIN la: %s", name1); refresh(); sleep(2); 
			hs.get_highscore(diem2.a1, name1, 2);
		        nodelay(stdscr, FALSE);
                        cha x; x.menu1();
	
                    }
                }
		}
	    }
	    if(this->attack_wall23() == true)
	    {
		clear();
                mvprintw(ma_y / 3 + 1, ma_x / 3 + ma_x / 7, "NGUOI CHOI 2 WIN la: %s", name2);refresh(); sleep(2); 
	        hs.get_highscore(diem2.a2, name2, 2);
	        nodelay(stdscr, FALSE);
		cha x; x.menu1();
	    }
	    if(this->attack_wall233() == true)
	    {
		clear();
                mvprintw(ma_y / 3 + 1, ma_x / 3 + ma_x / 7, "NGUOI CHOI 1 WIN la: %s", name1); refresh(); sleep(2);
		hs.get_highscore(diem2.a1, name1, 2);
	        nodelay(stdscr, FALSE);
		cha x; x.menu1();
	    }
            //if(this->attack_wall01() == true)
            //{
            //    hs.get_highscore(diem0, name);
            //    nodelay(stdscr, FALSE);
            //    cha x; x.menu1();
            //}
            usleep(90000 + kho);
            delete_snake2();
	    delete_snake22();
	    if(kimtra1 == true)
	    {
	        for(int i = 0; i < dan1.size(); i++)
	        {
	            dan1[i].delete_gun();
	        }
	    }
	    if(kimtra2 == true)
            {
                for(int i = 0; i < dan2.size(); i++)
                {
                    dan2[i].delete_gun();
                }
            }
	    // xoa bo dan trung tuong thuong
	    int bi1 = 0, bi2 = 0;
            while(bi1 < (int)dan1.size())
	    {
	        if(this->attack_wall_gun1(dan1[bi1]) == true)
		{
		    dan1.erase(dan1.begin() + bi1);
		}
		else 
		{
		    bi1++;
		}
	    }
	    while(bi2 < (int)dan2.size())
            {
                if(this->attack_wall_gun1(dan2[bi2]) == true)
                {
                    dan2.erase(dan2.begin() + bi2);
                }
                else
                {
                    bi2++;
                }
            }
	    int bi11 = 0, bi22 = 0;
	    while(bi11 < (int)dan1.size())
	    {
	        if(this->attack_wall_gun2(dan1[bi11]) == true)
		{
		    dan1.erase(dan1.begin() + bi11);
		}
		else
		{
		    bi11++;
		}
	    }
	    while(bi22 < (int)dan2.size())
            {
                if(this->attack_wall_gun2(dan2[bi22]) == true)
                {
                    dan2.erase(dan2.begin() + bi22);
                }
                else
                {
                    bi22++;
                }
            }
        }
        print_score2();
	print_score22();
    }
    nodelay(stdscr, FALSE);
}
void cha::menu()
{
    clear();
    mvprintw(ma_y / 3 - 1, ma_x / 3 + (ma_x / 7), "GAME SNAKE");
    refresh();
    wall tuong; tuong.set_wall(ma_x / 3, ma_y / 3, 2 * ma_x / 3, 2 * ma_y / 3, '*');
    tuong.print_wall();
    mvprintw(ma_y / 3 + 2, ma_x / 3 + 1, "   SELECT MODE");
    refresh();
    mvprintw(ma_y / 3 + 3, ma_x / 3 + 1, "");
    refresh();
    mvprintw(ma_y / 3 + 4, ma_x / 3 + 1, "   HIGH SCORE");
    refresh();
    mvprintw(ma_y / 3 + 5, ma_x / 3 + 1, "");
    refresh();
    mvprintw(ma_y / 3 + 6, ma_x / 3 + 1, "   HOW PLAY");
    refresh();
    mvprintw(ma_y / 3 + 7, ma_x / 3 + 1, "");
    refresh();
    mvprintw(ma_y / 3 + 8, ma_x / 3 + 1, "   EXIT(ESC)");
    refresh();
    mvprintw(ma_y / 3 + 2, ma_x / 3 + 1, "->");
    refresh();
    int check_y = ma_y / 3 + 2, check_x = ma_x / 3 + 1;
    while(1)
    {
        char ok; ok = getch();
	if(ok == '\n')
	{
	    if(check_y == ma_y / 3 + 2)
	    {
	        menu1();
	    }
	    else if(check_y == ma_y / 3 + 4)
	    {
	        clear();
		wall tung; tung.set_wall(ma_x / 3, ma_y / 3, 2 * ma_x / 3, 5 * ma_y / 6, '*');
                tung.print_wall();
		mvprintw(ma_y / 3 + 4 , ma_x / 3 + ma_x / 7, "TOP SERVER ONE");
		refresh();
		mvprintw(ma_y / 3 + 6, ma_x / 3 + ma_x / 7, "");
		refresh();
	        int diemm; char okx[100];
	        fstream filex; filex.open("diem_one.txt", ios::in | ios::out);	
		if(filex.is_open())
		{
		   filex.seekg(0, ios::beg);
		   filex >> diemm;
		   filex.ignore();
		   filex.getline(okx, 100);
		   filex.close();  
		}
		mvprintw(ma_y / 3 + 8, ma_x / 3 + ma_x / 7, "NAME: %s SCORE: %d", okx, diemm);
		refresh();
		mvprintw(ma_y / 3 + 10, ma_x / 3 + ma_x / 7, "");
		refresh();
		mvprintw(ma_y / 3 + 12, ma_x / 3 + ma_x / 7, "TOP SEVER TWO");
		refresh();
		mvprintw(ma_y / 3 + 14, ma_x / 3 + ma_x / 7, "");
		refresh();
		int diemm1; char okx1[100];
		fstream filex1; filex1.open("diem_two.txt", ios::in | ios::out);
		if(filex1.is_open())
		{
		    filex1.seekg(0, ios::beg);
		    filex1 >> diemm1;
		    filex1.ignore();
		    filex1.getline(okx1, 100);
		    filex1.close();
		}
		mvprintw(ma_y / 3 + 16, ma_x / 3 + ma_x / 7, "WINNER %s SCORE: %d", okx1, diemm1);
		refresh();
		mvprintw(ma_y / 3 + 18, ma_x / 3 + ma_x / 7, "");
		refresh();
		mvprintw(ma_y / 3 + 20, ma_x /3 + ma_x / 7, "   RETURN");
		refresh();
		mvprintw(ma_y / 3 + 20, ma_x / 3 + ma_x / 7, "->");
		refresh();
		while(1)
		{
		    char get = getch();
		    if(get == '\n')
		    {
			clear();
		        cha xx; xx.menu1();
	
		    }
		}
		
	    }
	    else if(check_y == ma_y / 3 + 8)
	    {
		endwin();// thoat game
		exit(0);
	    }
	}// kiem tra xem neu nguoi dung co bam enter luon khong
	else if(ok == 's')
	{
            if(check_y == ma_y / 3 + 8)
	    {
		mvprintw(check_y, check_x, "  ");
		check_y += 2; check_y -= 8;
                mvprintw(check_y, check_x, "->");
                refresh();
	    }
	    else
	    {
	        mvprintw(check_y, check_x, "  "); 
	        check_y += 2; 
	        mvprintw(check_y, check_x, "->"); 
	        refresh();
	    }
	}
	else if(ok == 'w')
	{
	    if(check_y == ma_y / 3 + 2)
	    {
		mvprintw(check_y, check_x, "  ");
	        check_y -= 2; check_y += 8;
                mvprintw(check_y, check_x, "->");
                refresh();
	    }
	    else
	    {
	        mvprintw(check_y, check_x, "  "); 
	        check_y -= 2; 
	        mvprintw(check_y, check_x, "->"); 
	        refresh(); 
	    }
	}
    }

}
void cha::menu1()
{
    clear();
    mvprintw(ma_y / 3 - 1, ma_x / 3 + (ma_x / 7), "GAME SNAKE");
    refresh();
    wall tuong; tuong.set_wall(ma_x / 3, ma_y / 3, 2 * ma_x / 3, 2 * ma_y / 3, '*');
    tuong.print_wall();
    mvprintw(ma_y / 3 + 1, ma_x / 3 + 1, "");
    refresh();
    mvprintw(ma_y / 3 + 2, ma_x / 3 + 1, "   GAME ONE PERSON");
    refresh();
    mvprintw(ma_y / 3 + 3, ma_x / 3 + 1, "");
    refresh();
    mvprintw(ma_y / 3 + 4, ma_x / 3 + 1, "   GAME TWO PERSON");
    refresh();
    mvprintw(ma_y / 3 + 5, ma_x / 3 + 1, "");
    refresh();
    mvprintw(ma_y / 3 + 6, ma_x / 3 + 1, "   RETURN");
    refresh();
    mvprintw(ma_y / 3 + 2, ma_x / 3 + 1, "->");
    refresh();
    int check_y = ma_y / 3 + 2, check_x = ma_x / 3 + 1;
    while(1)
    {
        char ok; ok = getch();
	if(ok == '\n')
	{
	    if(check_y == ma_y / 3 + 6)
	    {
	        menu();
	    }
	    else if(check_y == ma_y / 3 + 2)
	    {
		clear();
		echo();
		char name[100];
		mvprintw(ma_y / 3 + 5, ma_x / 3 + ma_x / 10, "NHAP VAO TEN NGUOI CHOI: "); refresh();
	        getstr(name);
	        clear();	
		noecho();
		//check_map1 = true; 
		check_map0 = true;
	        snake0 ran0; ran0.Run0(name); 
	    }
	    else if(check_y == ma_y / 3 + 4)
	    {
	        clear();
		echo();
		char name1[100];
		char name2[100];
		mvprintw(ma_y / 3 + 5, ma_x / 3 + ma_x / 10, "NHAP VAO TEN NGUOI CHOI THU NHAT: "); refresh();
		getstr(name1);
		clear();
		mvprintw(ma_y / 3 + 5, ma_x / 3 + ma_x / 10, "NHAP VAO TEN NGUOI CHOI THU HAI: "); refresh();
		getstr(name2);
		clear();
		noecho();
		snake2 ran2; ran2.Run2(name1, name2);
	    }
	}
        if(ok == 's')
        {
            if(check_y == ma_y / 3 + 6)
            {
                mvprintw(check_y, check_x, "  ");
                check_y += 2; check_y -= 6;
                mvprintw(check_y, check_x, "->");
                refresh();
            }
            else
            {
                mvprintw(check_y, check_x, "  ");
                check_y += 2;
                mvprintw(check_y, check_x, "->");
                refresh();
            }
        }
        if(ok == 'w')
        {
            if(check_y == ma_y / 3 + 2)
            {
                mvprintw(check_y, check_x, "  ");
                check_y -= 2; check_y += 6;
                mvprintw(check_y, check_x, "->");
                refresh();
            }
            else
            {
                mvprintw(check_y, check_x, "  ");
                check_y -= 2;
                mvprintw(check_y, check_x, "->");
                refresh();
            }
        }
    }
 
}
void cha::menu2(int diem0, char name[100], int hoi)
{
    clear();
    //mvprintw(10, 10, "%d", diem0.a1);
    //refresh();
    //sleep(10);
    mvprintw(ma_y / 3 - 1, ma_x / 3 + (ma_x / 7), "GAME SNAKE");
    refresh();
    wall tuong; tuong.set_wall(ma_x / 3, ma_y / 3, 2 * ma_x / 3, 2 * ma_y / 3, '*');
    tuong.print_wall();
    mvprintw(ma_y / 3 + 1, ma_x / 3 + 1, "");
    refresh();
    mvprintw(ma_y / 3 + 2, ma_x / 3 + 1, "");
    refresh();
    mvprintw(ma_y / 3 + 3, ma_x / 3 + 1, "");
    refresh();
    mvprintw(ma_y / 3 + 4, ma_x / 3 + ma_x / 10, "   ARE YOU CONTINUE");
    refresh();
    mvprintw(ma_y / 3 + 5, ma_x / 3 + 1, "");
    refresh();
    mvprintw(ma_y / 3 + 6, ma_x / 3 + ma_x / 10, "   NO");
    refresh();
    mvprintw(ma_y / 3 + 7, ma_x / 3 + 1, "");
    refresh();
    mvprintw(ma_y / 3 + 8, ma_x / 3 + ma_x / 10, "   YES");
    refresh();
    mvprintw(ma_y / 3 + 6, ma_x / 3 + ma_x / 10, "->");
    refresh();
    int check_y = ma_y / 3 + 6, check_x = ma_x / 3 + ma_x / 10;
    while(1)
    {
        char ok; ok = getch();
        if(ok == '\n')
        {
            if(check_y == ma_y / 3 + 6)
            {
		hs.get_highscore(diem0, name, hoi);// dien ten va diem nguoi choi cao nhat
                cha next; next.menu1();
            }
            else if(check_y == ma_y / 3 + 8)
            {
		break;
            }

        }
        if(ok == 's')
        {
            if(check_y == ma_y / 3 + 8)
            {
                mvprintw(check_y, check_x, "  ");
                check_y -= 2;
                mvprintw(check_y, check_x, "->");
                refresh();
            }
            else
            {
                mvprintw(check_y, check_x, "  ");
                check_y += 2;
                mvprintw(check_y, check_x, "->");
                refresh();
            }
        }
        if(ok == 'w')
        {
            if(check_y == ma_y / 3 + 6)
            {
                mvprintw(check_y, check_x, "  ");
                check_y += 2;
                mvprintw(check_y, check_x, "->");
                refresh();
            }
            else
            {
                mvprintw(check_y, check_x, "  ");
                check_y -= 2;
                mvprintw(check_y, check_x, "->");
                refresh();
            }
        }
    }

}
void task2()
{
    ofstream file("diem_one.txt");
    file.close();
    ofstream filex("diem_two.txt");
    filex.close();
    initscr();
    srand(time(0));
    noecho();
    curs_set(0);
    keypad(stdscr, true);
    getmaxyx(stdscr,ma_y, ma_x);
    cha game;
    game.menu();
    endwin();
}

