#pragma once
#include "Animation.h"

class Menu
{
private:
	int menuSprite;
	int chapterSprite;
	int choice = 0;
	std::vector<int> menuSelect;
	std::vector<int> chapterSelect;
	int chapterChoice = 0;
public:
	bool play_clicked = false;
	Menu()
	{
		menuSprite = iLoadImage("Images/menu/menu.png");
		chapterSprite = iLoadImage("images/menu/level.png");
		menuSelect.emplace_back(iLoadImage("images/menu/choiceplay.png"));
		menuSelect.emplace_back(iLoadImage("images/menu/choiceInstruction.png"));
		menuSelect.emplace_back(iLoadImage("images/menu/choiceCredits.png"));
		menuSelect.emplace_back(iLoadImage("images/menu/choiceExit.png"));
		chapterSelect.emplace_back(iLoadImage("images/menu/level1.png"));
		chapterSelect.emplace_back(iLoadImage("images/menu/level2.png"));
		chapterSelect.emplace_back(iLoadImage("images/menu/level3.png"));
		chapterSelect.emplace_back(iLoadImage("images/menu/levelback.png"));
	}

	void render() const
	{
		if (!play_clicked)
		{
			if (choice < 1)
				iShowImage(0, 0, 800, 600, menuSprite);
			else iShowImage(0, 0, 800, 600, menuSelect[choice - 1]);
		}
		else if (play_clicked)
		{
			if (chapterChoice <1)
				iShowImage(0, 0, 800, 600, chapterSprite);
			else iShowImage(0, 0, 800, 600, chapterSelect[chapterChoice - 1]);
		}
	}
	void update(int mx, int my)
	{
		if ((mx > 380 && my > 310) && (mx < 430 && my < 328))
		{
			choice = 1;
		}
		else if ((mx > 318 && my > 254) && (mx < 495 && my < 275)) choice = 2;
		else if ((mx > 364 && my > 207) && (mx < 445 && my < 225)) choice = 3;
		else if ((mx > 378 && my > 162) && (mx < 426 && my < 177)) choice = 4;
		else choice = 0;
		if (play_clicked)
		{
			if ((mx > 16 && my > 105) && (mx < 213 && my < 523)) chapterChoice = 1;
			else if ((mx > 305 && my > 102) && (mx < 501 && my < 521)) chapterChoice = 2;
			else if ((mx > 596 && my > 98) && (mx < 790 && my < 518)) chapterChoice = 3;
			else if ((mx > 23 && my > 28) && (mx < 146 && my < 65)) chapterChoice = 4;
			else chapterChoice = 0;
		}
	}
	int getChoice() const
	{
		return this->choice;
	}
	int getLevelChoice() const
	{
		return this->chapterChoice;
	}
};