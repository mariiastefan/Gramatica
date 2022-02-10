#include <iostream>
#include <fstream>
#include "Gramatica.h"
#include <set>
std::ifstream f("gramatica.txt");
int main()
{
	int n;
	std::cout << "n=";
	std::cin >> n;
	Gramatica gr;
	f >> gr;
	std::cout << gr;
	gr.verificare();
	std::map<std::string, int> map;
	for (auto ind : gr.GetP())
	{
		map[ind.first] = 1;
	}
	int preferinta;
	std::cout << "Alegeti modul cum doriti sa va fie afisata productia, 0-pe pasi, 1-doar rezultatul: ";
	std::cin >> preferinta;
	std::cout << std::endl;
	for (int index = 0; index < n; index++)
	{
		if (preferinta == 0)
		{
			std::cout << gr.GetS();
			std::string x = gr.GetS();
			gr.Generare_cuvant(x, map);
			if (gr.cuv_format_din_terminale(x) == false)
				std::cout << "\nCuvantul nu este format doar din terminale";
			std::cout << std::endl;
		}
		if (preferinta == 1)
		{
			std::string x = gr.GetS();
			std::cout<<gr.Generare_cuvrez(x, map);
			if (gr.cuv_format_din_terminale(x) == false)
				std::cout << "\nCuvantul nu este format doar din terminale";
			std::cout << std::endl;
		}
	}

	return 0;
}