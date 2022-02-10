#include "Gramatica.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <utility>
#include <sstream>
#include <set>
#include <map>
#include <random>
std::istream& operator>>(std::istream& in, Gramatica& Gr)
{
	std::string buffer, words, buff;
	std::getline(in, buffer);
	std::istringstream iss(buffer);
	while (iss >> words)
	{
		Gr.Vn += words;
	}
	words.clear();
	buffer.clear();
	std::getline(in, buffer);
	std::istringstream is(buffer);
	while (is >> words)
	{
		Gr.Vt += words;
	}
	words.clear();
	buffer.clear();
	std::cin.get();
	in >> Gr.S;
	in >> Gr.nr_productii;
	for (int index = 0; index < Gr.nr_productii; index++)
	{
		in >> words >> buffer;
		Gr.P.push_back(std::make_pair(words, buffer));
		words.clear();
		buffer.clear();
	}
	return in;
}

std::ostream& operator<<(std::ostream& out, Gramatica Gr)
{
	out << "Acestea sunt elementele lui Vn: ";
	for (int index = 0; index < Gr.Vn.size(); index++)
	{
		out << Gr.Vn[index] << " ";
	}
	out << "\n";
	out << "Acestea sunt elementele lui Vt: ";
	for (int index = 0; index < Gr.Vt.size(); index++)
	{
		out << Gr.Vt[index] << " ";
	}
	out << "\n";
	out << "Acesta este primul cuvant ";
	out << Gr.S;
	out << "\n";
	for (auto index : Gr.P)
	{
		out << index.first << " -> " << index.second;
		out << "\n";
	}
	return out;
}

void Gramatica::verificare()
{
	if (regula1() == false)
		std::cout << "Regula1 a fost incalcata\n";
	if (regula2() == false)
		std::cout << "Regula2 a fost incalcata\n";
	if (regula3() == false)
		std::cout << "Regula3 a fost incalcata\n";
	if (regula4() == false)
		std::cout << "Regula4 a fost incalcata\n";
	if (regula5() == false)
		std::cout << "Regula5 a fost incalcata\n";
	if (regula1() && regula2() && regula3() && regula4() && regula5())
		std::cout << "Gramatica este corecta";

}

bool Gramatica::regula1()
{
	for (auto indvn : Vn)
	{
		for (auto indvt : Vt)
		{
			if (indvn == indvt)
				return false;
		}
	}
	return true;
}

bool Gramatica::regula2()
{
	if (Vn.find(S) == std::string::npos)
		return false;
	return true;
}

bool Gramatica::regula3()
{
	int ok = false;
	for (auto& it : P)
	{
		/*if (Vn.find(it.first) == std::string::npos)
		{
				return false;
		}*/
		if (it.first.size() > 1)
		{
			for (auto& it1 : it.first)
				if (Vn.find(it1) != std::string::npos)
				{
					ok = true;
				}
			if (ok == true)
			{
				for (auto& it2 : it.first)
					if (Vn.find(it2) != std::string::npos)
					{
						return true;
					}
			}
		}
		else
		{
			if (Vn.find(S) == std::string::npos)
				return false;
			return true;
		}

	}
	return true;


}

bool Gramatica::regula4()
{

	for (auto& it : P)
	{
		if (it.first.find(S) == NULL)
			return true;
	}
	return false;
}

bool Gramatica::regula5()
{
	std::string concat = Vn + Vt;
	for (auto ind : P)
	{
		for (auto ind1 : ind.first)
			if (concat.find(ind1) == std::string::npos)
				return false;
		for (auto ind2 : ind.second)
		{
			if (ind2 == '#')
				return true;

			if (concat.find(ind2) == std::string::npos)
				return false;
		}
	}
	return true;
}

bool Gramatica::cuv_format_din_terminale(std::string s)
{
	if (s == " ")
		return true;
	for (auto ind1 : s)
	{
		if (Vt.find(ind1) == std::string::npos)
			return false;
	}
	return true;
}

std::string Gramatica::GetVn()
{
	return Vn;
}

std::string Gramatica::GetVt()
{
	return Vt;
}

std::string Gramatica::GetS()
{
	return S;
}

std::vector<std::pair<std::string, std::string>> Gramatica::GetP()
{
	return P;
}

void Gramatica::SetVn(const std::string& Vn1)
{
	Vn = Vn1;
}

void Gramatica::SetVt(const std::string& Vt1)
{
	Vt = Vt1;
}

void Gramatica::SetS(const std::string& S1)
{
	S = S1;
}

void Gramatica::SetP(const std::vector<std::pair<std::string, std::string>>& P1)
{
	P = P1;
}

Gramatica::Gramatica()
{
	S = "";
	nr_productii = 0;
}

Gramatica::Gramatica(std::string Vn1, std::string Vt1, std::string S1, std::vector<std::pair<std::string, std::string>> P1, int nr_productii1) :Vn{ Vn1 }, Vt{ Vt1 }, S{ S1 }, P{ P1 }, nr_productii{ nr_productii1 }
{
}

void Gramatica::Generare_cuvant(std::string& s, std::map<std::string, int> map)
{
	std::sort(P.begin(), P.end());
	bool flag = true;
	for (auto ind1 : map)
	{
		if (s.find(ind1.first) != std::string::npos)
		{
			flag = true;
			int a = 0, b = 0;
			for (int ind2 = 0; ind2 < P.size(); ind2++)
			{
				if (P[ind2].first == ind1.first)
				{
					a = ind2;
					break;
				}
			}
			for (int ind3 = a + 1; ind3 < P.size(); ind3++)
			{
				if (P[ind3].first != ind1.first)
				{
					b = ind3 - 1;
					break;
				}
				else
					if (P[ind3].first == ind1.first && ind3 == P.size() - 1)
					{
						b = ind3;
						break;
					}
			}
			int x = random_number(a, b);
			if (P[x].second == "#")
			{
				s.erase(s.begin() + s.find(ind1.first));
			}
			else

			{
				s.replace(s.find(ind1.first), ind1.first.length(), P[x].second);
			}
			std::cout << "->" << s;
			return Generare_cuvant(s, map);
		}
		else
		{
			flag = false;
		}

	}
	if (flag == false)
	{
		return;
	}
}

std::string Gramatica::Generare_cuvrez(std::string &s, std::map<std::string, int> map)
{
	std::sort(P.begin(), P.end());
	bool flag = true;
	for (auto ind1 : map)
	{
		if (s.find(ind1.first) != std::string::npos)
		{
			flag = true;
			int a = 0, b = 0;
			for (int ind2 = 0; ind2 < P.size(); ind2++)
			{
				if (P[ind2].first == ind1.first)
				{
					a = ind2;
					break;
				}
			}
			for (int ind3 = a + 1; ind3 < P.size(); ind3++)
			{
				if (P[ind3].first != ind1.first)
				{
					b = ind3 - 1;
					break;
				}
				else
					if (P[ind3].first == ind1.first && ind3 == P.size() - 1)
					{
						b = ind3;
						break;
					}
			}
			int x = random_number(a, b);
			if (P[x].second == "#")
			{
				s.erase(s.begin() + s.find(ind1.first));
			}
			else
			{
				s.replace(s.find(ind1.first), ind1.first.length(), P[x].second);
			}
			return Generare_cuvrez(s, map);
		}
		else
		{
			flag = false;
		}

	}
	if (flag == false)
	{
		return s;
	}

}

int Gramatica::random_number(const int& a, const int& b)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(a, b);

	return dist(mt);
}
