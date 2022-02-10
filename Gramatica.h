#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <map>
class Gramatica {
	std::string Vn;
	std::string Vt;
	std::string S;
	std::vector<std::pair<std::string, std::string>> P;
	std::string stanga, dreapta;
	int nr_productii;
public:
	friend std::istream& operator >> (std::istream& in, Gramatica& Gr);
	friend std::ostream& operator <<(std::ostream& out, Gramatica Gr);
	void verificare();
	bool regula1();
	bool regula2();
	bool regula3();
	bool regula4();
	bool regula5();
	bool cuv_format_din_terminale(std::string s);
	std::string GetVn();
    std::string GetVt();
	std::string GetS();
	std::vector<std::pair<std::string, std::string>> GetP();
	void SetVn(const std::string& Vn1);
	void SetVt(const std::string& Vt1);
	void SetS(const std::string& S1);
	void SetP(const std::vector<std::pair<std::string, std::string>>& P1);
	Gramatica();
	Gramatica(std::string Vn1,std::string Vt1, std::string S1, std::vector<std::pair<std::string, std::string>> P1, int nr_productii1);
	void Generare_cuvant(std::string &s, std::map<std::string, int> map);
	std::string Generare_cuvrez(std::string &s,std::map<std::string, int> map);
	int random_number(const int& a, const int& b);


};
