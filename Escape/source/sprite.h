#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <3ds.h>
#include <sf2d.h>
#include <vector>

class sprite
{
	int x, y, width, height;
	std::vector<int> R;
	std::vector<int> G;
	std::vector<int> B;
	std::vector<int> A;
	double Scale;
public:

	/**
	* brief: set values for sprite [DO THIS BEFORE USING SPRITE FOR ANYTHING]
	* param: ix: X Coordinate (integer)
	* param: iy: Y Coordinate
	* param: iR: int vector containing hex/int values for Red color channel
	* param: iG: int vector containing hex/int values for Green color channel
	* param: iB: int vector containing hex/int values for Blue color channel
	* param: iA: int vector containing hex/int values for Alpha color channel
	* param: iwidth: width of sprite (integer)
	* param: iheight: height of sprite (integer)
	* param: iscale: scale of sprite (double)
	*/
	void set(int ix, int iy, std::vector<int> iR, std::vector<int> iG, std::vector<int> iB, std::vector<int> iA, int iwidth, int iheight, double iscale)
	{
		x = ix;
		y = iy;
		R.insert(R.end(), iR.begin(), iR.end());
		G.insert(G.end(), iG.begin(), iG.end());
		B.insert(B.end(), iB.begin(), iB.end());
		A.insert(A.end(), iA.begin(), iA.end());
		width = iwidth;
		height = iheight;
		Scale = iscale;
	}

	/**
	* brief: returns X coordinate
	*/
	int getX()
	{
		return x;
	}

	/**
	* brief: returns Y coordinate
	*/
	int getY()
	{
		return y;
	}

	/**
	* brief: sets sprite position (intended for use with an object)
	* param: a: X (integer)
	* param: b: Y (integer)
	*/
	void setPosition(int a, int b)
	{
		x = a;
		y = b;
	}

	/**
	* brief: changes sprites scale
	* param: n: new scale value (double)
	*/
	void scale(double n)
	{
		Scale = n;
	}

	/**
	* brief: draws the sprite
	* param: relative_x: sprite's x coordinate offset
	* param: relative_y: sprite's y coordinate offset
	* offset's usually used for 3D effect
	*/
	void draw(int relative_x, int relative_y);
};

extern sprite spr_Null;
extern sprite spr_Geno;
extern sprite spr_Goblin;

class obj_Player {
	sprite private_sprite;
	bool private_exists;
	int private_scale;
public:

	/**
	* brief: set's Player's [default] values [USE THIS BEFORE USING THE PLAYER OBJECT]
	* param: set_sprite: sprite to use
	* param: x: Player's x Coordinate
	* param: y: Player's y Coordinate
	* param: scale: player sprite scale
	*/
	void set(sprite set_sprite, int x, int y, int scale)
	{
		private_sprite = set_sprite;
		private_exists = true;
		private_sprite.setPosition(x, y);
		private_scale = scale;
		private_sprite.scale(scale);
	}

	/**
	* brief: returns player's X coordinate
	*/
	int getX()
	{
		return private_sprite.getX();
	}

	/**
	* brief: return player's Y coordinate
	*/
	int getY()
	{
		return private_sprite.getY();
	}

	/**
	* brief: move player
	* param: x: new x position (to move relative, I recommend using obj_Player.getX() + relative
	* param: y: new y position (to move relative, I recommend using obj_Player.getY() + relative
	*/
	void move(int x, int y)
	{
		private_sprite.setPosition(x, y);
	}

	/**
	* brief: draws player
	* param: relative_x: x offset from x value (useful for 3D)
	* param: relative_y: y offset from y value (possibly useful for 3D)
	*/
	void draw(int relative_x, int relative_y)
	{
		private_sprite.draw(relative_x, relative_y);
	}

	/**
	* brief: returns true if the player 'exists' (useful for death vs. life)
	*/
	bool exists()
	{
		return private_exists;
	}
	
	/**
	* brief: returns scale of player sprite
	*/
	int scale()
	{
		return private_scale;
	}

	/**
	* brief: sets player sprite scale
	* param: n: new scale (int) (for relative, recommended to use obj_Player.scale()
	*/
	void setScale(int n)
	{
		private_sprite.scale(n);
		private_scale = n;
	}

	/**
	* brief: toggles 'existance' (bool exists) state
	*/
	void changeExistance()
	{
		if (private_exists)
			private_exists = false;
		else
			private_exists = true;
	}
};

class obj_Tile {
	sprite private_sprite;
public:

	/**
	* brief: set's initial values for tile [recommended to do this before using tile]
	*/
	void set(sprite set_sprite, int x, int y, int scale)
	{
		private_sprite = set_sprite;
		private_sprite.setPosition(x, y);
		private_sprite.scale(scale);
	}

	/**
	* brief: returns tiles X coordinate
	*/
	int getX()
	{
		return private_sprite.getX();
	}

	/**
	* brief: returns tiles Y coordinate
	*/
	int getY()
	{
		return private_sprite.getY();
	}

	/**
	* brief: moves tile
	* param: x: new X value (int) (for relative, recommended to use obj_Tile.getX()
	* param: y: new Y value (int) (for relative, recommended to use obj_Tile.getY()
	*/
	void move(int x, int y)
	{
		private_sprite.setPosition(x, y);
	}

	/**
	* brief: draws tile
	* param: relative_x: offset from set X (useful for 3D)
	* param: relative_y: offset from set Y (possibly useful for 3D)
	*/
	void draw(int relative_x, int relative_y)
	{
		private_sprite.draw(relative_x, relative_y);
	}
};

class obj_Enemy {
	sprite private_sprite;
	bool private_exists;
	int private_scale;
	bool isGeno;
	bool isGoblin;
	char *temp;
public:

	obj_Enemy(std::string type);

	//obj_Enemy(std::string type);

	/**
	* brief: set's Enemy's [default] values [USE THIS BEFORE USING THE PLAYER OBJECT]
	* param: set_sprite: sprite to use
	* param: x: Enemy's x Coordinate
	* param: y: Enemy's y Coordinate
	* param: scale: enemy sprite scale
	*/
	void set(int x, int y, int scale)
	{
		if (isGeno)
			private_sprite = spr_Geno;
		else if (isGoblin)
			private_sprite = spr_Goblin;
		else
			private_sprite = spr_Null;
		private_exists = true;
		private_sprite.setPosition(x, y);
		private_scale = scale;
		private_sprite.scale(scale);
	}

	/**
	* brief: returns enemy's X coordinate
	*/
	int getX()
	{
		return private_sprite.getX();
	}

	/**
	* brief: return enemy's Y coordinate
	*/
	int getY()
	{
		return private_sprite.getY();
	}

	/**
	* brief: move enemy
	* param: x: new x position (to move relative, I recommend using obj_Enemy.getX() + relative
	* param: y: new y position (to move relative, I recommend using obj_Enemy.getY() + relative
	*/
	void move(int x, int y)
	{
		private_sprite.setPosition(x, y);
	}

	/**
	* brief: draws enemy
	* param: relative_x: x offset from x value (useful for 3D)
	* param: relative_y: y offset from y value (possibly useful for 3D)
	*/
	void draw(int relative_x, int relative_y)
	{
		private_sprite.draw(relative_x, relative_y);
	}

	/**
	* brief: returns true if the enemy 'exists' (useful for death vs. life)
	*/
	bool exists()
	{
		return private_exists;
	}

	/**
	* brief: returns scale of enemy sprite
	*/
	int scale()
	{
		return private_scale;
	}

	/**
	* brief: sets enemy sprite scale
	* param: n: new scale (int) (for relative, recommended to use obj_Enemy.scale()
	*/
	void setScale(int n)
	{
		private_sprite.scale(n);
		private_scale = n;
	}

	/**
	* brief: toggles 'existance' (bool exists) state
	*/
	void changeExistance()
	{
		if (private_exists)
			private_exists = false;
		else
			private_exists = true;
	}
};
