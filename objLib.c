#include <stdio.h>
#include <malloc.h>

#include "objLib.h"


void readFaces(struct Face * f, char * line)
{
	sscanf(line, "f %d%*[^ ]%d%*[^ ]%d%*[^\n]", &f->vA, &f->vB, &f->vC);
}


void WriteVertexLine(All * all, char * line)
{
	++all->vCurrent;

	if (all->vCurrent >= all->vSize)
	{
		all->vSize *= MULTIPLIER;
		all->V = (struct Vertex *) realloc(all->V, sizeof(struct Vertex) * all->vSize);
	}

	all->V[all->vCurrent].x = 1.0;
	all->V[all->vCurrent].y = 1.0;
	all->V[all->vCurrent].z = 1.0;
}


void WriteFaceLine(All * all, char * line)
{
	++all->fCurrent;

	if (all->fCurrent >= all->fSize)
	{
		all->fSize *= MULTIPLIER;
		all->F = (struct Face *) realloc(all->F, sizeof(struct Face) * all->fSize);
	}

	readFaces(&all->F[all->fCurrent], line);
}


void CreatePoints(All * all)
{
	int i, j;

	all->Triangles = (struct Vertex **) malloc(sizeof(struct Vertex *) * all->fCurrent);
	for (i = 0; i < all->fCurrent; i++)
	{
   	all->Triangles[i] = (struct Vertex *) malloc(sizeof(struct Vertex) * 3);
	}
	
	for (i = 0; i < all->fCurrent; i++)
	{
		for (j = 0; j < 3; j++)
		{
			all->Triangles[i][j].x = 0.0;
			all->Triangles[i][j].y = 1.0;
			all->Triangles[i][j].z = 2.0;
		}
	}
}


void DeleteAll(All * all)
{
	free(all->V);
	free(all->F);
	free(all->Triangles);
	free(all);
}


void ParseObjFile(char * fileName)
{
	char line[BUFFER_LENGTH + 1] = "";
	FILE * file = fopen(fileName, "r");

	All * all = malloc(sizeof(All));
	all->vSize = START_VERTEX_COUNT;
	all->vCurrent = 0;
	all->fSize = START_FACE_COUNT;
	all->fCurrent = 0;
	all->V = malloc(sizeof(struct Vertex) * START_VERTEX_COUNT);
	all->F = malloc(sizeof(struct Face) * START_FACE_COUNT);

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
							WriteVertexLine(all, line);

						break;

					case 'f':
						if (line[1] == ' ')
						{
							WriteFaceLine(all, line);
						}
						break;

					default:
						break;
				}
			}
		}

		fclose(file);

		CreatePoints(all);
		fprintf(stdout, "There are %d vertexes in %d size\n\t\t %d faces in %d size\n", all->vCurrent, all->vSize, all->fCurrent, all->fSize);
	}
}
