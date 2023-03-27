#include "AnimationWindow.h"
#include "Cat.h"
#include "SurpriseFace.h"


// Definer størrelse på vindu og emoji
constexpr int xmax = 1000;
constexpr int ymax = 600;
constexpr int emojiRadius = 50;

int main()
{

	const Point tl{100, 100};
	const string win_label{"Emoji factory"};
	AnimationWindow win{tl.x, tl.y, xmax, ymax, win_label};

	SurpriseFace f({200, 200}, emojiRadius);
	f.draw(win);
	
	win.wait_for_close();

	return 0;
}
