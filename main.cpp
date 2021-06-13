// Nicole Kurtz
// The Game of Life
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <cctype>
#include <string.h>
#include <random>
#include <time.h>

using namespace std;

/*
int width = 5;
int height = 5;
*/
struct node
{
	node * next; 
	node * head;
	int data;
};

struct Point
{
	int x;
	int y;
};

void random_state(int &width, int& height);
void display(node * array[], int width, int height);
void next_board_state(node ** array, int& width, int &height);
void test(int width, int height);
void import(int & width, int & height);

int main()
{
	int width = 0;
	int height = 0;
	system("clear");
	//random_state(width, height);
	//test(width, height);
	import(width, height);
	return 0;
}

void import(int & width, int & height)
{
	//const char infile[] = "toad.txt";
	const char infile[] = "ggg.txt";

	ifstream file_in;
	file_in.open(infile);
	node ** array;

	if(!file_in)
		return;
	
	if(file_in)
	{
		string line;
		while(getline(file_in,line))
		{
			++height;
			width = line.length();
		}
	}

	array = new node*[height];
	for(int i = 0; i < height; ++i)
	{
		array[i] = new node;
		array[i]->head = new node[width];
	}
	file_in.close();
	file_in.open(infile);

	if(file_in)
	{
		int k = 0;
		while(k < height)
		{
			string line;
			getline(file_in, line);
			for(int i = 0; i < width; ++i)
			{
				array[k]->head[i].data = (((int)(line[i])) - 48);
			}
			++k;
		}
	}

	file_in.close();
	display(array, width, height);
	next_board_state(array, width, height);


}

void random_state(int &width, int& height)
{
	srand (time(NULL));
	node ** array = new node*[height];	
	for(int i = 0; i < height; ++i)
	{
		array[i] = new node;
		array[i]->head = new node[width];
		for(int j = 0; j < width; ++j)
		{
			array[i]->head[j].data = rand() % 2;
		}
	}
	
	display(array, width, height);
	next_board_state(array, width, height);
	int counter = 1;
}

void next_board_state(node ** array, int &width, int& height)
{
	node ** new_board = new node*[height];

	// create new board
	for(int i = 0; i < height; ++i)
	{
		new_board[i] = new node;
		new_board[i]->head = new node[width];
	}

	// coordinate system
	Point grid[8] = { {-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1} };
	int neighbor_count;

	for(int i = 0; i < height; ++i)
	{
		for(int j = 0; j < width; ++j)
		{
			neighbor_count = 0;

			for(int cell = 0; cell < 8; ++cell)
			{
				if((j + grid[cell].x >= 0) && (i + grid[cell].y >= 0) && (i + grid[cell].y < height) 
				&& (j + grid[cell].x < width))
				{
					neighbor_count += array[(i + grid[cell].y)]->head[(j + grid[cell].x)].data;
				}
			}

			if((neighbor_count <= 1 || neighbor_count > 3) && array[i]->head[j].data)
			{
				new_board[i]->head[j].data = 0;
			}
			else if(neighbor_count == 3 && (!array[i]->head[j].data))
			{
				new_board[i]->head[j].data = 1;
			}
			else
			{
				new_board[i]->head[j].data = array[i]->head[j].data;
			}

		}
	}
	display(new_board, width, height);
	next_board_state(new_board, width, height);
}

void display(node ** array, int width, int height)
{
	for(int i = 0; i < height; ++i)
	{
		for(int j = 0; j < width; ++j)
		{
			if(array[i]->head[j].data)
				cout << "#" << flush;
			else
				cout << " " << flush;
		}
		cout << endl;
	}
	sleep(1);
	system("clear");
}
