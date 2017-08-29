#include "stdafx.h"
#include "FBXExporter.h"

int main(int argc, char** argv)
{
	// TODO: create binary format
	// Output for materials

	FBXExporter* myExporter = new FBXExporter();
	myExporter->Initialize();
	myExporter->LoadScene("two_textures_and_three_mat.FBX"/*argv[1]*/);
	myExporter->ExportAsMesh("Testing");
	//myExporter->ExportFBX();

	getch();
}