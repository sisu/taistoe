const double PHYS_FPS = 50;
const double PHYS_FRAME = 1/PHYS_FPS;
const double PLAYER_SIZE = 0.4;

struct Unit;
struct Area;
void moveUnits(Unit* us, int n, Area& a);
