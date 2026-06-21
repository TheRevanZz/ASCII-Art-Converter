#include <vector>
#include <string>
#include <fstream>

int bi_to_de(std::vector<unsigned char> data);
std::string choose_pal(int cara, std::vector<std::string> palette);
std::string GetNomFichier();
std::vector<std::string> dec_pal(std::string pale);
std::vector<std::vector<int>> fileToTab(std::string nf, int wid, int hei);
void diplayConsole(std::vector<std::vector<int>> tab, std::vector<std::string> palette);
void createFile(std::vector < std::vector<int>> tab, std::string res, std::vector<std::string> palette);
std::vector<std::vector<int>> reechantillionnage(std::vector<std::vector<int>> sylvionormal, int maxw, int maxh);