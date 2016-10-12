#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	TCHAR  *directory = TEXT("d:\\");
	TCHAR patter[MAX_PATH];
	TCHAR fileName[MAX_PATH];
	memset(patter, 0x00, MAX_PATH);
	_stprintf(patter, TEXT("%s\\*.dat"), directory);
	hFind = FindFirstFile(patter, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		printf("FindFirstFile failed (%d)\n", GetLastError());
		return 1;
	}
	else
	{
		do
		{
			//ignore current and parent directories
			if (_tcscmp(FindFileData.cFileName, TEXT(".")) == 0 || _tcscmp(FindFileData.cFileName, TEXT("..")) == 0)
				continue;

			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				//ignore directories
			}
			else
			{
				//list the Files

				_tprintf(TEXT("%s\n"),

					FindFileData.cFileName);
				memset(fileName, 0x00, sizeof(fileName));
				_stprintf(fileName, TEXT("%s\\%s"), directory, FindFileData.cFileName);
				FILE *fptr = _tfopen((const TCHAR *)fileName, TEXT("r"));
				//do here whatever you want to do..
				fclose(fptr);
			}
		} while (FindNextFile(hFind, &FindFileData));
		FindClose(hFind);
	}
	system("pause");
	return 0;
}