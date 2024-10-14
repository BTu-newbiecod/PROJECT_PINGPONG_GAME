#include<iostream>
#include "raylib.h"
using namespace std;

Color Green = Color{ 38,185,154,255 };
Color Dark_Green = Color{ 20,160,133,255 };
Color Light_Green = Color{ 29,204,184,255 };
Color Yellow = Color{ 243 ,213,91,255 };


//khoi tao bien diem

int cpu_point=0, player_point=0;

//khoi tao lop Ball
class Ball 
{
//thuoc tinh
public:
	float x, y;
	int speed_x, speed_y;
	int radius;

//phuong thuc
void Draw()
{
	DrawCircle(x, y, radius, Yellow);
}

void Update()
{
	x += speed_x;
	y += speed_y;

	//CheckColision_wall
	if (y + radius >= GetScreenHeight() || y - radius <= 0)
	{
		speed_y *= -1;
	}
	if (x + radius >= GetScreenWidth())
	{
		cpu_point++;
		ResetBall();
	}

	if (x - radius <= 0)
	{
		player_point++;
		ResetBall();
	}
}

//RESET KHI AI DO GHI DIEM
void ResetBall()
{
	x = GetScreenWidth() / 2;
	y = GetScreenHeight() / 2;

	int speed_choice[2] = { -1,1 };
	speed_x *= speed_choice[GetRandomValue(0, 1)];
	speed_y *= speed_choice[GetRandomValue(0, 1)];
}
};

//khoi tao lop
class Paddle
{

//thuoc tinh
public:
	float x, y;
	float width, height;
	int speed;


//phuong thuc
	void Draw()
	{
		DrawRectangle(x,y, width, height, WHITE);
	}
	
	void Update()
	{
		if (IsKeyDown(KEY_UP))
		{
			y = y - speed;
		}
		if (IsKeyDown(KEY_DOWN))
		{
			y = y + speed;
		}

		//check gioi han di chuyen paddle player
		if (y <= 0)
			y = 0;
		if (y + height >= GetScreenHeight())
			y = GetScreenHeight() - height;
	}

};

//tao lop CpuPaddle ke thua tu lop Paddle
class CpuPaddle : public Paddle
{
public:

	//ghi de phuong thuc Update
	void Update(int ball_y)
	{
		if (y + height / 2 >= ball_y)
			y -= speed;
		if (y + height / 2 < ball_y)
			y += speed;

		//check gioi han di chuyen paddle cpu
		if (y <= 0)
			y = 0;
		if (y + height >= GetScreenHeight())
			y = GetScreenHeight() - height;
		
	}

	
};

Ball ball;
Paddle player;
CpuPaddle cpu;

int main()
{
	const int screen_width = 1280;
	const int screen_height = 800;
	InitWindow(screen_width, screen_height, "PING_PONG--GAME");

	//SetFPS to make slow
	SetTargetFPS(70);

	//khoi tao gia tri ban dau ball
	ball.radius = 20;
	ball.x = screen_width / 2;
	ball.y = screen_height / 2;
	ball.speed_x = 7;
	ball.speed_y = 7;

	//khoi tao gia tri ban dau paddle player
	player.width = 25;
	player.height = 120;
	player.x = GetScreenWidth() - 10 - player.width;
	player.y = GetScreenHeight() / 2 - player.height / 2;
	player.speed = 6;

	//khoi tao gia tri ban dau cpu
	cpu.width = 25;
	cpu.height = 120;
	cpu.x = 10;
	cpu.y = screen_height / 2 - cpu.height / 2;
	cpu.speed = 6;



	while (WindowShouldClose() == false)
	{

		BeginDrawing();

		//Update
		ball.Update();
		player.Update();
		cpu.Update(ball.y);

		//check_Collision_paddle
		if (CheckCollisionCircleRec(Vector2{ ball.x,ball.y }, ball.radius, Rectangle{ player.x,player.y,player.width,player.height }))
			ball.speed_x*= -1;

		if (CheckCollisionCircleRec(Vector2{ ball.x,ball.y }, ball.radius, Rectangle{ cpu.x,cpu.y,cpu.width,cpu.height }))
			ball.speed_x *= -1;

		
		//Drawing
		ClearBackground(Dark_Green); //To den cua so
		DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, Light_Green);
		DrawRectangle(0 ,0, screen_width / 2, screen_height, Dark_Green);
		DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);

		ball.Draw();
		cpu.Draw();
		player.Draw();

		//HIEN DIEM
		DrawText(TextFormat("NPC:%i", cpu_point), screen_width / 4 - 20, 20, 80, WHITE);
		DrawText(TextFormat("Me:%i", player_point), (screen_width / 4)*3 - 20, 20, 80, WHITE);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
