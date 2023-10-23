#ifndef GAMERAN_H
#define GAMERAN_H
#include<iostream>
#include<curses.h>
#include<vector>
#include<string.h>
#include<unistd.h>
#include<ctime>
#include<map>
#include<fstream>
using namespace std;
class Body
{
public:
    int x, y;
    char c;
    Body(){x = 0; y = 10; c = 'o';}
    Body(int x_demo, int y_demo, char m){x = x_demo; y = y_demo; c = m;}
    void set_body(int x_demo, int y_demo, char c_demo);
    ~Body(){}
};

class food
{
public:
    friend class wall;
    int x; int y;
    char c;
    vector<string> best_food =
    {
    " 000",
    "00000",
    " 000"
    };
    int vtri_x = 0, vtri_y = 0;// vi tri in ra cua best food
    food(){x = 0; y = 0; c = 'Q';}
    void set_food(int x_demo, int y_demo, char c_demo);
    void print_best();
    void delete_best();
    void ramdom_food();
    void ramdom_food(int x0, int y0, int x1, int y1);
    void ramdom_food(int x0, int y0, int x1, int y1, int x0m, int y0m, int x1m, int y1m);// ramdom o map 0
    void ramdom_best_food();
    void ramdom_best_food(int x0, int y0, int x1, int y1);
    void delete_best_food();
    void delete_best_food0();
    void delete_best_food1();
    ~food(){}
};
class gun
{
public:
    int x = 10, y = 10;
    int tmp_x = 0, tmp_y = 0;
    char c = 'O';
    gun();
    void set_gun(int x0, int y0, int tmp_x0, int tmp_y0, char c);
    void print_gun();
    void delete_gun();
    ~gun(){}
};

class score
{
public:
    int a1, a2;
    //fstream file;
    score(){a1 = 0; a2 = 0;}
    ~score(){}
};
class highscore
{
public:
    highscore(){}
    void get_highscore(int diem0, char name[100], int hoi);
    ~highscore(){}
};
class wall
{
public:
    friend class food;
    int x0, y0, x1, y1; char ktu;
    wall();
    void set_wall(int x00, int y00, int x11, int y11, char ktu1);
    void print_wall();// in tuong
    void print_wallx();// in tuong dac biet
    ~wall(){}
};
class hole
{
public:
    vector<string> hd
    {
    "***********",
    "*DARK_HOLE*",
    "***********"
    };
    int x, y;
    hole();
    void print_hole();// tao loi thoat
    ~hole(){}
};
class cha
{
public:
    bool Stop = false;
    void in(int x, int y);
    void menu();
    void menu1();
    void menu2(int diem0, char name[100], int hoi);
    void menu3();
};
// RAN O MAP 2
class snake1
{
public:
    int level = 1;
    int difficult = 100000;
    score diem1;
    wall tuong1;
    wall tuong11;
    wall tuong111;
    hole den1;
    int kho = 0;
    bool check_snake1 = false;
    char char_body1 = 'O';
    vector<Body> snake_run1;
    snake1();
    void print_snake1();// in trang thai cua ran
    void delete_snake1();// xoa trang thai cua ran
    bool attack1(food place_food);// tan cong moi
    bool attack_best1(food place_food);// tan cong moi dac biet
    bool attack_wall1();// dam vao tuong
    bool attack_hole1();
    //void no_wall1();//di xuyen tuong
    void Run1(char name[100]);// chay ran
    void print_score1();// in diem
    void setup_data1();// dua ve trang thai ban dau cua game
    void end_game1();// ket thuc tro choi
    ~snake1(){}
};
// RAN O MAP 1
class snake0
{
public:
    int level = 1;
    int difficult = 100000;
    score diem0;
    wall tuong0;
    wall tuong01;
    hole den1;
    int limit_score = 0;
    int kho = 0;
    bool check_snake0 = false;
    char char_body0 = 'O';
    vector<Body> snake_run0;
    snake0();
    void print_snake0();// in trang thai cua ran
    void delete_snake0();// xoa trang thai cua ran
    bool attack0(food place_food);// tan cong moi
    bool attack_best0(food place_food);// tan cong moi dac biet
    bool attack_wall0();// dam vao tuong
    bool attack_wall01();// dam vao tuong dac biet
    void no_wall0();//di xuyen tuong
    void Run0(char name[100]);// chay ran
    bool attack_hole1();
    void print_score0();// in diem
    void setup_data0();// dua ve trang thai ban dau cua game
    void end_game0();// ket thuc tro choi
    ~snake0(){}
};
// 2 nguoi choi
class snake2
{
public:
    score diem2;
    wall tuong2;
    wall tuong22;
    vector<gun> dan1;
    vector<gun> dan2;
    int kho = 0;
    bool check_snake2 = false;
    bool check_snake22 = false;
    char char_body2 = 'O';
    char char_body22 = 'X';
    vector<Body> snake_run2;
    vector<Body> snake_run22;
    snake2();
    void print_snake2();// in trang thai cua ran
    void delete_snake2();// xoa trang thai cua ran
    void print_snake22();
    void delete_snake22();
    bool attack2(food place_food);// tan cong moi 
    bool attack22(food place_food);
    bool attack_best2(food place_food);// tan cong moi dac biet
    bool attack_wall2();// dam vao tuong
    bool attack_wall22();
    bool attack_wall23(); // dam vao tuong dac biet
    bool attack_wall233();//
    bool attack_two();// hai ran dam nhau 
    bool attack_gun1(gun a);// ran 2 va cham voi 1 thanh vien trong vector dan1 khong 
    bool attack_gun2(gun a);// ran 1 va cham voi 1 thanh vien trong vector dan2 khong
    bool attack_wall_gun1(gun a);// va cham vao vien 
    bool attack_wall_gun2(gun a);// va cham vao tuong dac biet
    bool attack_gun_wall(int x0, int y0, int x1, int y1, int x00, int y00, int x11, int y11);// kiem tra dan va cham voi tuong
    void no_wall2();//di xuyen tuong
    void no_wall22();
    void Run2(char name1[100], char name2[100]);// chay ran
    void print_score2();// in diem
    void print_score22();
    void setup_data2();// dua ve trang thai ban dau cua game
    void setup_data22();
    void end_game2();// ket thuc tro choi
    void end_game22();
    ~snake2(){}
};
void task2();
#endif
