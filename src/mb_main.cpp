#include <ijengine/exception.h>
#include <iostream>

#include "mb_game.h"

using namespace ijengine;
using namespace std;

int main(){
	int rc;

	try{
		MBGame game("Teste", 800, 600);
		rc = game.run("1");
	}catch(Exception &ex){
		cout << ex.what() << endl;
	}

	return rc;
}
