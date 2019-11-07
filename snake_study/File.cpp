#include "File.h"
#include "main.h"
#include <cstdio>

extern int g_nSpeed;
extern int g_nObstacle;
void File::readFile(const char* fileName, int nEleSize, void* p) {
	FILE* pf = NULL;
	int nElementCount = 0;
	if (fopen_s(&pf, fileName, "rb") || pf == nullptr) {
		return;
	}

	if (fseek(pf, SEEK_SET, SEEK_END)) {
		// return nElementCount;
	}
	long nCountSize = ftell(pf); // 总大小

	nElementCount = nCountSize / nEleSize;

	rewind(pf);
	fread(p, nEleSize, nElementCount, pf);

	fclose(pf);

	return;
}

void File::writeFile(const char* fileName, int nEleSize, int nCount, const void* p) {
	FILE* pf = nullptr;
	if (fopen_s(&pf, fileName, "wb") || pf == NULL) {
		printf("存档失败");
		exit(EXIT_FAILURE);
	}
	fwrite(p, nEleSize, nCount, pf);
	fclose(pf);
	return;
}

void File::readMap(std::vector<MapPointer>& mps) {
	FILE* pf = NULL;
	int nElementCount = 0;
	int nEleSize = sizeof(MapPointer);
	if (fopen_s(&pf, SNAKEMAPFIELNAME, "rb") || pf == nullptr) {
		return;
	}
	fseek(pf, SEEK_SET, SEEK_END);

	long nCountSize = ftell(pf); // 总大小
	nElementCount = nCountSize / nEleSize;
	MapPointer* pmp = new MapPointer[nCountSize];
	nElementCount = nCountSize / nEleSize;

	rewind(pf);
	fread(pmp, nEleSize, nElementCount, pf);

	fclose(pf);
	for (int i = 0; i < nElementCount; i++) {
		mps.push_back(pmp[i]);
	}
	delete[] pmp;
	return;

}

void File::readBody(std::vector<SnakeNode>& body) {
	FILE* pf = NULL;
	int nElementCount = 0;
	int nEleSize = sizeof(SnakeNode);
	if (fopen_s(&pf, SNAKEBODYFILENAME, "rb") || pf == nullptr) {
		return;
	}
	fseek(pf, SEEK_SET, SEEK_END);

	long nCountSize = ftell(pf); // 总大小
	nElementCount = nCountSize / nEleSize;
	SnakeNode* pmp = new SnakeNode[nCountSize];
	nElementCount = nCountSize / nEleSize;

	rewind(pf);
	fread(pmp, nEleSize, nElementCount, pf);

	fclose(pf);
	for (int i = 0; i < nElementCount; i++) {
		body.push_back(pmp[i]);
	}
	delete[] pmp;
	return;
}

void File::saveBody(const SnakeNode* psn, int nCount) {
	writeFile(SNAKEBODYFILENAME, sizeof(SnakeNode), nCount, psn);
}

void File::saveSnakeInfo(SNAKEINFO& snakeInfo) {
	writeFile(SNAKEINFOFILENAME, sizeof(SNAKEINFO), 1, &snakeInfo);
}

void File::readSnakeInfo(short& nFoodX, short& nFoodY, short& nEatFoodCount, short& nScore, short& nDire) {
	SNAKEINFO* psn = new SNAKEINFO;
	readFile(SNAKEINFOFILENAME, sizeof(SNAKEINFO), psn);
	nFoodX = psn->nFoodX;
	nFoodY = psn->nFoodY;
	nEatFoodCount = psn->nEatFoodCount;
	nScore = psn->nScore;
	nDire = psn->nDire;
	g_nSpeed = psn->nSpeed;
	g_nObstacle = psn->nObstacle;
}

void File::saveMap(const MapPointer* pmp, int nCount) {
	writeFile(SNAKEMAPFIELNAME, sizeof(MapPointer), nCount, pmp);
}


