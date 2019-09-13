#ifndef OBJLIB_H
#define OBJLIB_H

#define BUFFER_LENGTH 255
#define START_VERTEX_COUNT 2
#define MULTIPLIER 2
#define OBJ_STARTS_COUNTING_FROM_ONE 1


typedef struct AllVertexes
{
	int size;
	int current;
	struct Vertex * v;
} AllVertexes;


/*
typedef struct AllFaces
{
	int size;
	int current;
	struct Face * v;
} AllFaces;
*/


struct Vertex
{
	double x;
	double y;
	double z;
} Vertex;


typedef struct Face
{
	struct Vertex a;
	struct Vertex b;
	struct Vertex c;
} Face;


void readFaces(char * line);

void readVertexes(char * line, struct Vertex * v);

void printfVertexes(AllVertexes * AllVert);

void WriteVertexLine(AllVertexes * V, char * line);

//void WriteFaceLine(AllFaces * F, char * line);

AllVertexes * CreateVertexesList(void);

//AllPoints * CreatePoints(AllVertexes * V, AllFaces * F);

void ParseObjFile(char * fileName);

//void DeleteFacesAndVertexes(AllVertexes * V, AllFaces * F);


#endif //OBJLIB_H
