#include "InitSDL.h"

int main(int argc, char* args[])
{
	InitSDL *app = new InitSDL();
	app->Run();
	delete app;
	return 0;
}