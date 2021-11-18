#include <iostream>
#include <string.h>
#include <assert.h>
#include <sstream>
#include <fstream>
#include <stdio.h> 

void run(std::istream& input, std::ostream& output, int N) {
    std::ifstream FileDataBase("fileBD.txt");
    std::string PasswordFromDataBase;
    for (int i = 1;i<N;++i) {
        FileDataBase >> PasswordFromDataBase;
    }
    FileDataBase >> PasswordFromDataBase;
    FileDataBase.close();
    std::string PasswordFromYou;
    input >> PasswordFromYou;
    std::ofstream fout("filein.txt");
    fout << PasswordFromYou;
    fout.close();
    system("openssl enc -base64 -in filein.txt -out fileout.txt");
    std::ifstream fin("fileout.txt");
    fin >> PasswordFromYou;
    output << (PasswordFromYou == PasswordFromDataBase);
    fin.close();
}

void testCripting()
{
	{
		std::stringstream input;
		std::stringstream output;
		input << "crypto345";
		run( input, output , 1);
        assert(output.str() == "1");
	}
    {
		std::stringstream input;
		std::stringstream output;
		input << "crapto345";
		run( input, output , 1);
        assert(output.str() == "0");
	}
    {
		std::stringstream input;
		std::stringstream output;
		input << "tratatr327_";
		run( input, output , 2);
        assert(output.str() == "1");
	}
    {
		std::stringstream input;
		std::stringstream output;
		input << "traktor234";
		run( input, output , 2);
        assert(output.str() == "1");
	}
}

int main() {
    testCripting();
}