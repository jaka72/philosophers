#include "philo.h"

char *colors(int i)
{
	if (i == 0)
		return BLU;
	else if (i == 1)
		return YEL;
 	else if (i == 2)
 		return GRN;
	else if (i == 3)
 		return RED;
	else if (i == 4)
 		return MAG;
	else if (i == 5)
 		return CYN;
	else if (i == 6)
 		return HYEL;
	else if (i == 7)
 		return HGRN;
	else if (i == 8)
 		return BLUBH;
	else if (i == 9)
 		return BLKB;
	RES = "\x1B[0m";
	return (RES);
}

char *choose_color(t_filo *f)
{
	char *color;
	int j;

	j = f->filo;
	if (colors_on == 1)
	{
		color = colors(f->filo); // CHOOSE COLOR FOR EACH THREAD
		RES = "\x1B[0m";
	}
	else if (colors_on == 0)
	{
		color = "";
		RES = "";
	}
	else if (colors_on == 2 && f->d->nrfilos >= 100)
	{
		if (j == 0)
		{
			color = BLU;
			RES = "\x1B[0m";
		}
		else if (j == 99)
		{
			color = MAG;
			RES = "\x1B[0m";
		}
		else if (j == 1)
		{
			color = YEL;
			RES = "\x1B[0m";
		}
		else
			color = "\x1B[0m";
	}
	return (color);
}
