// (c) Daniel Bortfeld 2018
#pragma once
#ifndef COLORS_H
#define COLORS_H

enum Color
{
	Black,

	Blue,
	Green,
	Cyan,
	Red,
	Pink,
	Yellow,
	White,
	Grey,

	IntenseBlue,
	IntenseGreen,
	IntenseCyan,
	IntenseRed,
	IntensePink,
	IntenseYellow,
	IntenseWhite,

	BlueBackground = 16,
	GreenBackground = 32,
	CyanBackground = 48,
	RedBackground = 64,
	PinkBackground = RedBackground + 16,
	YellowBackground = PinkBackground + 16,
	WhiteBackground = RedBackground + GreenBackground + BlueBackground,
	GreyBackground = WhiteBackground + 16,

	IntenseBlueBackground = GreyBackground + 16,
	IntenseGreenBackground = IntenseBlueBackground + 16,
	IntenseCyanBackground = IntenseGreenBackground + 16,
	IntenseRedBackground = IntenseCyanBackground + 16,
	IntensePinkBackground = IntenseRedBackground + 16,
	IntenseYellowBackground = IntensePinkBackground + 16,
	IntenseWhiteBackground = IntenseYellowBackground + 16,
};

#endif // !COLORS_H
