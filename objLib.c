#include <stdio.h>
#include <malloc.h>

#include "objLib.h"


void readFaces(char * line)
{
	int a, b, c;
	sscanf(line, "f %d%*[^ ]%d%*[^ ]%d%*[^\n]", &a, &b, &c);
}


void readVertexes(char * line, struct Vertex * v)
{
	sscanf(line, "v %lf %lf %lf", &v->x, &v->y, &v->z);
}


void WriteVertexLine(AllVertexes * V, char * line)
{
	//fprintf(stdout, "Line!\n");
	++V->current;

	if (V->current >= V->size)
	{
		V->size *= MULTIPLIER;
		//fprintf(stdout, "Size is = %d\n", V->size);
		V->v = (struct Vertex *) realloc(V->v, sizeof(struct Vertex) * V->size);
		//fprintf(stdout, "\tExpand!\n");
	}

	V->v[V->current].x = 1.0;
	V->v[V->current].y = 1.0;
	V->v[V->current].z = 1.0;
}


/*
void WriteFaceLine(AllFaces * F, char * line)
{

}
*/


AllVertexes * CreateVertexesList(void)
{
	AllVertexes * AllVert = (AllVertexes *) malloc(sizeof(AllVertexes *));
	AllVert->v = malloc(sizeof(struct Vertex) * START_VERTEX_COUNT);
	AllVert->current = 0;
	AllVert->size = START_VERTEX_COUNT;

	return AllVert;
}


/*
AllPoints * CreatePoints(AllVertexes * V, AllFaces * F);
{
	return P;
}
*/


/*
void DeleteFacesAndVertexes(AllVertexes * V, AllFaces * F);
{

}
*/


void ParseObjFile(char * fileName)
{
	int faces = 0;
	char line[BUFFER_LENGTH + 1] = "";
	FILE * file = fopen(fileName, "r");
	AllVertexes * V = CreateVertexesList();
	//AllFaces * F = CreateFacesList(void);

	if (file == NULL)
	{
		fprintf(stdout, "No file!\n");
	}
	else
	{
		while(!feof(file))
		{
			if (fgets(line, BUFFER_LENGTH, file))
			{
				switch (line[0])
				{
					case 'v':
						if (line[1] == ' ')
							WriteVertexLine(V, line);

						break;

					case 'f':
						if (line[1] == ' ')
						{
							//WriteFaceLine(F, line);
							readFaces(line);
							++faces;
						}
						break;

					default:
						break;
				}
			}
		}
		fclose(file);

		//AllPoints * P = CreatePoints(V, F);
	}
}


