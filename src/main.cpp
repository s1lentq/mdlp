#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "studio.hpp"

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: <filename.mdl>\n");
		return -1;
	}

	FILE *fp = fopen(argv[1], "rb");
	fseek(fp, 0, SEEK_END);
	auto size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char *data = (char *)malloc(size);
	if (!data) {
		fclose(fp);
		printf("Can't allocate memory\n");
		return -1;
	}

	fread(data, size, 1, fp);
	fclose(fp);

	// check data header
	if (*(unsigned int *)data != IDSTUDIOHEADER) {
		printf("The file is not a model.\n");
		free(data);
		return -1;
	}

	studiohdr_t *pstudiohdr = (studiohdr_t *)data;
	mstudiobone_t *pbones = (mstudiobone_t *)((char *)pstudiohdr + pstudiohdr->boneindex);
	for (int i = 0; i < pstudiohdr->numbones; i++)
	{
		pbones[i].bonecontroller[0] = pbones[i].name[1] == '0' ? 0 : 1;
		pbones[i].bonecontroller[1] = pbones[i].name[2] == '0' ? 2 : 3;
		pbones[i].bonecontroller[2] = pbones[i].name[0] == '0' ? 4 : 5;
	}

	char szFileName[_MAX_PATH];
	strncpy(szFileName, argv[1], sizeof(szFileName) - 1);
	szFileName[sizeof(szFileName) - 1] = '\0';

	// strip .mdl
	char *pos = strstr(szFileName, ".mdl");
	if (pos) {
		*pos = '\0';
	}

	strcat(szFileName, "_patch.mdl");

	fp = fopen(szFileName, "wb");
	if (!fp) {
		printf("Can't open to write %s\n", szFileName);
		free(data);
		return -1;
	}

	fwrite(data, 1, size, fp);
	fclose(fp);
	free(data);

	return 0;
}
