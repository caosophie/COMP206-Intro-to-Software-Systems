#ifndef NODEH
#define NODEH

struct ZoomRecord
{
	char email[60];
	char name[60];
	int durations[9];
	struct ZoomRecord *next;
};

void addZoomRecord(char *email, char *name, char *lab, int duration);
void generateAttendance(FILE *output);
void freelist();
#endif
