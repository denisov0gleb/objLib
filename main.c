#include <stdio.h>
#include <malloc.h>


#define bufferLength 255


typedef struct Vertex
{
	double x;
	double y;
	double z;
} Vertex;


typedef struct Vertexes
{
	int totalVertexes;
	int spaceForVertexes;
	Vertex * vertexList;
} Vertexes;


typedef struct Face
{
	Vertex a;
	Vertex b;
	Vertex c;
} Face;



void readFaces(char * line)
{
	int a, b, c;
	sscanf(line, "f %d%*[^ ]%d%*[^ ]%d%*[^\n]", &a, &b, &c);
}


void readVertexes(char * line, Vertex * v)
{
	sscanf(line, "v %lf %lf %lf", &v->x, &v->y, &v->z);
}


void printfVertexes(Vertexes * Vert)
{
	int i;
	for (i = 1; i <= Vert->totalVertexes; i++)
	{
		fprintf(stdout, "Vertex: %f %f %f\n", Vert->vertexList[i].x, Vert->vertexList[i].y, Vert->vertexList[i].z);
	}
}


void readFile(char * fileName, Vertexes * Vert)
{
	Vert->totalVertexes = 0;
	int faces = 0;
	char line[bufferLength + 1] = "";

	fprintf(stdout, "OK!\n");
	Vert->vertexList = (Vertex *) malloc(sizeof(Vertex) * 10);
	//Vertex * vertexList = (Vertex *) malloc(sizeof(Vertex) * 10);
	Vert->spaceForVertexes = 10;
	//int vertexesInList = 10;

	fprintf(stdout, "OK!\n");
	FILE * file = fopen(fileName, "r");
	if (file == NULL)
	{
		fprintf(stdout, "No file!\n");
	}
	else
	{
		while(!feof(file))
		{
			if (fgets(line, bufferLength, file))
			{
				switch (line[0])
				{
					case 'v':
						if (line[1] == ' ')
						{
							if ( Vert->totalVertexes == Vert->spaceForVertexes )
							{
								Vert->spaceForVertexes += 10;
								Vert->vertexList = (Vertex *) realloc(Vert->vertexList, sizeof(Vertex)*Vert->spaceForVertexes);
								fprintf(stdout, "Expand vertexes list!\n");
							}

							++Vert->totalVertexes;
							readVertexes(line, &Vert->vertexList[Vert->totalVertexes]);
						}
						break;

					case 'f':
						if (line[1] == ' ')
						{
							readFaces(line);
							++faces;
						}
						break;

					default:
						break;
				}
			}
		}
		fprintf(stdout, "\nIn %s Vertexes = %d, faces = %d\n", fileName, Vert->totalVertexes, faces);
		fclose(file);
	}
}


int main()
{
	Vertexes * Vert;
	readFile("./obj/cube.obj", Vert);
	printfVertexes(Vert);
	//readFile("./obj/african_head.obj");

	return 0;
}
