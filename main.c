#include <stdio.h>


void clearString(char * s, int len)
{
	int i;
	for (i = 0; i < len; i++)
	{
		s[i] = '\0';
	}
}


int parseLine(char * s, int * next)
{
	int i = 0;
	int count = 0;

	char word[32] = "";

	//word[0] = s[0];

	if (s[0] == '\0')
	{
		*next = -1;

		return -1;
	}
	else
	{
		while(s[i] != '\0')
		{
			//fprintf(stdout, "Char = %c\n", s[i]);
			if (s[i] == ' ' || s[i] == '\n')
			{
				fprintf(stdout, "Word = %s\n", word);
				count = 0;
				clearString(word, 32);
			}
			else
			{
				word[count] = s[i];
				++count;
			}

			++i;

		//fprintf(stdout, "There were %d symbols\n\n", i);

		*next += i + 1;

		}
		return 1;
	}
}


void readFaces(char * line)
{
	int a, b, c;
	sscanf(line, "f %d%*[^ ]%d%*[^ ]%d%*[^\n]", &a, &b, &c);
	//fprintf(stdout, "\ta = %d, b = %d, c = %d\n", a, b, c);
}


void readVertexes(char * line)
{
	double a, b, c;
	sscanf(line, "v %lf %lf %lf", &a, &b, &c);
	//fprintf(stdout, "\tA = %f, B = %f, C = %f\n", a, b, c);
}


void readFile(char * fileName)
{
	int vertexes = 0;
	int faces = 0;
	char line[256] = "";
	FILE * file = fopen(fileName, "r");
	if (file == NULL)
	{
		fprintf(stdout, "No file!\n");
	}
	else
	{
		while(!feof(file))
		{
			if (fgets(line, 255, file))
			{
				switch (line[0])
				{
					case 'v':
						if (line[1] == ' ')
						{
							//fprintf(stdout, "Vertex line: %s", line);
							readVertexes(line);
							++vertexes;
						}
						break;

					case 'f':
						if (line[1] == ' ')
						{
							//fprintf(stdout, "Face line: %s", line);
							readFaces(line);
							++faces;
						}
						break;

					default:
						//fprintf(stdout, "Not a needed line\n");
						break;
				}
			}
		}
		fprintf(stdout, "\nIn %s Vertexes = %d, faces = %d\n", fileName, vertexes, faces);
		fclose(file);
	}
}


int main()
{
	readFile("./obj/cube.obj");
	readFile("./obj/african_head.obj");

	return 0;
}
