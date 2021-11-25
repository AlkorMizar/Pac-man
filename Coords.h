#pragma once
struct Coords
{
	double x;
	double y;
};

namespace directions {
	const Coords    UP{  0, 1 };
	const Coords  DOWN{  0,-1 };
	const Coords RIGHT{  1, 0 };
	const Coords  LEFT{ -1, 0 };
}