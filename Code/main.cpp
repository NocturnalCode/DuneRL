
#ifdef _WIN32
#include "SDL.h"
#endif
#include "DuneRL.h"
#include <cstdlib>

int main(int argc, char *argv[])
{
    DuneRL *rogue = new DuneRL();
    rogue->poll();
	delete(rogue);
    return 0;
}
