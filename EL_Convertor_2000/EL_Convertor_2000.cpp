#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <math.h>
#include "EL_Convertor_2000.h"
#include <Windows.h>

//binary to decimal
int bi_to_de(std::vector<unsigned char> data)
{
	int base_d = 0;
	for (size_t i = 0; i < size(data); i++)
	{
		base_d += data[i] * std::pow(2, data.size() - 1 - i);
	}
	return base_d;
}

//choix dans la palette
std::string choose_pal(int cara, std::vector<std::string> palette)
{
	int indice_a_choisir;
	indice_a_choisir = (cara * palette.size()) / 255;
	return palette[indice_a_choisir];
}

//Demande le nom du fichier
std::string GetNomFichier()
{
	std::string choix;
	std::cout << "Quel fichier vouslez-vous transformer (afficher l'extension) : ";
	std::cin >> choix;
	choix = "../" + choix;
	return choix;
}




//palette
std::vector<std::string> dec_pal(std::string pale)
{
	std::ifstream pal(pale);
	std::vector<std::string> paltt;
	std::string strpal;
	while (!pal.eof())
	{
		std::getline(pal, strpal);
		paltt.push_back(strpal);
	}
	return paltt;
}

std::vector<std::vector<int>> fileToTab(std::string nf, int wid, int hei)
{
	//Recupération de la taille de l'image x y
	//Ouverture du fichier "ImageTest1.pgm" en mode binaire :
	std::ifstream fichier(nf, std::ios_base::binary);
	//Décodage de l'entete du fichier
	std::string strX, strY;
	int x, y;
	for (size_t i = 0; i < 4; i++)
	{
		std::string lol;
		std::getline(fichier, lol);

		if (i == 2)
		{
			std::stringstream sstr(lol);
			std::getline(sstr, strX, ' ');
			std::getline(sstr, strY, ' ');
			x = std::stod(strX);
			y = std::stod(strY);
			std::cout << x << " , " << y << "\n";
		}
	}

	std::vector<std::vector<int>> sylvio;
	sylvio.resize(x);

	//Affichage
	//Création d'une mémoire de 1 octets :
	std::vector<unsigned char> donnees(1);
	//Lecture de 1 octets depuis le fichier et stockage dans le tableau donnees :
	for (size_t i = 0; i < x; i++)
	{
		for (size_t j = 0; j < y; j++)
		{
			sylvio[i].resize(y);
			fichier.read(reinterpret_cast<char*>(donnees.data()), 1); ///REFLECHIS
			for (auto leo : donnees)
			{
				sylvio[i][j] = bi_to_de(donnees);

			}
		}
		//std::cout << "\n";
		//w_file << std::endl;
	}
	return sylvio;
}


std::vector<std::vector<int>> reechantillionnage(std::vector<std::vector<int>> sylvionormal,int maxw, int maxh)
{
	// Nouvelle image redimensionnée
	std::vector<std::vector<int>> image_resized;

	// Facteur de réduction
	int fac;

	int x = sylvionormal.size();
	int y = sylvionormal[0].size();

	int f1, f2;
	f1 = y/maxw ;
	f2 = x/maxh;
	int ruf = x / f1;
	if (ruf<maxh)
		fac=f1;
	else
		fac=f2;



	// Parcourir l'image par blocs de 2x2 valeurs ASCII
	for (size_t i = 0; i < sylvionormal.size(); i += fac)
	{
		std::vector<int> new_row;

		for (size_t j = 0; j < sylvionormal[i].size(); j += fac)
		{
			// Prendre la valeur ASCII moyenne des 4 éléments (ou simplement le premier élément)
			int reduced_value = sylvionormal[i][j];  // Vous pouvez changer cette logique

			// Vous pouvez aussi calculer la moyenne des valeurs si nécessaire
			// int reduced_value = (sylvionormal[i][j] + sylvionormal[i + 1][j] + sylvionormal[i][j + 1] + sylvionormal[i + 1][j + 1]) / 4;

			// Ajout de cette valeur à la nouvelle ligne
			new_row.push_back(reduced_value);
		}

		// Ajout de la nouvelle ligne à l'image redimensionnée
		image_resized.push_back(new_row);
	}

	return image_resized;
}

void diplayConsole(std::vector<std::vector<int>> tab,std::vector<std::string> palette)
{
	for (auto a:tab)
	{
		for(auto b:a)
		{
			std::cout << choose_pal(b, palette);
		}
		std::cout << "\n";
	}

}

void createFile(std::vector < std::vector<int>> tab , std::string res, std::vector<std::string> palette)
{
	std::ofstream fichier_a_ecrire(res);
	for (auto a : tab)
	{
		for (auto b : a)
		{
			fichier_a_ecrire << choose_pal(b, palette);
		}
		fichier_a_ecrire << std::endl;
	}
}

