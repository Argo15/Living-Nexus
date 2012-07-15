#include <iostream>
#include "ArgoModel.h"
using namespace std;

int main(int argc, char *argv[]) {
	ArgoModel *model = new ArgoModel();
	string location;

	for (int i = 0; i<argc; i++) {
		location = argv[i];
		cout << "loading " << location << endl;
		model->loadModel(location.c_str());
		cout << "calculating tangents" << endl;
		model->calcFlatTangents();
		int pos = location.find(".obj")+1;
		location.insert(pos,"a");
		cout << "saving " << location << endl;
		model->save(location);
		cout << "finished" << endl;
	}
	Sleep(3000);
	return 0;
}